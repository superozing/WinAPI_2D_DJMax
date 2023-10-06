#pragma once

class CLevel;

class CEngine
{
	SINGLETON(CEngine);

private:
	HWND	m_hWnd;			// ���� �ڵ�
	POINT	m_ptResolution; // ȭ�� �԰�

	HDC		m_DC;			// ���� DC
	//HDC		m_SubDC;		// ���� DC(�̸� �׷�����)
	//HBITMAP	m_SubBitMap;	// ���� ��Ʈ��
	
	//bool	m_bDebugRender; 

	//HPEN	m_arrPen[PEN_END];

public:
	HWND	GetMainWind()	{ return m_hWnd; }
	HDC		GetMainDC()		{ return m_DC; }
	POINT	GetResolution() { return m_ptResolution; }

	//HPEN GetPen(PEN_TYPE _type) { return m_arrPen[_type]; }
	//bool DebugRender() { return m_bDebugRender; }

private:
	//void CreateDefaultGDI(); // �� ����

public:
	void init(HWND _hWnd, POINT _ptResolution);
	void tick();

};

