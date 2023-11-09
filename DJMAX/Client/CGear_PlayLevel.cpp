#include "pch.h"
#include "CGear_PlayLevel.h"
#include "CPathMgr.h"
#include "CNote.h"
#include "CLogMgr.h"

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

void CGear_PlayLevel::tick(float _DT)
{
	CGear::tick(_DT);
	bool isEnd = true;
	for (auto& iter : m_vecNotePool)
	{
		// 1. ���� üũ



		// ���� �̹� ���� �Ⱓ�� ������ ���
		if (m_CurMusicTime + 0.4167 > iter->Note->m_fTapTime && iter->isJudged == false)
		{
			iter->isJudged = true;
		}

		// 2. �޸� Ǯ üũ �� ���ο� ��Ʈ �����ͷ� ä�� �ֱ�
		if (iter->isJudged)
		{
			isEnd = false;
			if(m_NoteInfoIdx < m_vecNoteInfo.size())
			{
				iter->isJudged = false;
				*(iter->Note) = m_vecNoteInfo[m_NoteInfoIdx++];
			}
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

CGear_PlayLevel::CGear_PlayLevel()
	:m_NoteInfoIdx(0) // 0������ ����Ű�� ��Ʈ�� ���ʴ�� �ű�鼭 �ʱ�ȭ
	,m_KeyCheck{}
{
	// init NotePool
	m_vecNotePool.resize(POOL_MAX_SIZE);
}

CGear_PlayLevel::~CGear_PlayLevel()
{
	for (auto& iter : m_vecNotePool)
	{
		delete iter->Note;
	}
}
