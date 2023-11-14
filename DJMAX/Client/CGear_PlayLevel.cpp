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
#define CURNOTE_KEYCHECK	m_KeyCheck[(ULONG)CurNote->m_Line]
#define TAP_TIME_OVER		m_CurMusicTime + m_DelayOffset > CurNote->m_fTapTime + 0.5f && !CURNOTE_KEYCHECK.isTap()

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
	, m_Coolbomb(_CoolbombTexture)
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
		if (!iter->isJudged) iter->Note->render(_dc, m_CurMusicTime, speed, m_DelayOffset);
	}
}

NoteInfo CGear_PlayLevel::GetNoteInfo()
{
	if (m_vecNoteInfo.size() > m_NoteInfoIdx)
		return m_vecNoteInfo[m_NoteInfoIdx++];
	else
		return NoteInfo();
}

//bool CGear_PlayLevel::isJudgeCheck(JUDGE_PERCENT_CAL _Percent, float _JudgeMode, float _TapTime)
//{
//	if (	(m_CurMusicTime + m_DelayOffset + ((float)_Percent * 0.03334) + (_JudgeMode / 1000) > _TapTime)
//		&&  (m_CurMusicTime + m_DelayOffset - ((float)_Percent * 0.03334) - (_JudgeMode / 1000) < _TapTime))
//		return true;
//	else
//		return false;
//}

float Judge[12] = { 1,2,3,4,5,6,7,8,9,10,15,20 };

JUDGE_VECTOR_IDX CGear_PlayLevel::JudgeCheck(float _TapTime)
{
	float judgeTime = abs(m_CurMusicTime + m_DelayOffset - _TapTime);
	float range = m_JudgeRange[m_JudgeRangeIdx] / 1000;
	float Per = 0.03334f;
	int i = 0;

	while(true)
	{
		if (judgeTime - (range + (Per * Judge[i])) < 0.f)
		{
			break;
		}
		++i;
		if (i == 13) return JUDGE_VECTOR_IDX::END;
	}
	return (JUDGE_VECTOR_IDX)i;
}

enum class JUDGE_MODE;			// => �⺻, �ϵ�, �ƽ� ��������
enum class JUDGE_VECTOR_IDX;	// ���� �ε��� üũ�� �� ���, JVI�� ġȯ

void CGear_PlayLevel::KeyCheck(GEARLINE_TYPE _line, KEY _key)
{
	// ���� ���
	m_KeyCheck[(ULONGLONG)_line].key_tap		= KEY_TAP(_key);
	m_KeyCheck[(ULONGLONG)_line].key_press		= KEY_PRESSED(_key);
	m_KeyCheck[(ULONGLONG)_line].key_release	= KEY_RELEASED(_key);

	if (m_KeyCheck[(ULONGLONG)_line].isTap()) 
	{
		m_LineTexture->SetShineOn(_line); // tap �� �ѱ�
	}
	if (m_KeyCheck[(ULONGLONG)_line].isRelease())
	{
		m_LineTexture->SetShineOff(_line); // release �� ����
	}

}

// ���� �۾�
void CGear_PlayLevel::JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote)
{
	// ���� ���
	++m_vecJudge[(ULONGLONG)_Judge];

	// ������ ���� �ؽ�Ʈ �̹��� ���
	m_JudgeTexture->SetJudgeAnimation(_Judge);

	// ������ ���� coolbomb �ִϸ��̼� ��� (Break �� return)
	m_Coolbomb->PlayCoolbombAnimation(CurNote->GetLineType(), _Judge); 

	// fever ������ ������ ���� ���� (Break �� FeverBreak()ȣ��)
	m_Fever->FeverGaugeUp(_Judge);

	// Combo ���� => fever�� ����� (Break �� ComboBreak()ȣ��)
	m_Combo->ComboUp(_Judge);
}


// sort()�� ����� callback ���� �Լ�
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


	// �������� �ٲٵ��� ���߿� �Ű��ֱ�
	if (KEY_TAP(_9))
	{
		SetDelayOffset(m_DelayOffset - 0.05f);
	}
	if (KEY_TAP(_0))
	{
		SetDelayOffset(m_DelayOffset + 0.05f);
	}
	 
#pragma endregion

	// ��� ������ �������� üũ�ϴ� bool �� -> �� ���� ���� ó���� ���� �ʾ��� ��� ��� ������ ����.
	bool isEnd = true;

	// �޸� Ǯ ���� �۾�
	for (auto& iter : m_vecNotePool)
	{
		// ���� �̹� ���� ó�� �� ��Ʈ��� ���� ó���� �������� ����.
		if (iter->isJudged == true)  
			continue;
		
		// �������� ���� ���� ��Ʈ�� �����ͷ� �޾Ƴ���
		CNote* CurNote = iter->Note; 

		// tap time�� ���� �ð� ������ ���� ���� ��� ���� Break ���� ó��
		if (TAP_TIME_OVER)
		{
			iter->isJudged = true;
			JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // ���� �۾�
		}

		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{
			if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false)
			{
				// ���� üũ
				JUDGE_VECTOR_IDX Judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (Judge == JUDGE_VECTOR_IDX::END)	
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�

				iter->isJudged			 = true;	// ���� ó�� - �޸� Ǯ���� ���ο� �����͸� �޾ƿ��� ����
				CURNOTE_KEYCHECK.key_tap = false;	// ������ �������� �ٸ� ��Ʈ�� Ű �Է��� �˻����� �ʵ��� Ű �Է� ����
				JudgementOperation(Judge, CurNote); // ���� �۾�
			}
		}
		
		if (iter->isJudged)// �޸� Ǯ ��ü
		{
			isEnd = false;
			iter->isJudged = false;
			*(iter->Note) = GetNoteInfo();
		}
	} // ���� üũ ����



	
	if (isEnd) // �÷��� ���� ���� ����
	{
		// 1. ������ ���� Ŭ����, �ƽ� �޺�, ����Ʈ �÷��̸� ���
		// 2. fadeout
		// 3. ������ ��Ʈ �Է� ���� ����
		// 4. exit, score level enter
	}
	else
	{
		// ������ �̷�������Ƿ� ����
		std::sort(m_vecNotePool.begin(), m_vecNotePool.end(), compareNoteTapTime);
	}
}

void CGear_PlayLevel::render(HDC _dc)
{
	CGear::render(_dc);
}

#undef GT
#undef CURNOTE_KEYCHECK
#undef TAP_TIME_OVER	