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
#define WClassName L"MyWindow"
#define WTitleName L"DJMAX"


// singleton 
#define SINGLETON(ClassType)\
public:\
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


