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

// GC
#define GARBAGE_MAX_SIZE 10

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

#define GENERATED_OBJECT(type) typedef type Super;\
							   virtual void Abstract() override {}

#define GAME_FOLDER MyGame

// Key
#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)


// Pen
#define DEBUG_RENDER CEngine::GetInst()->DebugRender()
#define SELECT_PEN(DC, TYPE) FSelectPen tempPenSelect(DC, TYPE)
#define SELECT_BRUSH(DC, hBrush) FSelectBrush tempBrushSelect(DC, hBrush)
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

enum PEN_TYPE
{
	GREEN_PEN,
	BLUE_PEN,
	RED_PEN,

	PEN_END,
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

enum TASK_TYPE
{
	// Param1 : Layer Type, Param2 : Object Adress
	CREATE_OBJECT,

	// Param1 : Object Adress
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,
};