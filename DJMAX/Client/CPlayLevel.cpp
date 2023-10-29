#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"

void CPlayLevel::init()
{
	// 오브젝트 생성 예시
	//CPlayer* pPlayer = new CPlayer;
	//pPlayer->SetPos(Vec2(500.f, 200.f));
	//pPlayer->SetScale(Vec2(50.f, 50.f));
	//AddObject(PLAYER, pPlayer);

	// 카메라 설정 예시
	//Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	//vLookAt /= 2.f;
	//CCamera::GetInst()->SetLookAt(vLookAt);

	//충돌 설정 예시
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);


}

void CPlayLevel::enter()
{
	CCamera::GetInst()->FadeIn(0.3f);

	// 사운드 로딩 예시
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	//pSound->SetVolume(100);
	//pSound->SetPosition(45.f);
	//pSound->Play(true);
}

void CPlayLevel::exit()
{
	CCamera::GetInst()->FadeOut(0.3f);
	DeleteAllObjects();

}

void CPlayLevel::tick()
{
	CLevel::tick();
}
