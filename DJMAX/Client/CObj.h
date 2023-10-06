#pragma once
#include "CEntity.h"

class CObj :
    public CEntity
{
virtual void Abstract() = 0;
protected:
	Vec2				m_Pos;			// 위치
	Vec2				m_Scale;		// 크기
	//vector<CComponent*>	m_vecComponent;
	
private:
	int					m_iLayerIdx;	// 자신이 레이어의 몇 번째 인덱스인지.
///////////////


public:
	//Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
	int Get_m_iLayerIdx() { return m_iLayerIdx; }

protected:
	// template <typename T>
	// T* AddComponent(const wstring& _strName = L"")

public:
	virtual void begin() {};
	virtual void tick() {};
	//virtual void finaltick() final;
	virtual void render(HDC _dc);

	// Destroy 함수

	// 충돌 이벤트

private:
	CObj();
	virtual ~CObj();
	
	//friend class CLevel;
	//friend class CTaskMgr;
};

