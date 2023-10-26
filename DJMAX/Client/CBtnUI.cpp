#include "pch.h"
#include "CBtnUI.h"

#include "CEngine.h"
#include "resource.h"

#include "CKeyMgr.h"

CBtnUI::CBtnUI()
	: m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_CallBackFunc(nullptr)
	, m_Inst(nullptr)
	, m_Delegate(nullptr)
{
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
	Vec2 vScale = GetScale();

	if (nullptr != m_CurImg)
	{
		/*���⿡ ���� ��µ� �̹��� ���� �ۼ�*/
	}
	else
	{
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	// �θ� Ŭ����(CUI) �����Լ� ȣ��(�ڽ� UI ������ render �� ȣ��)
	Super::render(_dc);
}


// ���콺�� ��ư ���� �ö��
void CBtnUI::OnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_HoverImg;
}

// ���콺�� ��ư ������ ���
void CBtnUI::OnUnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}

// ���콺�� ��ư ���� �ö�� �ִ� ������
void CBtnUI::MouseOn(Vec2 _vMousePos)
{
}

// ���콺 �� ���� ����
void CBtnUI::LBtnDown(Vec2 _vMousePos)
{
	m_CurImg = m_PressedImg;
}

// ���콺 �� ���� ������
void CBtnUI::LBtnUp(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}

// Dialog ���� ����


// ���콺�� �� ���� ��ư ���� �ö�� �ִ� ���¿��� ������ - Ŭ�� ����
void CBtnUI::LBtnClicked(Vec2 _vMousePos)
{
	// m_CallBackFunc ���� ��
	if (nullptr != m_CallBackFunc)
	{
		m_CallBackFunc();
	}

	// m_Delegate ���� ��
	if (nullptr != m_Inst && nullptr != m_Delegate)
	{
		(m_Inst->*m_Delegate)();
	}
}
