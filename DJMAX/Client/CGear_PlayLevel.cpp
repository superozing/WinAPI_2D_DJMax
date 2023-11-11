#include "pch.h"
#include "CGear_PlayLevel.h"
#include "CPathMgr.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CNote.h"

// define
#define GT (ULONGLONG)GEARLINE_TYPE
#define JVI (ULONGLONG)JUDGE_VECTOR_IDX
#define JUDGECHECK_TAPTIME m_JudgeRange[m_JudgeRangeIdx], iter->Note->m_fTapTime
#define CURNOTE_KEYCHECK m_KeyCheck[(ULONG)CurNote->m_Line]

CGear_PlayLevel::CGear_PlayLevel(vector<int>& _vecJudge)
	:m_NoteInfoIdx(0) // 0������ ����Ű�� ��Ʈ�� ���ʴ�� �ű�鼭 �ʱ�ȭ
	,m_KeyCheck{}
	,m_JudgeRange{	41.67f,	20.83f, 10.42f	}
	,m_JudgeRangeIdx(0)
	,m_vecJudge(_vecJudge)
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
	if (	(m_CurMusicTime + ((float)_Percent * 0.01667) + (_JudgeMode / 1000) > _TapTime)
		&&  (m_CurMusicTime - ((float)_Percent * 0.01667) - (_JudgeMode / 1000) < _TapTime))
		return true;
	else
		return false;
}

enum class JUDGE_PERCENT_CAL;	// => 100%,90%....
enum class JUDGE_MODE;			// => �⺻, �ϵ�, �ƽ� ��������
enum class JUDGE_VECTOR_IDX;	// ���� �ε��� üũ�� �� ���, JVI�� ġȯ��

void CGear_PlayLevel::KeyCheck(GEARLINE_TYPE _line, KEY _key)
{
	m_KeyCheck[(ULONGLONG)_line].key_tap		= KEY_TAP(_key);
	m_KeyCheck[(ULONGLONG)_line].key_press		= KEY_PRESSED(_key);
	m_KeyCheck[(ULONGLONG)_line].key_release	= KEY_RELEASED(_key);
}

void CGear_PlayLevel::tick(float _DT)
{
	// Super tick
	CGear::tick(_DT);

#pragma region _	KEY_STATE_CHECK
	// Ű ���� ����
	// ��...�ڵ尡 �� �������� �� ���� �� ���� ����.....?????
	// �� ���̸��̸���
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
		if (iter->isJudged == true) { continue; }

		CNote* CurNote = iter->Note;
		// �⺻ ��Ʈ ���� ó��
		if (CurNote->m_eType == NOTE_TYPE::DEFAULT)
		{
			// ��Ʈ�� ������ �� �ð��� �̹� �Ѿ�� ���
			if (m_CurMusicTime > CurNote->m_fTapTime + 0.5f)
			{
				iter->isJudged = true;

				++m_vecJudge[JVI::BREAK];
			}

			// 1. ������ ���� �ؽ��� ��� (ex - MAX 100%)
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
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_90, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_90];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_80, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_80];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_70, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_70];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_60, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_60];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_50, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_50];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_40, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_40];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_30, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_30];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_20, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_20];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_10, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_10];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_1, JUDGECHECK_TAPTIME))
				{
					iter->isJudged = true;
					// ���� ó��
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::_1];
				}
				else if (JudgeCheck(JUDGE_PERCENT_CAL::_BREAK, JUDGECHECK_TAPTIME))/////// BREAK ����
				{
					iter->isJudged = true;
					CURNOTE_KEYCHECK.key_tap = false;
					++m_vecJudge[JVI::BREAK];

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