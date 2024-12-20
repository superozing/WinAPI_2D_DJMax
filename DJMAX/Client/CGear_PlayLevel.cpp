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
	: m_CurNoteInfoIdx(0) // 0번부터 가리키는 노트를 차례대로 옮기면서 초기화
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
	MUSICINFO* musicinfo = CLevelMgr::GetInst()->GetCurMusicInfo();

	wstring strNoteDataFolderPath = CPathMgr::GetContentPath();
	strNoteDataFolderPath += L"notedata\\";
	strNoteDataFolderPath += musicinfo->wstrMusicName;
	strNoteDataFolderPath += L".note";
	
	// 파일 오픈
	FILE* pFile = nullptr;
	
	if (_wfopen_s(&pFile, strNoteDataFolderPath.c_str(), L"rb"))
		LOG(LOG_LEVEL::ERR, L"파일 열기에 실패했습니다..");

	// 노트 개수
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

//void CGear_PlayLevel::PlayMusic(int diff)
//{
//	m_IsMusicPlaying = true;
//	m_CurMusicTime += diff;
//
//	if (m_CurMusicTime < 0.f)
//	{
//		m_CurMusicTime = 0.f;
//	}
//	m_pMusic->SetPosition(m_CurMusicTime * 100.f / m_MaxMusicTime);
//}



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
	// 모든 풀 데이터에 render 호출
	// 벡터 안의 모든 노트 render
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

// 기본 범위에 곱해질 판정 배율 
float Judge[12] = { 1,2,3,4,5,6,7,8,9,10,15,20 };

JUDGE_VECTOR_IDX CGear_PlayLevel::JudgeCheck(float _NoteTapTime)
{
	// 노트 입력 시간과 음악 진행 시간의 오차
	float judgeTimeDiff = abs(m_CurMusicTime + m_DelayOffset - _NoteTapTime);

	// 난이도에 따른 판정 기본 범위
	float judgeRange = m_JudgeRange[m_JudgeRangeIdx] / 1000;

	int i = 0;
	for (; i < (UINT)JUDGE_VECTOR_IDX::END; ++i)
	{
		if (judgeTimeDiff < judgeRange + (Judge[i] * judgeRange))
			break;
	}

	// 계산한 판정을 enum으로 변환해 반환
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
	m_vecJudge->operator[]((ULONGLONG)_Judge) += 1;

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

void CGear_PlayLevel::init()
{
	CGear::m_CurMusicTime = 0;
	minus = 0;
	EndBGLigth = 0.f;
	EndTextureRender = false;
	// 메모리 풀 클리어
	for (auto& iter : m_vecNotePool)
	{
		delete iter->Note;
		delete iter;
	}
	// 판정 벡터 클리어
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

	bool NoteChange = false;


	// 메모리 풀 판정 작업
	for (auto& iter : m_vecNotePool)
	{
		
		// 가독성을 위해 현재 노트를 포인터로 받아놓기
		CNote* CurNote = iter->Note; 

		// 만약 이미 판정 처리 된 노트라면 판정 처리를 수행하지 않음.
		if (iter->isJudged == true && iter->Note->m_fTapTime == 0.f)  
		{
			continue;
		}
		else
		{
			isEnd = false;
		}

		// 기본 노트 판정 처리
		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{

			// tap time이 판정 시간 범위를 벗어 났을 경우 강제 Break 판정 처리
			if (TAP_TIME_OVER)
			{
				iter->isJudged = true;
				NoteChange = true;
				JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // 판정 작업
			}

			else if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false)
			{
				// 판정 체크
				JUDGE_VECTOR_IDX Judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (Judge == JUDGE_VECTOR_IDX::END)	
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사

				iter->isJudged			 = true;	// 판정 처리 - 메모리 풀에서 새로운 데이터를 받아오기 위해
				NoteChange = true;
				CURNOTE_KEYCHECK.key_tap = false;	// 판정이 끝났으니 다른 노트가 키 입력을 검사하지 않도록 키 입력 해제
				JudgementOperation(Judge, CurNote); // 판정 작업
			}
		}
		

		else if (CurNote->m_eType == NOTE_TYPE::LONG || CurNote->m_eType == NOTE_TYPE::SIDETRACK)
		{
			
			static LongNoteInfoBuffer arrJudge[(ULONGLONG)GEARLINE_TYPE::END] = { {0, false, (JUDGE_VECTOR_IDX)11},{0, false, (JUDGE_VECTOR_IDX)11},{0, false, (JUDGE_VECTOR_IDX)11}
																					, {0, false, (JUDGE_VECTOR_IDX)11}, {0, false, (JUDGE_VECTOR_IDX)11}, {0, false, (JUDGE_VECTOR_IDX)11} };

			// tap time이 판정 시간 범위를 벗어 났을 경우 강제 Break 판정 처리
			if (TAP_TIME_OVER && !CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사

				iter->isJudged = true;
				NoteChange = true;
				CUR_LONG_NOTE.isJudging = false;
				JudgementOperation(JUDGE_VECTOR_IDX::BREAK, CurNote); // 판정 작업
			}

			// release time이 판정 시간 범위를 벗어 났을 경우 강제 1% 판정 처리
			else if (RELEASE_TIME_OVER && CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사
				iter->isJudged = true;
				NoteChange = true;
				CUR_LONG_NOTE.isJudging = false;
				JudgementOperation(JUDGE_VECTOR_IDX::_1, CurNote); // 판정 작업
			}

			else if (CURNOTE_KEYCHECK.isTap() && iter->isJudged == false && !CUR_LONG_NOTE.isJudging)
			{
				// 판정 체크
				CUR_LONG_NOTE.judge = JudgeCheck(CurNote->GetNoteTapTime());

				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사

				iter->isJudged = true;	// 판정 처리
				CURNOTE_KEYCHECK.key_tap = false;	// 판정이 끝났으니 다른 노트가 키 입력을 검사하지 않도록 키 입력 해제
				CUR_LONG_NOTE.isJudging = true;
				JudgementOperation(CUR_LONG_NOTE.judge, CurNote); // 판정 작업
			}

			else if (CURNOTE_KEYCHECK.isRelease() && iter->isJudged == false)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사
				iter->isJudged = true;	
				CURNOTE_KEYCHECK.key_tap = false;	// 판정이 끝났으니 다른 노트가 키 입력을 검사하지 않도록 키 입력 해제
				CUR_LONG_NOTE.isJudging = false;
				NoteChange = true;// 판정 처리 - 메모리 풀에서 새로운 데이터를 받아오기 위해
			}

			else if (CURNOTE_KEYCHECK.isPress() && iter->isJudged == false && CUR_LONG_NOTE.isJudging)
			{
				if (CUR_LONG_NOTE.judge == JUDGE_VECTOR_IDX::END)
					continue; // 판정 범위 내에 없을 경우 다음 노트 검사

				iter->isJudged = true;	// 판정 처리
				CURNOTE_KEYCHECK.key_tap = false;	// 판정이 끝났으니 다른 노트가 키 입력을 검사하지 않도록 키 입력 해제
				CUR_LONG_NOTE.AccTime += _DT;

				if (CUR_LONG_NOTE.AccTime > 0.2f)
				{
					JudgementOperation(CUR_LONG_NOTE.judge, CurNote); // 판정 작업
					CUR_LONG_NOTE.AccTime = 0;
				}
			}
		}
		
		if (iter->isJudged)// 메모리 풀 교체
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
	} // 판정 체크 종료



	
	if (isEnd) // 플레이 레벨 종료 시점
	{
		// 1. 판정에 따라 클리어, 맥스 콤보, 퍼펙트 플레이를 출력
		// 2. fadeout
		// 3. 점수와 노트 입력 정보 저장
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
		// 판정이 이루어졌으므로 정렬
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