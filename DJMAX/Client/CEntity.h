#pragma once


class CEntity
{
	static UINT_PTR g_NextID;

protected:
	const UINT_PTR	m_ID;		// 고유 ID 값
	wstring			m_strName;	// 객체 이름
	bool			m_bDead;	// 객체 삭제시 Dead 여부 체크

public:
	UINT_PTR GetID() { return m_ID; }
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	bool IsDead() { return m_bDead; }

public:
	// 동일한 ID 값을 가진 특수한 객체 생성 시 사용할 것
	virtual CEntity* Clone() { return nullptr; } 

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();

	//friend class CTaskMgr;
	//friend class CObj;
};

