#pragma once

/***********************************
*	struct.h
* 
* Vec2(float ����)
*	������ �����ε� ����
* 
* FKeyData
*	Ű ���� ����, ���� ���� ����
* 
* (�������� ������Ʈ ����)
*	Object�κ��� �Ļ��� ���� ������Ʈ�� ����
* 
* FTask
*	���� ������ ���� ��
* 
* FSelectPen, Brush 
*	���ϴ� ��, �귯�ø� ���ڷ� DC�� �����ڿ� ������ �ٲپ� ��
* 
* FLog
*	log ���, �޼���, log ���� �ð�
*
*************************************/

struct Vec2
{
public:
	float x;
	float y;


public:
	// �Ÿ� �� �Լ�
	float Distance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	// ������ ���� (����)
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	// ���� ����ȭ (������ ���̸� 1�� ����)
	Vec2& Normalize()
	{
		float f = Length();
		
		assert(f);

		x /= f;
		y /= f;

		return *this;
	}

	// ������ �ΰ�?
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
