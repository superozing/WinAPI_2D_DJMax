#include "pch.h"
#include "CEngine.h"

// Manager
#include "manager.h"

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
	Manager::Init();

	// Default GDI Object ����
	//CreateDefaultGDI();
}

void CEngine::tick()
{
	// Manager Update
	Manager::UpdateTick();

	// debug render
	/*if (KEY_TAP(KEY::NUM8))
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	*/

	// Level
	Manager::LevelTick();
	Manager::LevelRender(m_SubDC);

	// Task
	Manager::TaskTick();
}

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}

// init���� �ʱ�ȭ ��
CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_DC(nullptr)
	, m_SubBitMap(nullptr)
	, m_bDebugRender(true)
	//, m_arrPen{}
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hWnd, m_DC);

	DeleteObject(m_SubBitMap);
	DeleteDC(m_SubDC);

	//for (UINT i = 0; i < PEN_END; ++i)
	//{
	//	DeleteObject(m_arrPen[i]);
	//}
}

