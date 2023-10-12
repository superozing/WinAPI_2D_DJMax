#pragma once
#include "CEntity.h"

class CObj :
    public CEntity
{
virtual void Abstract() = 0;
protected:
	Vec2				m_Pos;			// ��ġ
	Vec2				m_Scale;		// ũ��
	//vector<CComponent*>	m_vecComponent;
	
private:
	int					m_iLayerIdx;	// �ڽ��� ���̾��� �� ��° �ε�������.


public:
	//Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
	int GetLayerIdx() { return m_iLayerIdx; }

protected:
	// template <typename T>
	// T* AddComponent(const wstring& _strName = L"")

public:
	virtual void begin() {};
	virtual void tick(float _DT);
	virtual void finaltick(float _DT) final;
	virtual void render(HDC _dc);

	// Destroy �Լ�
	//void Destroy();


	// �浹 �̺�Ʈ
	//virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	//virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	//virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
private:
	void SetDead();

public:
	CObj();
	virtual ~CObj();
	
	friend class CLevel;
	//friend class CTaskMgr;
};

