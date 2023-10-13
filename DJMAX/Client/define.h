#pragma once

/***********************************
*	define.h
* 
* #define 
*	SINGLETON
* 		(��ü ������ ����. GetInst�� ����ؼ��� ��ü�� ���� ����)
*	KEY_CHECK
* 
* enum
*	Key value(üũ�� Ű ��)
*	Key state(�ش� Ű�� ���� ����)
*	Layer(Level�� ������ ���̾� ����)
*	Task Type(TaskMgr�� ó���� ������ ����)
*	Pen Type(�� ���� - �浹ü�� �ð�ȭ �� ��)
*	Log Level(�α��� ���赵 ǥ��)
* 
*************************************/

// Window Title
#define WCLASSNANE L"MyWindow"
#define WTITLENAME L"DJMAX"

// DT, Frame Count
#define MIN_DT (1.f / 60.f)
#define DT CTimeMgr::GetInst()->GetDeltaTime()

// singleton 
#define SINGLETON(ClassType) public:\
								static ClassType* GetInst()\
								{\
									static ClassType inst;\
									return &inst;\
								}\
							 public:\
								 ClassType* operator = (const ClassType& _Origin) = delete;\
							 private:\
								 ClassType();\
								 ClassType(const ClassType& _Origin) = delete;\
							 	 ~ClassType();

///////////////


enum LAYER
{
	DEFAULT,
	TILE,
	PLATFORM,
	NOTE,
	GEAR,
	EFECT,

	WORLD_STATIC,


	END = 32,
};


enum class LEVEL_TYPE
{
	START_LEVEL,
	PLAY_LEVEL,
	EDITOR_LEVEL,
	END,
};



// Key Value
enum KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	TAB,
	LSHIFT,
	RSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};


enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,

};