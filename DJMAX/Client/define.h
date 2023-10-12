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