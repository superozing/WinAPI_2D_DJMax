#pragma once

class CLevel;

class CEngine
{
	SINGLETON(CEngine);

private:
	HWND	m_hWnd;			// 메인 핸들
	POINT	m_ptResolution; // 화면 규격

	HDC		m_DC;			// 메인 DC
	//HDC		m_SubDC;		// 서브 DC(미리 그려놓을)
	//HBITMAP	m_SubBitMap;	// 서브 비트맵
	
	//bool	m_bDebugRender; 

	//HPEN	m_arrPen[PEN_END];

public:
	HWND	GetMainWind()	{ return m_hWnd; }
	HDC		GetMainDC()		{ return m_DC; }
	POINT	GetResolution() { return m_ptResolution; }

	//HPEN GetPen(PEN_TYPE _type) { return m_arrPen[_type]; }
	//bool DebugRender() { return m_bDebugRender; }

private:
	//void CreateDefaultGDI(); // 펜 세팅

public:
	void init(HWND _hWnd, POINT _ptResolution);
	void tick();

};

