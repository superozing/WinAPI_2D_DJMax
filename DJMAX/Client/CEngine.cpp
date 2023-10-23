#include "pch.h"
#include "CEngine.h"
#include "CKeyMgr.h"

// Manager
//#include "manager.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CTaskMgr.h"
#include "CCollisionMgr.h"
#include "CGCMgr.h"
#include "CLogMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"

// 1. main hWnd, 2. resolution
void CEngine::init(HWND _hWnd, POINT _ptResolution)
{
	// 멤버 초기화
	m_hWnd			= _hWnd;
	m_ptResolution	= _ptResolution;

	// 창 설정
	SetWindowPos(m_hWnd, nullptr, 10, 10, m_ptResolution.x, m_ptResolution.y, 0);
	ShowWindow(m_hWnd, true);

	// DC:		device context
	// Bitmap:	핸들에 해당하는 윈도우 비트맵(그림 그릴 곳)
	m_DC = GetDC(m_hWnd); 

	// 추가 비트맵 버퍼
	m_SubBitMap = CreateCompatibleBitmap(m_DC, m_ptResolution.x, m_ptResolution.y);
	m_SubDC = CreateCompatibleDC(m_DC);
	
	// m_SubDC 가 m_SubBitmap 을 목적지로 지정하고, 원래 목적지로 지정하고 있던 BitMap 이 반환값으로 나오는데, 
	// 이걸 바로 DeleteObject 함수에 전달시켜서 삭제요청한다.
	DeleteObject((HBITMAP)SelectObject(m_SubDC, m_SubBitMap));

	// Manager Init
	//Manager::Init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::init();
	CLevelMgr::GetInst()->init();

	// Default GDI Object 생성
	CreateDefaultGDI();
}

void CEngine::tick()
{
	// Manager Update
	//Manager::UpdateTick();
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();

	// debug render
	if (KEY_TAP(KEY::NUM8))
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	

	//// Level
	//Manager::LevelTick();
	//Manager::LevelRender(m_SubDC);

	//// Task
	//Manager::TaskTick();

	// LevelMgr
	CLevelMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();
	//CUIMgr::GetInst()->tick();
	CLevelMgr::GetInst()->render(m_SubDC);

	// Task Execute
	CTaskMgr::GetInst()->tick();

	// CG
	CGCMgr::GetInst()->tick();
}

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateDefaultGDI()
{
	m_arrPen[RED_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 20, 20));
	m_arrPen[GREEN_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 255, 20));
	m_arrPen[BLUE_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 20, 255));
}

// init에서 초기화 함
CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_DC(nullptr)
	, m_SubBitMap(nullptr)
	, m_bDebugRender(true)
	, m_arrPen{}
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hWnd, m_DC);

	DeleteObject(m_SubBitMap);
	DeleteDC(m_SubDC);

	for (UINT i = 0; i < PEN_END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

