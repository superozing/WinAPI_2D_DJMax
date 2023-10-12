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