#include "pch.h"
#include "CGear_PlayLevel.h"
#include "CPathMgr.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CNote.h"
#include "CJudgeTexture.h"
#include "CLineShine.h"
#include "CCoolbomb.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CCombo.h"
#include "CFever.h"

// define
#define GT (ULONGLONG)GEARLINE_TYPE
#define JVI (ULONGLONG)JUDGE_VECTOR_IDX
#define JUDGECHECK_TAPTIME m_JudgeRange[m_JudgeRangeIdx], iter->Note->m_fTapTime
#define CURNOTE_KEYCHECK m_KeyCheck[(ULONG)CurNote->m_Line]

CGear_PlayLevel::CGear_PlayLevel(vector<int>& _vecJudge, CJudgeTexture* _JudgeTexture
	, CLineShine* _LineTexture, CCoolbomb* _CoolbombTexture
	, CCombo* _Combo, CFever* _Fever)
	:m_NoteInfoIdx(0) // 0������ ����Ű�� ��Ʈ�� ���ʴ�� �ű�鼭 �ʱ�ȭ
	, m_KeyCheck{}
	, m_JudgeRange{ 41.67f,	20.83f, 10.42f }
	, m_JudgeRangeIdx(1)
	, m_vecJudge(_vecJudge)
	, m_JudgeTexture(_JudgeTexture)
	, m_LineTexture(_LineTexture)
	, m_CoolbombTexture(_CoolbombTexture)
	, m_Combo(_Combo)
	, m_Fever(_Fever)
{
	// init NotePool
	m_vecNotePool.reserve(POOL_MAX_SIZE);

	for (int i = 0; i < POOL_MAX_SIZE; ++i)
	{
		sNote* newsNote = new sNote;
		m_vecNotePool.push_back(newsNote);
	}

}

CGear_PlayLevel::~CGear_PlayLevel()
{
	for (auto& iter : m_vecNotePool)
	{
		delete iter->Note;
		delete iter;
	}
}

NoteInfo& NoteInfo::Load(FILE* _pFile)
{
	// NOTE_TYPE
	fread(&m_eType, sizeof(NOTE_TYPE), 1, _pFile);

	// GEARLINE_TYPE - ���;� �ϴ� ����
	fread(&m_Line, sizeof(GEARLINE_TYPE), 1, _pFile);

	// TapTime - tap �� �ð�(���� ���� ���൵�� ���� ��, 0.01�� ������ ���� ����)
	fread(&m_fTapTime, sizeof(float), 1, _pFile);

	// ReleasedTime - �����⸦ ������ �ð�(�� ��Ʈ, ���̵� Ʈ�������� ��� ����)
	fread(&m_fReleasedTime, sizeof(float), 1, _pFile);

	return *this;
}

// ���߿� �� �����ϸ� �ش� �� ������ �����Ǵ� ���Ͽ��� ������ �о���� �� ��.
void CGear_PlayLevel::LoadNoteData()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetContentPath();
	strTileFolderPath += L"note\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Note\0*.note\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	if (_wfopen_s(&pFile, szFilePath, L"rb"))
		LOG(LOG_LEVEL::ERR, L"���� ���⿡ �����߽��ϴ�..");

	// ��Ʈ ����
	size_t sizeBuf = 0;
	if (pFile)	fread(&sizeBuf, sizeof(size_t), 1, pFile);

	m_vecNoteInfo.reserve(sizeBuf);

	for (size_t i = 0; i < sizeBuf; ++i)
	{
		NoteInfo newdata = {};
		m_vecNoteInfo.push_back(newdata.Load(pFile));
	}

	for (size_t i = 0; i < POOL_MAX_SIZE; ++i)
	{
		*(m_vecNotePool[i]->Note) = GetNoteInfo();
	}



	if (pFile)
	{
		fclose(pFile);
	}
}

struct ShineTex;

void CGear_PlayLevel::NoteRender(HDC _dc, float speed)
{
	for (int i = 0; i < 4; ++i)
	{
		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.AlphaFormat = AC_SRC_ALPHA; // 0
		if (m_LineTexture->m_LineTex[i]->isRender)
		{
			blend.SourceConstantAlpha = m_LineTexture->m_LineTex[i]->alpha;
			POINT vImgScale = { (int)m_LineTexture->m_LineTex[i]->pShineTex->GetWidth(), (int)m_LineTexture->m_LineTex[i]->pShineTex->GetHeight() };
			AlphaBlend(_dc
				, 109 + 100 * i, 18
				, 100, 678
				, m_LineTexture->m_LineTex[i]->pShineTex->GetDC()
				, 0, 0
				, vImgScale.x, vImgScale.y
				, blend);
		}
	}
	// ��� Ǯ �����Ϳ� render ȣ��
	// ���� ���� ��� ��Ʈ render
	for (auto& iter : m_vecNotePool)
	{
		if (!iter->isJudged) iter->Note->render(_dc, m_CurMusicTime, speed);
	}
}

NoteInfo CGear_PlayLevel::GetNoteInfo()
{
	if (m_vecNoteInfo.size() > m_NoteInfoIdx)
		return m_vecNoteInfo[m_NoteInfoIdx++];
	else
		return NoteInfo();
}

bool CGear_PlayLevel::JudgeCheck(JUDGE_PERCENT_CAL _Percent, float _JudgeMode, float _TapTime)
{
	if (	(m_CurMusicTime + ((float)_Percent * 0.03334) + (_JudgeMode / 1000) > _TapTime)
		&&  (m_CurMusicTime - ((float)_Percent * 0.03334) - (_JudgeMode / 1000) < _TapTime))
		return true;
	else
		return false;
}

enum class JUDGE_PERCENT_CAL;	// => 100%,90%....
enum class JUDGE_MODE;			// => �⺻, �ϵ�, �ƽ� ��������
enum class JUDGE_VECTOR_IDX;	// ���� �ε��� üũ�� �� ���, JVI�� ġȯ

void CGear_PlayLevel::KeyCheck(GEARLINE_TYPE _line, KEY _key)
{
	m_KeyCheck[(ULONGLONG)_line].key_tap		= KEY_TAP(_key);
	m_KeyCheck[(ULONGLONG)_line].key_press		= KEY_PRESSED(_key);
	m_KeyCheck[(ULONGLONG)_line].key_release	= KEY_RELEASED(_key);

	if (m_KeyCheck[(ULONGLONG)_line].isTap()) 
	{
		m_LineTexture->SetShineOn(_line); // �ѱ�
	}
	if (m_KeyCheck[(ULONGLONG)_line].isRelease())
	{
		m_LineTexture->SetShineOff(_line); // ����
	}

}

// sort()�� callback �Լ�
bool compareNoteTapTime(const sNote* a, const sNote* b) 
{
	return *a->Note < *b->Note;
}

void CGear_PlayLevel::tick(float _DT)
{
	// Super tick
	CGear::tick(_DT);

#pragma region _	KEY_STATE_CHECK
	// Ű ���� ����
	KeyCheck(GEARLINE_TYPE::LEFTSIDE,	KEY::LSHIFT);
	KeyCheck(GEARLINE_TYPE::_1,			KEY::A);
	KeyCheck(GEARLINE_TYPE::_2,			KEY::S);
	KeyCheck(GEARLINE_TYPE::_3,			KEY::SEMICOLON);
	KeyCheck(GEARLINE_TYPE::_4,			KEY::QUOTATION);
	KeyCheck(GEARLINE_TYPE::RIGHTSIDE,	KEY::RSHIFT);


#pragma endregion

	// ��� ������ �������� üũ�ϴ� bool �� -> �� ���� ���� ó���� ���� �ʾ��� ��� ��� ������ ����.
	bool isEnd = true;

	for (auto& iter : m_vecNotePool)
	{
#pragma region _	JUDGE_CHECK
		
		// ���� �̹� ���� ó�� �� ��Ʈ��� ���� ó���� �������� ����.
		if (iter->isJudged == true) 
			continue;

		CNote* CurNote = iter->Note;
		// �⺻ ��Ʈ ���� ó��
		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{
			// Ű �Է� ���ο� ���� ���� ��Ʈ�� ������ �� �ð��� �̹� �Ѿ�� ���
			if (m_CurMusicTime > CurNote->m_fTapTime + 0.5f && !CURNOTE_KEYCHECK.isTap())
			{
				iter->isJudged = true;
				m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::BREAK);
				++m_vecJudge[JVI::BREAK];
				m_Combo->ComboBreak();
				m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::BREAK);
			}

			// 1. ������ ���� �ؽ��� ��� (ex - MAX 100%)		- �Ϸ�
			// 2. ���� �迭�� ������ �߰�						- �Ϸ�
			// 3. 350000 / 0.n ���� ���� ������Ű��			- ���⼭ ���� �� ���� �ƴ�.
			// 4. �ǹ� ������ ����(������ ����.)
			// 5. coolbomb ��� (�� �͵� ������ ����....)
			// 6. �޺� �� ����
			if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false)
			{
				if (JudgeCheck(JUDGE_PERCENT_CAL::_100, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_100];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_100);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), true);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_100);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_90, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_90];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_90);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), true);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_90);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_80, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_80];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_80);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_80);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_70, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_70];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_70);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_70);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_60, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_60];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_60);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_60);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_50, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_50];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_50);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_50);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_40, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_40];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_40);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_40);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_30, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_30];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_30);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_30);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_20, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_20];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_20);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_20);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_10, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_10];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_10);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Combo->ComboUp();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_10);
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_1, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_1];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::_1);
					m_CoolbombTexture->PlayCoolbombAnimation(CurNote->GetLineType(), false);
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::_1);
					}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_BREAK, JUDGECHECK_TAPTIME))/////// BREAK ����
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::BREAK];
					m_JudgeTexture->SetJudgeAnimation(JUDGE_VECTOR_IDX::BREAK);
					m_Combo->ComboBreak();
					m_Fever->FeverGaugeUp(JUDGE_VECTOR_IDX::BREAK);
				}
			}

		}
#pragma endregion
#pragma region _	POOL_CHANGE
		// �޸� Ǯ ��ü
		if (iter->isJudged)
		{
			isEnd = false;
			iter->isJudged = false;
			*(iter->Note) = GetNoteInfo();
		}
#pragma endregion
	} // ���� üũ ����
	std::sort(m_vecNotePool.begin(), m_vecNotePool.end(), compareNoteTapTime);
	

	// �÷��� ���� ���� ����
	if (isEnd)
	{
		// 1. ������ ���� Ŭ����, �ƽ� �޺�, ����Ʈ �÷��̸� ���
		// 2. fadeout
		// 3. ������ ��Ʈ �Է� ���� ����
		// 4. exit, score level enter
	}
}

void CGear_PlayLevel::render(HDC _dc)
{
	CGear::render(_dc);
}

#undef JUDGECHECK_TAPTIME
#undef GT