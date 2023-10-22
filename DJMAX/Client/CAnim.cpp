#include "pch.h"
#include "CAnim.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CLogMgr.h"
#include "CAssetMgr.h"

CAnim::CAnim()
	: m_pAnimator(nullptr)
	, m_Atlas(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)
	, m_AccTime(0.f)
{
}

CAnim::~CAnim()
{
}

// CAnimator->finaltick���κ��� ȣ��
void CAnim::finaltick()
{
	// ���̶�� finaltick�� �������� ����
	if (m_bFinish) 
		return;

	m_AccTime += DT;

	if (m_vecFrm[m_iCurFrm].Duration < m_AccTime)
	{
		m_AccTime = 0.f + (m_vecFrm[m_iCurFrm].Duration - m_AccTime); // ���� �����ӿ��� �Ѿ ���� ��ŭ ���� �����ӿ��� ��ƿ�.

		// �ִϸ��̼��� ��� �������� �Ѿ�� ��� bFinish = true;
		if (m_vecFrm.size() - 1 <= m_iCurFrm)
		{
			m_bFinish = true;
		}
		else
		{
			// ��� �������̶�� ���� ���������� �Ѿ��.
			++m_iCurFrm;
		}
	}
}

void CAnim::render(HDC _dc)
{
	// ������ ������ �޾ƿͿ�.
	const FFrame& frm = m_vecFrm[m_iCurFrm];

	// ������ ��ġ�� �׸� �׸��� (GetRenderPos()�� ���� ī�޶� �̵��� ������ ���� render��ġ)
	// DJMax�� ī�޶� �̵��� ������ �ʴµ� ���� �ʿ��Ѱ�? ��� ������ ��׿�...
	// ���߿� vRenderPos�� �ƿ� �׳� ���� ���� �ٷ� �����ִ� �Լ��� �����ؾ߰���.
	// �̸����� ���ƴٴϸ� ��ġ�� ���� �� ���ƿ�. �ð� ���� ��ġ��.
	CObj*	pOwnerObject = m_pAnimator->GetOwner();
	Vec2	vRenderPos	= pOwnerObject->GetRenderPos();

	// TransparentBlt-> ���ϴ� �̹����� ���ϴ� �κи� �ŰܿͿ�. ���ϴ� ���� ��(���� ����Ÿ)�� ���ֿ�.
	// ���� .png�� �޾ƿ��� �� �κ��� ��� ���� �� �𸣰���.
	TransparentBlt(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
		, int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, m_Atlas->GetDC()
		, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, RGB(255, 0, 255));
}

// Load���� ���� ��������� CAnim��ü�� init�̶�� ���� ���ؿ�.
void CAnim::Create(const wstring& _strName, CTexture* _Atlas, 
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
{
	// entity �̸� ����
	SetName(_strName);

	// Atlas ����
	m_Atlas = _Atlas;

	// �̸� ������ �÷����Ƽ� ���� �Ҵ� �Ƴ���
	m_vecFrm.reserve(_MaxFrm);

	for (size_t i = 0; i < _MaxFrm; ++i)
	{
		FFrame frm = {};

		// ���������� ���ڰ� ���ĵ� ���������� �� ����� ���ϰڴµ�, ���������� ���ĵ��� �ʾ��� ��쿡�� �� ����� �ణ ��ġ�����ڴµ���?
		// �ذ�å�� ã�ƾ� ��.
		frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * i, 0.f);
		frm.vCutSize = _vCutSize;
		frm.vOffset = _vOffset;
		frm.Duration = _Duration;

		m_vecFrm.push_back(frm);
	}
}


// ���� �ÿ� ������ ���� ��� ���ϴ� �ؽ�Ʈ ���� ���ؼ� �ִϸ��̼� ������ ���� ���� �����ϸ鼭 
// �����ÿ� �ٷιٷ� ��ȭ�� �� �� �ֵ��� ������ ������ �� ������ ���� ���־��.
bool CAnim::Save(const wstring& _FilePath)
{
	// ����* -> C ���.
	// ������� C ������� �ϼ����� ���� C ������� �� �ſ���.
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(ERR, L"���� ���� ����");
		return false;
	}

	// Animation �̸� ����
	fwprintf_s(pFile, L"[ANIM_NAME]\n");

	wstring strName = GetName();
	fwprintf_s(pFile, strName.c_str());
	fwprintf_s(pFile, L"\n\n");


	// Ű, ���
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	wstring strKey;
	wstring strRelativePath;

	if (IsValid(m_Atlas))
	{
		strKey = m_Atlas->GetKey();
		strRelativePath = m_Atlas->GetRelativePath();
	}

	fwprintf_s(pFile, strKey.c_str());
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, strRelativePath.c_str());
	fwprintf_s(pFile, L"\n\n");

	// ������ ������
	// ������ ����
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", m_vecFrm.size());


	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		// ������ ���� ����
		fwprintf_s(pFile, L"[FRAME_NUM]\n");
		fwprintf_s(pFile, L"%d\n", i);

		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		fwprintf_s(pFile, L"[CUT_SIZE]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vCutSize.x, m_vecFrm[i].vCutSize.y);

		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].Duration);
	}

	fclose(pFile);

	return true;
}

bool CAnim::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"r");

	// ���� ���⿡ ������ ���
	if (nullptr == pFile)
	{
		LOG(ERR, L"���� ���� ����");
		return false;
	}

	// Animation �̸� �ε�
	while (true)
	{
		wchar_t szRead[256] = {};
		// �о�Դµ� ���ۺ��� ������ �������̾���?
		if (EOF == fwscanf_s(pFile, L"%s", szRead, 256))
		{
			LOG(WARNING, L"Animation File is Empty");
			break;
		}

		if (!wcscmp(szRead, L"[ANIM_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szRead, 256);
			SetName(szRead);
		}
		else if (!wcscmp(szRead, L"[ATLAS_TEXTURE]"))
		{
			wstring strKey, strRelativePath;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strKey = szRead;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strRelativePath = szRead;

			m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
		}
		else if (!wcscmp(szRead, L"[FRAME_COUNT]"))
		{
			size_t iFrameCount = 0;
			fwscanf_s(pFile, L"%d", &iFrameCount);
			m_vecFrm.resize(iFrameCount);

			size_t iCurFrame = 0;
			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"[FRAME_NUM]"))
				{
					fwscanf_s(pFile, L"%d", &iCurFrame);
				}
				else if (!wcscmp(szRead, L"[LEFT_TOP]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.y);
				}
				else if (!wcscmp(szRead, L"[CUT_SIZE]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.y);
				}
				else if (!wcscmp(szRead, L"[OFFSET]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.y);
				}
				else if (!wcscmp(szRead, L"[DURATION]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].Duration);

					// ��� �������� �� �о��� ���
					if (iFrameCount - 1 <= iCurFrame)
						break;
				}
			}
		}
	}

	// ����� ���� ������ �ݱ�
	fclose(pFile);
	return true;
}
