#pragma once

class CLevel;
class CTexture;

class CEngine
{
	SINGLETON(CEngine);
private:
	HWND		m_hWnd;
	POINT		m_ptResolution;

	HDC			m_DC;
	CTexture*	m_SubTex;
	bool		m_bDebugRender;
	HPEN		m_arrPen[PEN_END];
	HBRUSH		m_ClearBrush;
public:
	HWND GetMainWind() { return m_hWnd; }
	HDC GetMainDC() { return m_DC; }
	POINT GetResolution() { return m_ptResolution; }

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[_type]; }
	HBRUSH GetBrush() { return m_ClearBrush; }
	
	bool DebugRender() { return m_bDebugRender; }
	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);


private:
	void CreateDefaultGDI();

public:
	void init(HWND _hWnd, POINT _ptResolution);
	void tick();
};

