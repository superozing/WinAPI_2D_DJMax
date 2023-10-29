#pragma once

/***********************************
*	func.h
* 
* 유효성 체크
*	CEntity를 상속받는 모든 파생 클래스 객체가 유효한지 체크
*	
*
*************************************/

Vec2 Rotate(Vec2 _vDir, float _angle);
bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2);

template<typename T>
bool IsValid(T*& _Entity)
{
	if (nullptr == _Entity)
	{
		return false;
	}

	if (_Entity->IsDead())
	{
		_Entity = nullptr;
		return false;
	}

	return true;
}

void ChangeLevel(LEVEL_TYPE _type);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _File);
