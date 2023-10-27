#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUI::CUI()
	: m_ParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bMouseOn_Prev(false)
	, m_bMouseLBtnDown(false)
{
}

// 복사 생성자 (Clone()함수)
CUI::CUI(const CUI& _Origin)
	: CObj(_Origin)
	, m_ParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bMouseOn_Prev(false)
	, m_bMouseLBtnDown(false)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i)
	{
		// 자식 UI 복제, 부모 설정, 벡터에 넣기
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::tick(float _DT)
{
	Super::tick(_DT); // 컴포넌트 틱

	m_vFinalPos = GetPos(); // UI는 카메라의 영향을 받지 않고 화면에 머물러 있음.

	// 최종 좌표 연산(최상위 UI라면 offset 값이 아닌 실제 화면 상의 render 위치가 pos에 들어있겠죠?
	if (nullptr != m_ParentUI)
	{
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}

	// 마우스 정보 갱신
	m_bMouseOn_Prev = m_bMouseOn;
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos(); // 키 매니저로부터 값 받아오기

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + GetScale().x		// x값이 UI의 범위 내에 들어와있는가?
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + GetScale().y)	// y값이 UI의 범위 내에 들어와있는가?
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	// 자식 UI tick 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick(_DT);
	}
}

void CUI::render(HDC _dc)
{
	// components render
	Super::render(_dc);

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		// child UI render
		m_vecChildUI[i]->render(_dc);
	}
}

