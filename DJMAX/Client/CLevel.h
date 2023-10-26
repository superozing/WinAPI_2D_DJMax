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
	void DeleteAllObjects();
	//void CreateTile(UINT _Row, UINT _Col);

public:
	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);

	// ������ �����ϰ� �ִ� ��� ���̾�(�ش� ���� ��ü)�� ��ȸ�ϸ鼭 T Ÿ�Կ� �ش��ϴ� ��ü�� ã�Ƽ� ���(���ڷ� ���� _Out) ���Ϳ� ����ش�.
	template<typename T>
	void GetObjects(vector<T*>& _Out);

	// ������ �����ϰ� �ִ� Ư�� ���̾��� ������Ʈ ����� ��ȯ�Ѵ�.
	const vector<CObj*>& GetObjects(LAYER _LayerType) { return m_Layer[_LayerType]->m_vecObjects; }

	CLayer* GetLayer(int LayerIdx)
	{
		assert(!(LayerIdx < 0 || LAYER::END <= LayerIdx));
		return m_Layer[LayerIdx];
	}

public:
	CLONE_DISABLE(CLevel); // ������ ������ �� ������ �ؿ�.
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
