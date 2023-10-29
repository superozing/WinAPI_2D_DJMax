#pragma once
#include "CEntity.h"

class CObj;
class CCollider;

class CLayer :
    public CEntity
{
private:
	vector<CObj*> 		m_vecObjects;
	vector<CCollider*>	m_vecCollider;

public:
	void begin();
	void tick(float _DT);
	void finaltick(float _DT);
	void render(HDC _dc);

	void clear() { m_vecCollider.clear(); }
	void AddObject(CObj* _Object) { m_vecObjects.push_back(_Object); }

	// 충돌체가 자신을 등록할 시 사용
	void RegisterCollider(CCollider* _Collider) { m_vecCollider.push_back(_Collider); }

	// 레이어의 모든 오브젝트를 참조하고 싶을 때 사용. GetLayer(레이어 명)->GetObjects()
	const vector<CObj*>& GetObjects() { return  m_vecObjects; }

	// 충돌 매니저에서 사용
	const vector<CCollider*>& GetColliders() { return m_vecCollider; }

	void DeleteAllObjects();


public:
	CLONE_DISABLE(CLayer); // 레이어가 복제될 일 없도록 해요.
	CLayer();
	CLayer(const CLayer& _Origin) = delete;
	~CLayer();

	friend class CLevel;
	friend class CUIMgr;
};

