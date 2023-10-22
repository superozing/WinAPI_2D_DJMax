#pragma once
#include "CComponent.h"

/* 사용 예시
 * 애니메이터 컴포넌트 추가
CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link.bmp");
m_Animator = AddComponent<CAnimator>(L"Animator");

 * 애니메이션 생성
m_Animator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);	
m_Animator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 1);
m_Animator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->SaveAnimations(L"animdata");

 * File에서 애니메이션 데이터 불러오기
m_Animator->LoadAnimation(L"animdata\\IdleDown.txt");
m_Animator->LoadAnimation(L"animdata\\IdleLeft.txt");
m_Animator->LoadAnimation(L"animdata\\IdleRight.txt");
m_Animator->LoadAnimation(L"animdata\\IdleUp.txt");
m_Animator->LoadAnimation(L"animdata\\WalkDown.txt");
m_Animator->LoadAnimation(L"animdata\\WalkLeft.txt");
m_Animator->LoadAnimation(L"animdata\\WalkRight.txt");
m_Animator->LoadAnimation(L"animdata\\WalkUp.txt");

m_Animator->Play(L"WalkDown", true);

*/
class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    // Animator 가 보유하고 있는 Animation 목록, 탐색을 위해서 Map 으로 
    map<wstring, CAnim*> m_mapAnim;

    // 현재 재생중인 Animation
    CAnim* m_CurAnim;

    // 반복 재생 여부
    bool                 m_bRepeat;

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();


    // Animation 찾기
    CAnim* FindAnim(const wstring& _strName);

    // 애니메이션 생성
    void CreateAnimation(const wstring& _strName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize
        , Vec2 _vOffset, float _duration, int _MaxFrm);

    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);



public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    //CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();
};

