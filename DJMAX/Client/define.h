#pragma once

/***********************************
*	define.h
* 
* #define 
*	SINGLETON
* 		(객체 생성을 막음. GetInst를 사용해서만 객체에 접근 가능)
*	KEY_CHECK
* 
* enum
*	Key value(체크할 키 값)
*	Key state(해당 키의 현재 상태)
*	Layer(Level이 보유할 레이어 종류)
*	Task Type(TaskMgr가 처리할 업무의 종류)
*	Pen Type(펜 종류 - 충돌체를 시각화 할 때)
*	Log Level(로그의 위험도 표시)
* 
*************************************/

// constexpr
#define DEFINE constexpr auto 

// PI
DEFINE PI					= 3.14159265348979f;

// Window Title
DEFINE WCLASSNANE			= L"MyWindow";
DEFINE WTITLENAME			= L"DJMAX";

// GC
DEFINE GARBAGE_MAX_SIZE		= 10;

// Camera
DEFINE CAMERA_DEFAULT_SPEED = 200.f;

// DT, Frame Count
DEFINE MIN_DT				= (1.f / 30.f);
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

// GENERATED_OBJECT
#define GENERATED_OBJECT(type) typedef type Super;

// folder name
#define GAME_FOLDER DJMAX

// Key
#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key)		KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(Key, NONE)


// Pen
#define DEBUG_RENDER CEngine::GetInst()->DebugRender()
#define SELECT_PEN(DC, TYPE)		FSelectPen tempPenSelect(DC, TYPE)
#define SELECT_BRUSH(DC, hBrush)	FSelectBrush tempBrushSelect(DC, hBrush)

// Clone
#define CLONE(type)			virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}

// Asset
#define LOADTEX(LstrName, LstrPath) CAssetMgr::GetInst()->LoadTexture(LstrName, LstrPath)
#define LOADSND(LstrName, LstrPath) CAssetMgr::GetInst()->LoadSound(LstrName, LstrPath)
#define FINDTEX(LstrName)			CAssetMgr::GetInst()->FindTexture(LstrName)
#define FINDSND(LstrName)			CAssetMgr::GetInst()->FindSound(LstrName)


// gear, note value
DEFINE NOTE_MOVE_SECOND			= 200;
DEFINE GEAR_LINE_POS			= 625;
DEFINE NOTE_WIDTH				= 100;
DEFINE NOTE_HEIGHT				= 20;
DEFINE NOTE_SIDE_WIDTH			= 200;

// memory pool max size
DEFINE POOL_MAX_SIZE = 20;

///////////////


enum LAYER
{
	DEFAULT,
	BACK_GROUND,
	GEAR,
	SPEED,
	SHINE,
	COMBO,
	COOLBOMB,
	FEVER,
	EFFECT,
	JUDGE,
	PAUSE,

	WORLD_STATIC,

	UI = 30,
	ONTHEUI,
	END = 32,
};

enum SCORE_LAYER
{
	S_DEFAULT,
	S_BACK_GROUND,
	S_OBJECT,
	S_SCORE,
	S_ICON,

};

enum class LEVEL_TYPE
{
	START_LEVEL,
	EDITOR_LEVEL,
	SELECT_LEVEL,
	PLAY_LEVEL,
	SCORE_LEVEL,
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

	SEMICOLON,
	QUOTATION,

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

enum LOG_LEVEL
{
	LOG,
	WARNING,
	ERR,

};


////////////// Object enum class

// note
enum class NOTE_TYPE // 음... dinamic_cast 쓰기 싫어져서 만들었어요.
{
	DEFAULT,
	LONG,
	SIDETRACK
};

enum class GEARLINE_TYPE
{
	LEFTSIDE,
	_1,
	_2,
	_3,
	_4,
	RIGHTSIDE,
	END,
};


// 판정
enum class JUDGE_VECTOR_IDX
{
	_100,
	_90,
	_80,
	_70,
	_60,
	_50,
	_40,
	_30,
	_20,
	_10,
	_1,
	BREAK,
	END
};

enum class JUDGE_MODE
{
	DEfAULT = 0,
	HARD,
	MAX,

	END
};


enum class PLAY_RESULT
{
	MAX_COMBO,
	PERFECT_PLAY,
	DEFAULT,
};


enum class PLAY_RANK_IDX
{
	C,
	B,
	A,
	S,
	MAX_COMBO,
	PERFECT_PLAY,
	END,
};





//////////////////////
/// state
enum class ESTARTLEVEL_CHOICE_STATE
{
	MOUSE_ON,
	MOUSE_OFF,
};


