#include "pch.h"
#include "CCollider.h"
#include "CLayer.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CObj.h"
#include "CCamera.h"

CCollider::CCollider(CObj* _Owner)
	:CComponent(_Owner)
	,m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

// tick 이후 위치 값에 따라서 컴포넌트 위치 조정
void CCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();

	m_vFinalPos = vOwnerPos + m_vOffsetPos;

	// 현재 속해있는 레이어에 충돌체 등록을 위해서 레이어 가져오기
	int iLayerIdx = GetOwner()->GetLayerIdx();
	assert(!(iLayerIdx < 0));
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);

	// 등록!!!
	pCurLayer->RegisterCollider(this);

}

void CCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);//m_vFinalPos;

	if (0 < m_iCollisionCount)
	{
		SELECT_PEN(_dc, RED_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SELECT_PEN(_dc, GREEN_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
}


void CCollider::BeginOverlap(CCollider* _OtherCol)
{
	++m_iCollisionCount;
	GetOwner()->BeginOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::Overlap(CCollider* _OtherCol)
{
	GetOwner()->Overlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::EndOverlap(CCollider* _OtherCol)
{
	--m_iCollisionCount;
	GetOwner()->EndOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}