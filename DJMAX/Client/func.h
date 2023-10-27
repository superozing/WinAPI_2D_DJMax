#pragma once

/***********************************
*	func.h
* 
* 유효성 체크
*	CEntity를 상속받는 모든 파생 클래스 객체가 유효한지 체크
*	
*
*************************************/

template<typename T>
bool IsValid(T*& _Entity)
{
	// 이미 삭제된 객체라면
	if (nullptr == _Entity)
	{
		return false;
	}

	// Dead 상태의 오브젝트 라면
	if (_Entity->IsDead())
	{
		// 삭제된 오브젝트 상태로 만듦
		_Entity = nullptr;
		return false;
	}

	// 다 아니라면 false
	return true;
}


// 레벨 전환 => task => level mgr changeLevel()
void ChangeLevel(LEVEL_TYPE _type);