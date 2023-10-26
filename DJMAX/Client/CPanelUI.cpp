#include "pch.h"
#include "CPanelUI.h"

#include "CAssetMgr.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:m_Panel(nullptr)
{
	// 텍스처 추가 시 아래 구문 사용하기.
	//m_Panel = CAssetMgr::GetInst()->LoadTexture(L"",L"");
}

CPanelUI::~CPanelUI()
{
}

// 드래그 앤 드롭
void CPanelUI::tick(float _DT)
{
	// LBtn Down 시 마우스 Pos 받아와서 현재 마우스 Pos와 이전 마우스 Pos Diff로 좌표 세팅
	if (IsLBtnDown())
	{
		Vec2 vDiff = m_vLbtnDownPos - CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = GetPos();
		vPos -= vDiff;
		SetPos(vPos);
		m_vLbtnDownPos = CKeyMgr::GetInst()->GetMousePos(); // 비교를 위해 값 저장
	}
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos(); // Panal UI이기 때문에 실제 render Pos만 반환 된다.

	// 설정된 패널 텍스처가 있는가?
	if (nullptr != m_Panel)
	{
		// 사실 이미 텍스처가 있으면 위의 Scale 값을 받아올 필요가 없기 때문에 else에 넣어줌.
		/*여기에 텍스처 출력 구문을 작성*/
	}
	else // 만약 없을 경우, 기본 사각형 이미지를 출력함.
	{
		Vec2 vScale = GetScale();
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	

	// 컴포넌트 render와 자식UI 쪽 render 호출
	Super::render(_dc);
}

void CPanelUI::LBtnDown(Vec2 _MousePos)
{
	// 왼 쪽 버튼이 눌렸을 때 마우스 위치를 기록
	m_vLbtnDownPos = _MousePos;
}

