#pragma once
#include "CEntity.h"
#include "CLayer.h"

class CLevel
	: public CEntity
{
private:
	CLayer* m_Layer[LAYER::END];

protected:
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	void AddObject(LAYER _LayerType, CObj* _Object);

	// 전체 삭제 *큰 연산*
	void DeleteAllObjects();

	// 특정 레이어만 삭제 *큰 연산*
	void DeleteObjectsByLayer(LAYER _Layer);

public:
	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);

	// 레벨이 소유하고 있는 모든 레이어(해당 레벨 전체)를 순회하면서 T 타입에 해당하는 객체를 찾아서 결과(인자로 들어온 _Out) 벡터에 담아준다.*큰 연산*
	template<typename T>
	void GetObjects(vector<T*>& _Out);

	// 레벨이 소유하고 있는 특정 레이어의 오브젝트 목록을 반환한다.
	const vector<CObj*>& GetObjects(LAYER _LayerType) { return m_Layer[_LayerType]->m_vecObjects; }

	CLayer* GetLayer(int LayerIdx)
	{
		assert(!(LayerIdx < 0 || LAYER::END <= LayerIdx));
		return m_Layer[LayerIdx];
	}

	// entity의 이름으로 객체 찾아내기 *큰 연산*
	CObj* FindObjectByName(const wstring& _Name);

public:
	CLONE_DISABLE(CLevel); // 레벨이 복제될 일 없도록 해요.
	CLevel();
	CLevel(const CLevel& _Origin) = delete;
	~CLevel();

	friend class CLevelMgr;
	friend class CTaskMgr;
};

template<typename T>
inline void CLevel::GetObjects(vector<T*>& _Out)
{
	for (UINT j = 0; j < LAYER::END; ++j)
	{
		for (size_t i = 0; i < m_Layer[j]->m_vecObjects.size(); ++i)
		{
			T* pObj = dynamic_cast<T*>(m_Layer[j]->m_vecObjects[i]);

			if (nullptr != pObj)
			{
				_Out.push_back(pObj);
			}
		}
	}
}
