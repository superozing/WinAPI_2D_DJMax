#pragma once

/***********************************
*	struct.h
* 
* Vec2(float 벡터)
*	연산자 오버로딩 구현
* 
* FKeyData
*	키 값과 상태, 이전 상태 저장
* 
* (여러가지 오브젝트 정보)
*	Object로부터 파생된 여러 오브젝트의 정보
* 
* FTask
*	업무 정보와 인자 들
* 
* FSelectPen, Brush 
*	원하는 펜, 브러시를 인자로 DC와 생성자에 넣으면 바꾸어 줌
* 
* FLog
*	log 경고도, 메세지, log 노출 시간
*
*************************************/

struct Vec2
{
public:
	float x;
	float y;


public:
	// 거리 비교 함수
	float Distance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	// 벡터의 길이 (빗변)
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	// 벡터 정규화 (벡터의 길이를 1로 만듦)
	Vec2& Normalize()
	{
		float f = Length();
		
		assert(f);

		x /= f;
		y /= f;

		return *this;
	}

	// 영벡터 인가?
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

public:// operator

	Vec2 operator + (Vec2 _Other) const
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}

	void operator += (Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	Vec2 operator + (float _f) const
	{
		return Vec2(x + _f, y + _f);
	}

	Vec2 operator += (float _f)
	{
		x += _f;
		y += _f;
	}


	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}


	Vec2 operator - (Vec2 _Other) const
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}

	Vec2 operator - (float _f) const
	{
		return Vec2(x - _f, y - _f);
	}



	Vec2 operator * (Vec2 _Other) const
	{
		return Vec2(x * _Other.x, y * _Other.y);
	}

	Vec2 operator * (float _f) const
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator / (Vec2 _Other) const
	{
		assert(_Other.x);
		assert(_Other.y);

		return Vec2(x / _Other.x, y / _Other.y);
	}

	Vec2 operator / (float _f) const
	{
		assert(_f);
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		assert(_f);

		x /= _f;
		y /= _f;
	}



public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};

struct FKeyData
{
	KEY			eKey;
	KEY_STATE	eState;
	bool		bPressed;
};

struct FTask
{
	TASK_TYPE Type;
	UINT_PTR  Param_1;
	UINT_PTR  Param_2;
};
