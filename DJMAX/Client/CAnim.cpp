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

// CAnimator->finaltick으로부터 호출
void CAnim::finaltick()
{
	// 끝이라면 finaltick을 수행하지 않음
	if (m_bFinish) 
		return;

	m_AccTime += DT;

	if (m_vecFrm[m_iCurFrm].Duration < m_AccTime)
	{
		m_AccTime = 0.f + (m_vecFrm[m_iCurFrm].Duration - m_AccTime); // 이전 프레임에서 넘어간 오차 만큼 다음 프레임에서 깎아요.

		// 애니메이션의 모든 프레임이 넘어갔을 경우 bFinish = true;
		if (m_vecFrm.size() - 1 <= m_iCurFrm)
		{
			m_bFinish = true;
		}
		else
		{
			// 계속 진행중이라면 다음 프레임으로 넘어가요.
			++m_iCurFrm;
		}
	}
}

void CAnim::render(HDC _dc)
{
	// 프레임 정보를 받아와요.
	const FFrame& frm = m_vecFrm[m_iCurFrm];

	// 소유주 위치에 그림 그리기 (GetRenderPos()를 통한 카메라 이동을 포함한 최종 render위치)
	// DJMax는 카메라 이동을 쓰지를 않는데 굳이 필요한가? 라는 생각이 드네요...
	// 나중에 vRenderPos를 아예 그냥 받은 값을 바로 돌려주는 함수로 구현해야겠음.
	// 이리저리 돌아다니며 고치기 힘들 것 같아요. 시간 나면 고치고.
	CObj* pOwnerObject = m_pAnimator->GetOwner();
	Vec2	vRenderPos = pOwnerObject->GetRenderPos();

	// TransparentBlt-> 원하는 이미지의 원하는 부분만 옮겨와요. 원하는 바탕 색(보통 마젠타)를 없애요.
	/*TransparentBlt(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
		, int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, m_Atlas->GetDC()
		, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, RGB(255, 0, 255));*/

	// AlphaBlend를 사용하기 위해서 대부분의 방식이 TranceparentBlt와 비슷하지만, 
	// 마지막 인자로 BLENDFUNCTION 객체를 넣어주어야 한다.
	// SourceConstantAlpha: 최종으로 조정할 알파 값
	// AlphaFormat: AC_SRC_ALPHA로 원본의 값을 따르거나 0을 넣어서 아예 안보이게 처리할 수 있다.
	//				다만, 안보이게 처리할 경우에는 바깥에 if문을 하나 넣어서 그냥 AlphaBlend를 사용하지 않는 것이 좋다.
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
		, int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, m_Atlas->GetDC()
		, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, blend);
}

// Load에서 새로 만들어지는 CAnim객체의 init이라고 보면 편해요.
void CAnim::Create(const wstring& _strName, CTexture* _Atlas, 
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
{
	// entity 이름 설정
	SetName(_strName);

	// Atlas 설정
	m_Atlas = _Atlas;

	// 미리 공간을 늘려놓아서 동적 할당 아끼기
	m_vecFrm.reserve(_MaxFrm);

	for (size_t i = 0; i < _MaxFrm; ++i)
	{
		FFrame frm = {};

		// 연속적으로 예쁘게 정렬된 구조에서는 이 방법이 통하겠는데, 연속적으로 정렬되지 않았을 경우에는 이 방법이 약간 골치아프겠는데요?
		// 해결책을 찾아야 해.
		frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * i, 0.f);
		frm.vCutSize = _vCutSize;
		frm.vOffset = _vOffset;
		frm.Duration = _Duration;

		m_vecFrm.push_back(frm);
	}
}

// 애니메이터에서 열 개수를 받는 버전
void CAnim::Create(const wstring& _strName, CTexture* _Atlas,
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm, int _row)
{
	// entity 이름 설정
	SetName(_strName);

	// Atlas 설정
	m_Atlas = _Atlas;

	// 미리 공간을 늘려놓아서 동적 할당 아끼기
	m_vecFrm.reserve(_MaxFrm);
	for (size_t i = 0,r = 0, c = 0; i < _MaxFrm; ++i, ++r)
	{
		if (r == _row)
		{
			r = 0;
			++c;
		}
		
		FFrame frm = {};
		// 연속적으로 예쁘게 정렬된 구조에서는 이 방법이 통하겠는데, 연속적으로 정렬되지 않았을 경우에는 이 방법이 약간 골치아프겠는데요?
		// 해결책을 찾아야 해.
		frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * r, _vCutSize.y * c);
		frm.vCutSize = _vCutSize;
		frm.vOffset = _vOffset;
		frm.Duration = _Duration;

		m_vecFrm.push_back(frm);
		
	}
}

// 저장 시에 파일을 직접 열어서 원하는 텍스트 파일 통해서 애니메이션 프레임 등을 직접 수정하면서 
// 수정시에 바로바로 변화를 볼 수 있도록 파일을 열었을 때 가독성 좋게 해주어요.
bool CAnim::Save(const wstring& _FilePath)
{
	// 파일* -> C 방식.
	// 강사님이 C 방식으로 하셨으니 나도 C 방식으로 할 거에요.
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(ERR, L"파일 열기 실패");
		return false;
	}

	// Animation 이름 저장
	fwprintf_s(pFile, L"[ANIM_NAME]\n");

	wstring strName = GetName();
	fwprintf_s(pFile, strName.c_str());
	fwprintf_s(pFile, L"\n\n");


	// 키, 경로
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

	// 프레임 데이터
	// 프레임 숫자
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());


	for (int i = 0; i < (int)m_vecFrm.size(); ++i)
	{
		// 프레임 정보 저장
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

	// 파일 열기에 실패할 경우
	if (nullptr == pFile)
	{
		LOG(ERR, L"파일 열기 실패");
		return false;
	}

	// Animation 이름 로드
	while (true)
	{
		wchar_t szRead[256] = {};
		// 읽어왔는데 시작부터 파일의 마지막이었다?
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
			int iFrameCount = 0;
			fwscanf_s(pFile, L"%d", &iFrameCount);
			m_vecFrm.resize(iFrameCount);

			int iCurFrame = 0;
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

					// 모든 프레임을 다 읽었을 경우
					if (iFrameCount - 1 <= iCurFrame)
						break;
				}
			}
		}
	}

	// 사용한 파일 포인터 닫기
	fclose(pFile);
	return true;
}
