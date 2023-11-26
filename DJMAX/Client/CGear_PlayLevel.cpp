#include "pch.h"
#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CCombo.h"
#include "CCoolbomb.h"
#include "CFever.h"
#include "CGear_PlayLevel.h"
#include "CJudgeTexture.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLineShine.h"
#include "CLogMgr.h"
#include "CNote.h"
#include "CPathMgr.h"
#include "CPlayLevel.h"
#include "CSound.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CEffectAnim.h"

// define
#define GT (ULONGLONG)GEARLINE_TYPE
#define CURNOTE_KEYCHECK	m_KeyCheck[(ULONG)CurNote->m_Line]
#define TAP_TIME_OVER		m_CurMusicTime + m_DelayOffset > CurNote->m_fTapTime + 0.5f && !CURNOTE_KEYCHECK.isTap()
#define RELEASE_TIME_OVER		m_CurMusicTime + m_DelayOffset > CurNote->m_fReleasedTime + 0.3f && !CURNOTE_KEYCHECK.isRelease()

#define CUR_LONG_NOTE		arrJudge[(ULONG)CurNote->m_Line]

static int		minus = 1;
static float	EndBGLigth = .0f;

CGear_PlayLevel::CGear_PlayLevel(vector<int>* _vecJudge, CJudgeTexture* _JudgeTexture
	, CLineShine* _LineTexture, CCoolbomb* _CoolbombTexture
	, CCombo* _Combo, CFever* _Fever)
	: m_CurNoteInfoIdx(0) // 0������ ����Ű�� ��Ʈ�� ���ʴ�� �ű�鼭 �ʱ�ȭ
	, m_KeyCheck{}
	, m_JudgeRange{ 41.67f,	20.83f, 10.42f }
	, m_JudgeRangeIdx(0)
	, m_vecJudge(_vecJudge)
	, m_JudgeTexture(_JudgeTexture)
	, m_LineTexture(_LineTexture)
	, m_Coolbomb(_CoolbombTexture)
	, m_Combo(_Combo)
	, m_Fever(_Fever)
	, m_ClearSound(FINDSND(L"effect_GameClear"))
	, m_EndAtlas(FINDTEX(L"end_atlas"))
	, m_EndFlare(FINDTEX(L"flare_1"))
{
	// init NotePool
	m_vecNotePool.reserve(POOL_MAX_SIZE);

	for (int i = 0; i < POOL_MAX_SIZE; ++i)
	{
		sNote* newsNote = new sNote;
		m_vecNotePool.push_back(newsNote);
	}
	m_ClearSound->SetVolume(100);

	SetBPM(105.f);


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
	MUSICINFO* musicinfo = CLevelMgr::GetInst()->GetCurMusicInfo();

	wstring strNoteDataFolderPath = CPathMgr::GetContentPath();
	strNoteDataFolderPath += L"notedata\\";
	strNoteDataFolderPath += musicinfo->wstrMusicName;
	strNoteDataFolderPath += L".note";
	
	// ���� ����
	FILE* pFile = nullptr;
	
	if (_wfopen_s(&pFile, strNoteDataFolderPath.c_str(), L"rb"))
		LOG(LOG_LEVEL::ERR, L"���� ���⿡ �����߽��ϴ�..");

	// ��Ʈ ����
	size_t sizeBuf = 0;
	if (pFile)	
		fread(&sizeBuf, sizeof(size_t), 1, pFile);

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

void CGear_PlayLevel::GearInsideRender(HDC _dc, float speed)
{
	m_Fever->GearInsideRender(_dc);

	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0

	for (int i = 0; i < 4; ++i)
	{
		if (m_LineTexture->m_LineTex[i]->isRender)
		{
			m_blend.SourceConstantAlpha = m_LineTexture->m_LineTex[i]->alpha;
			POINT vImgScale = { (int)m_LineTexture->m_LineTex[i]->pShineTex->GetWidth(), (int)m_LineTexture->m_LineTex[i]->pShineTex->GetHeight() };
			AlphaBlend(_dc
				, 109 + 100 * i, 18
				, 100, 678
				, m_LineTexture->m_LineTex[i]->pShineTex->GetDC()
				, 0, 0
				, vImgScale.x, vImgScale.y
				, m_blend);
		}
	}
	// ��� Ǯ �����Ϳ� render ȣ��
	// ���� ���� ��� ��Ʈ render
	for (auto& iter : m_vecNotePool)
	{
		if (!iter->isJudged) 
			iter->Note->render(_dc, m_CurMusicTime, speed, m_DelayOffset);
	}


}

NoteInfo CGear_PlayLevel::GetNoteInfo()
{
	if (m_vecNoteInfo.size() > m_CurNoteInfoIdx)
		return m_vecNoteInfo[m_CurNoteInfoIdx++];
	else
		return NoteInfo();
}

float Judge[12] = { 1,2,3,4,5,6,7,8,9,10,15,20 };

JUDGE_VECTOR_IDX CGear_PlayLevel::JudgeCheck(float _TapTime)
{
	float judgeTime = abs(m_CurMusicTime + m_DelayOffset - _TapTime);
	float range = m_JudgeRange[m_JudgeRangeIdx] / 1000;
	float Per = m_JudgeRange[m_JudgeRangeIdx] / 1000;
	int i = 0;

	while(true)
	{
		if (judgeTime - (range + (Per * Judge[i])) < 0.f)
			break;

		++i;

		if (i == (int)JUDGE_VECTOR_IDX::END) 
			return JUDGE_VECTOR_IDX::END;
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
	m_vecJudge->operator[]((ULONGLONG)_Judge) += 1;

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

void CGear_PlayLevel::init()
{
	CGear::m_CurMusicTime = 0;
	minus = 0;
	EndBGLigth = 0.f;
	EndTextureRender = false;
	// �޸� Ǯ Ŭ����
	for (auto& iter : m_vecNotePool)
	{
		delete iter->Note;
		delete iter;
	}
	// ���� ���� Ŭ����
	for (int i = 0; i < 12; ++i)
	{
		m_vecJudge->operator[](i) = 0;
	}

	m_vecNoteInfo.clear();
	m_CurNoteInfoIdx = 0;
	m_vecNotePool.clear();
	// init NotePool
	m_vecNotePool.reserve(POOL_MAX_SIZE);

	for (int i = 0; i < POOL_MAX_SIZE; ++i)
	{
		sNote* newsNote = new sNote;
		m_vecNotePool.push_back(newsNote);
	}
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

	bool NoteChange = false;


	// �޸� Ǯ ���� �۾�
	for (auto& iter : m_vecNotePool)
	{
		
		// �������� ���� ���� ��Ʈ�� �����ͷ� �޾Ƴ���
		CNote* CurNote = iter->Note; 

		// ���� �̹� ���� ó�� �� ��Ʈ��� ���� ó���� �������� ����.
		if (iter->isJudged == true && iter->Note->m_fTapTime == 0.f)  
		{
			continue;
		}
		else
		{
			isEnd = false;
		}

		// �⺻ ��Ʈ ���� ó��
		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{

			// tap time�� ���� �ð� ������ ���� ���� ��� ���� Break ���� ó��
			if (TAP_TIME_OVER)
			{
				iter->isJudged = true;
				NoteChange = true;
				JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // ���� �۾�
			}

			else if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false)
			{
				// ���� üũ
				JUDGE_VECTOR_IDX Judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (Judge == JUDGE_VECTOR_IDX::END)	
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�

				iter->isJudged			 = true;	// ���� ó�� - �޸� Ǯ���� ���ο� �����͸� �޾ƿ��� ����
				NoteChange = true;
				CURNOTE_KEYCHECK.key_tap = false;	// ������ �������� �ٸ� ��Ʈ�� Ű �Է��� �˻����� �ʵ��� Ű �Է� ����
				JudgementOperation(Judge, CurNote); // ���� �۾�
			}
		}
		

		else if (CurNote->m_eType == NOTE_TYPE::LONG || CurNote->m_eType == NOTE_TYPE::SIDETRACK)
		{
			
			static LongNoteInfoBuffer arrJudge[(ULONGLONG)GEARLINE_TYPE::END] = { {0, false, (JUDGE_VECTOR_IDX)11},{0, false, (JUDGE_VECTOR_IDX)11},{0, false, (JUDGE_VECTOR_IDX)11}
																					, {0, false, (JUDGE_VECTOR_IDX)11}, {0, false, (JUDGE_VECTOR_IDX)11}, {0, false, (JUDGE_VECTOR_IDX)11} };

			// tap time�� ���� �ð� ������ ���� ���� ��� ���� Break ���� ó��
			if (TAP_TIME_OVER && !CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�

				iter->isJudged = true;
				NoteChange = true;
				CUR_LONG_NOTE.isJudging = false;
				JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // ���� �۾�
			}

			// release time�� ���� �ð� ������ ���� ���� ��� ���� 1% ���� ó��
			else if (RELEASE_TIME_OVER && CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�
				iter->isJudged = true;
				NoteChange = true;
				CUR_LONG_NOTE.isJudging = false;
				JudgementOperation(JUDGE_VECTOR_IDX::_1, CurNote); // ���� �۾�
			}

			else if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false && !CUR_LONG_NOTE.isJudging)
			{
				// ���� üũ
				CUR_LONG_NOTE.judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�

				iter->isJudged = true;	// ���� ó��
				CURNOTE_KEYCHECK.key_tap = false;	// ������ �������� �ٸ� ��Ʈ�� Ű �Է��� �˻����� �ʵ��� Ű �Է� ����
				CUR_LONG_NOTE.isJudging = true;
				JudgementOperation(CUR_LONG_NOTE.judge, CurNote); // ���� �۾�
			}

			else if (CURNOTE_KEYCHECK.isRelease() && iter->isJudged == false)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�
				iter->isJudged = true;	
				CURNOTE_KEYCHECK.key_tap = false;	// ������ �������� �ٸ� ��Ʈ�� Ű �Է��� �˻����� �ʵ��� Ű �Է� ����
				CUR_LONG_NOTE.isJudging = false;
				NoteChange = true;// ���� ó�� - �޸� Ǯ���� ���ο� �����͸� �޾ƿ��� ����
			}

			else if (CURNOTE_KEYCHECK.isPress() && iter->isJudged == false && CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // ���� ���� ���� ���� ��� ���� ��Ʈ �˻�

				iter->isJudged = true;	// ���� ó��
				CURNOTE_KEYCHECK.key_tap = false;	// ������ �������� �ٸ� ��Ʈ�� Ű �Է��� �˻����� �ʵ��� Ű �Է� ����
				CUR_LONG_NOTE.AccTime += _DT;

				if (CUR_LONG_NOTE.AccTime > 0.2f)
				{
					JudgementOperation(CUR_LONG_NOTE.judge, CurNote); // ���� �۾�
					CUR_LONG_NOTE.AccTime = 0;
				}
			}
		}
		
		if (iter->isJudged)// �޸� Ǯ ��ü
		{
			if (iter->Note->m_fTapTime == 0.f) 
				continue;

			if (NoteChange)
			{
				*(iter->Note) = GetNoteInfo();
				NoteChange = false;
			}

			if (iter->Note->m_fTapTime == 0.f)	
				iter->isJudged = true;

			else								
				iter->isJudged = false;
				
		}
	} // ���� üũ ����



	
	if (isEnd) // �÷��� ���� ���� ����
	{
		// 1. ������ ���� Ŭ����, �ƽ� �޺�, ����Ʈ �÷��̸� ���
		// 2. fadeout
		// 3. ������ ��Ʈ �Է� ���� ����
		// 4. exit, score level enter
		if (!EndTextureRender)
		{
			
			m_pMusic->Stop();
			m_ClearSound->Play(false);
			//m_Combo->StopComboRender();
			int result = 0;
			for (int i = 1; i < (ULONGLONG)JUDGE_VECTOR_IDX::END; ++i)
			{
				result += m_vecJudge->operator[](i);
			}


			if (!result)
			{
				playResult = PLAY_RESULT::PERFECT_PLAY;
			}
			else if (!m_vecJudge->operator[]((ULONGLONG)JUDGE_VECTOR_IDX::BREAK))
			{
				playResult = PLAY_RESULT::MAX_COMBO;
			}
			else
			{
				playResult = PLAY_RESULT::DEFAULT;
			}

			EndTextureRender = true;
		}

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


void CGear_PlayLevel::EndRender(HDC _dc)
{
	BLENDFUNCTION m_blend;
	m_blend.BlendOp = AC_SRC_OVER;
	m_blend.BlendFlags = 0;
	m_blend.AlphaFormat = AC_SRC_ALPHA; // 0

	if (EndTextureRender)
	{
		static float EndTexsizePercent = .0f;
		if (EndTexsizePercent == 100.f)
		{
			m_blend.SourceConstantAlpha = 255 * (EndBGLigth / 100) * minus;

			if (playResult != PLAY_RESULT::DEFAULT)
			{
				AlphaBlend(_dc
					, 0, 0
					, 1600, 900
					, m_EndFlare->GetDC()
					, 0, 0
					, 1920, 1080
					, m_blend);
			}


			EndBGLigth += 50.f * DT;

			if (EndBGLigth > 100.f)
			{
				EndBGLigth = 100.f;
				ChangeLevel(LEVEL_TYPE::SCORE_LEVEL);
			}
		}
		m_blend.SourceConstantAlpha = 255;

		if (playResult != PLAY_RESULT::DEFAULT)
		{
			AlphaBlend(_dc
				, 1050 - (325 * (EndTexsizePercent / 100)), 450 - (325 * (EndTexsizePercent / 100))
				, 650 * (EndTexsizePercent / 100), 650 * (EndTexsizePercent / 100)
				, m_EndAtlas->GetDC()
				, ((int)playResult) * 550, 0
				, 550, 550
				, m_blend);
		}


		if (EndTexsizePercent < 100.f)
		{
			EndTexsizePercent += 600.f * DT;

			if (EndTexsizePercent > 100.f)
				EndTexsizePercent = 100.f;
		}

	}
}

#undef GT
#undef CURNOTE_KEYCHECK
#undef TAP_TIME_OVER	