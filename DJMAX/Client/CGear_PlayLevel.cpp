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
	:m_NoteInfoIdx(0) // 0번부터 가리키는 노트를 차례대로 옮기면서 초기화
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

	// GEARLINE_TYPE - 나와야 하는 라인
	fread(&m_Line, sizeof(GEARLINE_TYPE), 1, _pFile);

	// TapTime - tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)
	fread(&m_fTapTime, sizeof(float), 1, _pFile);

	// ReleasedTime - 누르기를 끝내는 시간(롱 노트, 사이드 트랙에서만 사용 가능)
	fread(&m_fReleasedTime, sizeof(float), 1, _pFile);

	return *this;
}

// 나중에 곡 선택하면 해당 곡 정보랑 연동되는 파일에서 데이터 읽어오면 될 듯.
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
		LOG(LOG_LEVEL::ERR, L"파일 열기에 실패했습니다..");

	// 노트 개수
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
	// 모든 풀 데이터에 render 호출
	// 벡터 안의 모든 노트 render
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

enum class JUDGE_MODE;			// => 기본, 하드, 맥스 판정범위
enum class JUDGE_VECTOR_IDX;	// 판정 인덱스 체크할 때 사용, JVI로 치환

void CGear_PlayLevel::KeyCheck(GEARLINE_TYPE _line, KEY _key)
{
	// 판정 기록
	m_KeyCheck[(ULONGLONG)_line].key_tap		= KEY_TAP(_key);
	m_KeyCheck[(ULONGLONG)_line].key_press		= KEY_PRESSED(_key);
	m_KeyCheck[(ULONGLONG)_line].key_release	= KEY_RELEASED(_key);

	if (m_KeyCheck[(ULONGLONG)_line].isTap()) 
	{
		m_LineTexture->SetShineOn(_line); // tap 시 켜기
	}
	if (m_KeyCheck[(ULONGLONG)_line].isRelease())
	{
		m_LineTexture->SetShineOff(_line); // release 시 끄기
	}

}

// 판정 작업
void CGear_PlayLevel::JudgementOperation(JUDGE_VECTOR_IDX _Judge, CNote* CurNote)
{
	// 판정 기록
	++m_vecJudge[(ULONGLONG)_Judge];

	// 판정에 따른 텍스트 이미지 출력
	m_JudgeTexture->SetJudgeAnimation(_Judge);

	// 판정에 따른 coolbomb 애니메이션 출력 (Break 시 return)
	m_Coolbomb->PlayCoolbombAnimation(CurNote->GetLineType(), _Judge); 

	// fever 게이지 판정에 따른 증가 (Break 시 FeverBreak()호출)
	m_Fever->FeverGaugeUp(_Judge);

	// Combo 증가 => fever에 비례함 (Break 시 ComboBreak()호출)
	m_Combo->ComboUp(_Judge);
}


// sort()에 사용할 callback 전용 함수
bool compareNoteTapTime(const sNote* a, const sNote* b) 
{
	return *a->Note < *b->Note;
}

void CGear_PlayLevel::tick(float _DT)
{
	// Super tick
	CGear::tick(_DT);

#pragma region _	KEY_STATE_CHECK
	// 키 상태 변경
	KeyCheck(GEARLINE_TYPE::LEFTSIDE,	KEY::LSHIFT);
	KeyCheck(GEARLINE_TYPE::_1,			KEY::A);
	KeyCheck(GEARLINE_TYPE::_2,			KEY::S);
	KeyCheck(GEARLINE_TYPE::_3,			KEY::SEMICOLON);
	KeyCheck(GEARLINE_TYPE::_4,			KEY::QUOTATION);
	KeyCheck(GEARLINE_TYPE::RIGHTSIDE,	KEY::RSHIFT);


	// 설정에서 바꾸도록 나중에 옮겨주기
	if (KEY_TAP(_9))
	{
		SetDelayOffset(m_DelayOffset - 0.05f);
	}
	if (KEY_TAP(_0))
	{
		SetDelayOffset(m_DelayOffset + 0.05f);
	}
	 
#pragma endregion

	// 모든 판정이 끝났는지 체크하는 bool 값 -> 한 번도 판정 처리를 하지 않았을 경우 모든 판정이 끝남.
	bool isEnd = true;

	// 메모리 풀 판정 작업
	for (auto& iter : m_vecNotePool)
	{
		// 만약 이미 판정 처리 된 노트라면 판정 처리를 수행하지 않음.
		if (iter->isJudged == true)  
			continue;
		
		// 가독성을 위해 현재 노트를 포인터로 받아놓기
		CNote* CurNote = iter->Note; 

		// tap time이 판정 시간 범위를 벗어 났을 경우 강제 Break 판정 처리
		if (TAP_TIME_OVER)
		{
			iter->isJudged = true;
			JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // 판정 작업
		}

		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{
			if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false)
			{
				// 판정 체크
				JUDGE_VECTOR_IDX Judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (Judge == JUDGE_VECTOR_IDX::END)	
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사

				iter->isJudged			 = true;	// 판정 처리 - 메모리 풀에서 새로운 데이터를 받아오기 위해
				CURNOTE_KEYCHECK.key_tap = false;	// 판정이 끝났으니 다른 노트가 키 입력을 검사하지 않도록 키 입력 해제
				JudgementOperation(Judge, CurNote); // 판정 작업
			}
		}
		
		if (iter->isJudged)// 메모리 풀 교체
		{
			isEnd = false;
			iter->isJudged = false;
			*(iter->Note) = GetNoteInfo();
		}
	} // 판정 체크 종료



	
	if (isEnd) // 플레이 레벨 종료 시점
	{
		// 1. 판정에 따라 클리어, 맥스 콤보, 퍼펙트 플레이를 출력
		// 2. fadeout
		// 3. 점수와 노트 입력 정보 저장
		// 4. exit, score level enter
	}
	else
	{
		// 판정이 이루어졌으므로 정렬
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