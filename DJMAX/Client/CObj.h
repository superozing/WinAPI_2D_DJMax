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

	// Destroy �Լ�

	// �浹 �̺�Ʈ

private:
	CObj();
	virtual ~CObj();
	
	//friend class CLevel;
	//friend class CTaskMgr;
};

