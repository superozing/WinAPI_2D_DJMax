#include "pch.h"
#include "CPanelUI.h"

#include "CAssetMgr.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:m_Panel(nullptr)
{
	// �ؽ�ó �߰� �� �Ʒ� ���� ����ϱ�.
	//m_Panel = CAssetMgr::GetInst()->LoadTexture(L"",L"");
}

CPanelUI::~CPanelUI()
{
}

// �巡�� �� ���
void CPanelUI::tick(float _DT)
{
	// LBtn Down �� ���콺 Pos �޾ƿͼ� ���� ���콺 Pos�� ���� ���콺 Pos Diff�� ��ǥ ����
	if (IsLBtnDown())
	{
		Vec2 vDiff = m_vLbtnDownPos - CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = GetPos();
		vPos -= vDiff;
		SetPos(vPos);
		m_vLbtnDownPos = CKeyMgr::GetInst()->GetMousePos(); // �񱳸� ���� �� ����
	}
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos(); // Panal UI�̱� ������ ���� render Pos�� ��ȯ �ȴ�.

	// ������ �г� �ؽ�ó�� �ִ°�?
	if (nullptr != m_Panel)
	{
		// ��� �̹� �ؽ�ó�� ������ ���� Scale ���� �޾ƿ� �ʿ䰡 ���� ������ else�� �־���.
		/*���⿡ �ؽ�ó ��� ������ �ۼ�*/
	}
	else // ���� ���� ���, �⺻ �簢�� �̹����� �����.
	{
		Vec2 vScale = GetScale();
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	

	// ������Ʈ render�� �ڽ�UI �� render ȣ��
	Super::render(_dc);
}

void CPanelUI::LBtnDown(Vec2 _MousePos)
{
	// �� �� ��ư�� ������ �� ���콺 ��ġ�� ���
	m_vLbtnDownPos = _MousePos;
}

