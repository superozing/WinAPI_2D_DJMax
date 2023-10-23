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
	// ��� �ʱ�ȭ
	m_hWnd			= _hWnd;
	m_ptResolution	= _ptResolution;

	// â ����
	SetWindowPos(m_hWnd, nullptr, 10, 10, m_ptResolution.x, m_ptResolution.y, 0);
	ShowWindow(m_hWnd, true);

	// DC:		device context
	// Bitmap:	�ڵ鿡 �ش��ϴ� ������ ��Ʈ��(�׸� �׸� ��)
	m_DC = GetDC(m_hWnd); 

	// �߰� ��Ʈ�� ����
	m_SubBitMap = CreateCompatibleBitmap(m_DC, m_ptResolution.x, m_ptResolution.y);
	m_SubDC = CreateCompatibleDC(m_DC);
	
	// m_SubDC �� m_SubBitmap �� �������� �����ϰ�, ���� �������� �����ϰ� �ִ� BitMap �� ��ȯ������ �����µ�, 
	// �̰� �ٷ� DeleteObject �Լ��� ���޽��Ѽ� ������û�Ѵ�.
	DeleteObject((HBITMAP)SelectObject(m_SubDC, m_SubBitMap));

	// Manager Init
	//Manager::Init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::init();
	CLevelMgr::GetInst()->init();

	// Default GDI Object ����
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

// init���� �ʱ�ȭ ��
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

