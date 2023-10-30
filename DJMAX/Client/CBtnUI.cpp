#include "pch.h"
#include "CBtnUI.h"

#include "CEngine.h"
#include "resource.h"
#include "CTexture.h"

#include "CKeyMgr.h"

CBtnUI::CBtnUI()
	: m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_CallBackFunc(nullptr)
	, m_Inst(nullptr)
	, m_Delegate(nullptr)
	, m_blendFunc{}
{
	m_CurImg = m_NormalImg;
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}

CBtnUI::~CBtnUI()
{
}


void CBtnUI::tick(float _DT)
{


	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	if (nullptr != m_CurImg)
	{
		Vec2 vImgScale = Vec2((float)m_CurImg->GetWidth(), (float)m_CurImg->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(vPos.y)
			, int(vImgScale.x), int(vImgScale.y)
			, m_CurImg->GetDC()
			, 0 , 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}
	else
	{
		Vec2 vScale = GetScale();
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	// 부모 클래스(CUI) 렌더함수 호출(자식 UI 들한테 render 를 호출)
	Super::render(_dc);
}


// 마우스가 버튼 위로 올라옴
void CBtnUI::OnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_HoverImg;
}

// 마우스가 버튼 위에서 벗어남
void CBtnUI::OnUnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}

// 마우스가 버튼 위에 올라와 있는 상태임
void CBtnUI::MouseOn(Vec2 _vMousePos)
{
}

// 마우스 왼 쪽이 눌림
void CBtnUI::LBtnDown(Vec2 _vMousePos)
{
	m_CurImg = m_PressedImg;
}

// 마우스 왼 쪽이 떼어짐
void CBtnUI::LBtnUp(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}

// Dialog 전방 선언


// 마우스의 왼 쪽이 버튼 위에 올라와 있는 상태에서 떼어짐 - 클릭 상태
void CBtnUI::LBtnClicked(Vec2 _vMousePos)
{
	// m_CallBackFunc 세팅 시
	if (nullptr != m_CallBackFunc)
	{
		m_CallBackFunc();
	}

	// m_Delegate 세팅 시
	if (nullptr != m_Inst && nullptr != m_Delegate)
	{
		(m_Inst->*m_Delegate)();
	}
}
