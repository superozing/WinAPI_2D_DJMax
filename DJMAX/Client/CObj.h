#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CCollider.h"

class CComponent;
class CCollider;
class CObj :
    public CEntity
{
virtual void Abstract() = 0;
private:
	Vec2				m_Pos;			// 위치
	Vec2				m_Scale;		// 크기
	vector<CComponent*>	m_vecComponent;
	
private:
	int					m_iLayerIdx;	// 자신이 레이어의 몇 번째 인덱스인지.


public:
	Vec2 GetPos() { return m_Pos; }
	Vec2 GetRenderPos() { return m_Pos; } // CCamera::GetInst()->GetRenderPos(m_Pos);

	Vec2 GetScale() { return m_Scale; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	int GetLayerIdx() { return m_iLayerIdx; }

protected:
	template<typename T>
	T* AddComponent(const wstring& _strName = L"")
	{
		T* pNewCom = new T(this);
		m_vecComponent.push_back(pNewCom);
		pNewCom->SetName(_strName);
		return pNewCom;
	}

public:
	virtual void begin() {};
	virtual void tick(float _DT);
	virtual void finaltick(float _DT) final;
	virtual void render(HDC _dc);

	// Destroy 함수
	void Destroy();


	// 충돌 이벤트
	virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
private:
	void SetDead();

public:
	CObj();
	virtual ~CObj();
	
	friend class CLevel;
	friend class CTaskMgr;
};

