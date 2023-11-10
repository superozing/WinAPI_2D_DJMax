#include "pch.h"
#include "CGear_PlayLevel.h"
#include "CPathMgr.h"
#include "CNote.h"
#include "CLogMgr.h"


CGear_PlayLevel::CGear_PlayLevel()
	:m_NoteInfoIdx(0) // 0번부터 가리키는 노트를 차례대로 옮기면서 초기화
	,m_KeyCheck{}
	,m_JudgeRange
		{	
			41.67f,
			20.83f, 
			10.42f
		}
	,m_JudgeRangeIdx(0)
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


void CGear_PlayLevel::NoteRender(HDC _dc, float speed)
{
	// 모든 풀 데이터에 render 호출
	// 벡터 안의 모든 노트 render
	for (auto& iter : m_vecNotePool)
	{
		if (!iter->isJudged)
			iter->Note->render(_dc, m_CurMusicTime, speed);
	}
}

NoteInfo CGear_PlayLevel::GetNoteInfo()
{
	if (m_vecNoteInfo.size() > m_NoteInfoIdx)
		return m_vecNoteInfo[m_NoteInfoIdx++];
	else
		return NoteInfo();
}

bool CGear_PlayLevel::JudgeCheck(JUDGE_PERCENT _Percent, float _JudgeMode, float _TapTime)
{
	if ((m_CurMusicTime + float((int)_Percent * _JudgeMode / 1000) > _TapTime)
		&& (m_CurMusicTime - float((int)_Percent * _JudgeMode / 1000) < _TapTime))
		return true;
	else
		return false;
}

enum class JUDGE_PERCENT;	// => 100%,90%....
enum class JUDGE_MODE;		// => 기본, 하드, 맥스 판정범위

#define JUDGECHECK_TAPTIME m_JudgeRange[m_JudgeRangeIdx], iter->Note->m_fTapTime
void CGear_PlayLevel::tick(float _DT)
{
	CGear::tick(_DT);
	bool isEnd = true;
	for (auto& iter : m_vecNotePool)
	{
		// 1. 판정 체크
		if (iter->isJudged == false)
		{
			if (iter->Note->m_eType == NOTE_TYPE::DEFAULT /*&& 키 입력된 경우를 판단할 무언가가 필요.*/)
			{
				
				if		(JudgeCheck(JUDGE_PERCENT::_100, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
					// 점수 증가, 피버 게이지
				}
				else if (JudgeCheck(JUDGE_PERCENT::_90, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_80, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_70, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_60, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_50, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_40, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_30, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_20, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_10, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				else if (JudgeCheck(JUDGE_PERCENT::_1, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// 판정 처리
				}
				/////// BREAK 판정
				else if (JudgeCheck(JUDGE_PERCENT::_BREAK, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;

				}
				else if (m_CurMusicTime > iter->Note->m_fTapTime + 1)
				{
					iter->isJudged = true;

				}
			}
			
		}




		// 2. 메모리 풀 체크 후 새로운 노트 데이터로 채워 넣기
		if (iter->isJudged)
		{
			isEnd = false;
			iter->isJudged = false;
			*(iter->Note) = GetNoteInfo();
		}
	}

	if (isEnd)
	{
		// 1. 판정에 따라 클리어, 맥스 콤보, 퍼펙트 플레이를 출력
		// 2. fadeout
		// 3. 점수와 노트 입력 정보 저장
		// 4. exit, score level enter
	}
}

void CGear_PlayLevel::render(HDC _dc)
{
	CGear::render(_dc);
}
