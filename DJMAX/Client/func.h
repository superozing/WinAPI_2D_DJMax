#pragma once

/***********************************
*	func.h
* 
* ��ȿ�� üũ
*	CEntity�� ��ӹ޴� ��� �Ļ� Ŭ���� ��ü�� ��ȿ���� üũ
*	
*
*************************************/

template<typename T>
bool IsValid(T*& _Entity)
{
	// �̹� ������ ��ü���
	if (nullptr == _Entity)
	{
		return false;
	}

	// Dead ������ ������Ʈ ���
	if (_Entity->IsDead())
	{
		// ������ ������Ʈ ���·� ����
		_Entity = nullptr;
		return false;
	}

	// �� �ƴ϶�� false
	return true;
}


// ���� ��ȯ => task => level mgr changeLevel()
void ChangeLevel(LEVEL_TYPE _type);