#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"


void CLevelMgr::init()
{
	// 레벨 생성 (이후 추가)
	m_pCurLevel = new CLevel;

	// 오브젝트 생성 후 벡터에 삽입

	// 플랫폼

	// 카메라 설정
	

	// 충돌 설정

	// 레벨 시작
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
