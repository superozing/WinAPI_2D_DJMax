#pragma once


class CEntity;

class CGCMgr
{
	SINGLETON(CGCMgr)
private:
	vector<CEntity*>	m_Entity;

public:
	void AddEntity(CEntity* _Entity)
	{
		m_Entity.push_back(_Entity);
	}

public:
	void tick();

};

