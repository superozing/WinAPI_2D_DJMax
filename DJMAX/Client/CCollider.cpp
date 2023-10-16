#include "pch.h"
#include "CCollider.h"
#include "CLayer.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

CCollider::CCollider(CObj* _Owner)
	:CComponent(_Owner)
	,m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

// tick ���� ��ġ ���� ���� ������Ʈ ��ġ ����
void CCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();

	m_vFinalPos = vOwnerPos + m_vOffsetPos;

	// ���� �����ִ� ���̾ �浹ü ����� ���ؼ� ���̾� ��������
	int iLayerIdx = GetOwner()->GetLayerIdx();
	assert(!(iLayerIdx < 0));
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);

	// ���!!!
	pCurLayer->RegisterCollider(this);

}

void CCollider::render(HDC _dc)
{
}

void CCollider::BeginOverlap(CCollider* _OtherCol)
{
}

void CCollider::Overlap(CCollider* _OtherCol)
{
}

void CCollider::EndOverlap(CCollider* _OtherCol)
{
}
