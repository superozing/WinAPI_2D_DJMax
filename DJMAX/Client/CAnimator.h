#pragma once
#include "CComponent.h"

/* ��� ����
 * �ִϸ����� ������Ʈ �߰�
CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link.bmp");
m_Animator = AddComponent<CAnimator>(L"Animator");

 * �ִϸ��̼� ����
m_Animator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
m_Animator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);	
m_Animator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 1);
m_Animator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
m_Animator->SaveAnimations(L"animdata");

 * File���� �ִϸ��̼� ������ �ҷ�����
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
    // Animator �� �����ϰ� �ִ� Animation ���, Ž���� ���ؼ� Map ���� 
    map<wstring, CAnim*> m_mapAnim;

    // ���� ������� Animation
    CAnim* m_CurAnim;

    // �ݺ� ��� ����
    bool                 m_bRepeat;

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();


    // Animation ã��
    CAnim* FindAnim(const wstring& _strName);

    // �ִϸ��̼� ����
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

