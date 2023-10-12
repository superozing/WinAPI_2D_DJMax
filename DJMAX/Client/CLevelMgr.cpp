#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"


void CLevelMgr::init()
{
	// ���� ���� (���� �߰�)
	m_pCurLevel = new CLevel;

	// ������Ʈ ���� �� ���Ϳ� ����

	// �÷���

	// ī�޶� ����
	

	// �浹 ����

	// ���� ����
	m_pCurLevel->begin();

}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);

}

CLevelMgr::CLevelMgr()
	:m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
	}
}