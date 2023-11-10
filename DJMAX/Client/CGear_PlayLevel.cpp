#include "pch.h"
#include "CGear_PlayLevel.h"
#include "CPathMgr.h"
#include "CNote.h"
#include "CLogMgr.h"


CGear_PlayLevel::CGear_PlayLevel()
	:m_NoteInfoIdx(0) // 0������ ����Ű�� ��Ʈ�� ���ʴ�� �ű�鼭 �ʱ�ȭ
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


void CGear_PlayLevel::NoteRender(HDC _dc, float speed)
{
	// ��� Ǯ �����Ϳ� render ȣ��
	// ���� ���� ��� ��Ʈ render
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
enum class JUDGE_MODE;		// => �⺻, �ϵ�, �ƽ� ��������

#define JUDGECHECK_TAPTIME m_JudgeRange[m_JudgeRangeIdx], iter->Note->m_fTapTime
void CGear_PlayLevel::tick(float _DT)
{
	CGear::tick(_DT);
	bool isEnd = true;
	for (auto& iter : m_vecNotePool)
	{
		// 1. ���� üũ
		if (iter->isJudged == false)
		{
			if (iter->Note->m_eType == NOTE_TYPE::DEFAULT /*&& Ű �Էµ� ��츦 �Ǵ��� ���𰡰� �ʿ�.*/)
			{
				
				if		(JudgeCheck(JUDGE_PERCENT::_100, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					// ���� ����, �ǹ� ������
				}
				else if (JudgeCheck(JUDGE_PERCENT::_90, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_80, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_70, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_60, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_50, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_40, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_30, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_20, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_10, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				else if (JudgeCheck(JUDGE_PERCENT::_1, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
				}
				/////// BREAK ����
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




		// 2. �޸� Ǯ üũ �� ���ο� ��Ʈ �����ͷ� ä�� �ֱ�
		if (iter->isJudged)
		{
			isEnd = false;
			iter->isJudged = false;
			*(iter->Note) = GetNoteInfo();
		}
	}

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
