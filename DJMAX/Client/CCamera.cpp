#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	// 방향키로 카메라가 바라보고 있는 위치를 변경
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_vLookAt.x -= CAMERA_MOVE_SPEED * DT;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_vLookAt.x += CAMERA_MOVE_SPEED * DT;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		m_vLookAt.y -= CAMERA_MOVE_SPEED * DT;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		m_vLookAt.y += CAMERA_MOVE_SPEED * DT;
	}



	// 화면 해상도의 중심위치를 알아낸다.
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 해상도 중심과, 카메라가 현재 보고있는 좌표의 차이값을 구한다.
	m_vDiff = m_vLookAt - vCenter;
}
