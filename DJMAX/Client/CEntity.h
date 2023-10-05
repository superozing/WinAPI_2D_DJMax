#pragma once


class CEntity
{
	static UINT_PTR g_NextID;

protected:
	const UINT_PTR	m_ID;		// ���� ID ��
	wstring			m_strName;	// ��ü �̸�
	//bool			m_bDead;	// ��ü ������ Dead ���� üũ

public:
	// ������ ID ���� ���� Ư���� ��ü ���� �� ����� ��
	virtual CEntity* Clone() { return nullptr; } 

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();

	//friend class CTaskMgr;
	//friend class CObj;
};

