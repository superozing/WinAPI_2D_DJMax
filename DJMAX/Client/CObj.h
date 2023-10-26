#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CCamera.h"

class CComponent;
class CCollider;
class CCamera;

class CObj :
    public CEntity
{
	// 오브젝트를 상속 받는 오브젝트 들이 알아야 하는 일.
	// 1. GENERATED_OBJECT()매크로 정의를 통헤 추상화 해제
	// 2. 부모 쪽의 tick, finaltick, render를 Super키워드를 사용해 실행시키기(컴포넌트 실행)
	// 3. 생성자에서 AddComponent("컴포넌트명")를 통한 컴포넌트 추가. AddComponent 내부에서 동적 할당을 자동으로 수행함.
	// 4. 생성자에서 멤버로 들고 있을 아틀라스나 텍스쳐를 에셋 매니저를 통해 불러옴.
	// 5. 애니메이터 컴포넌트 사용 시 render를 재정의 해도 의미 없음
	// 6. 멤버에 담고 멤버를 통한 수정을 추천
	// 7. CreateAnimation() 이후 LoadAnimation() 실행 가능
	// 8. LOG(); 매크로를 통해 문제가 있을 여지가 있는 곳에 로그를 띄우도록 설정
	// 9. Pos 수정 이후 SetPos로 다시 값 넣어주기 잊지 말기
	// 10. Begin이 필요한 오브젝트는 override 해서 재정의 후 사용하기
	// 11. 객체 생성 후 레이어에 넣을 때 알맞은 Layer인덱스 참조
	// 12. 움직임은 왠만해서 Movement component를 이용하기
	// 13. CLONE()을 통해서 복제 시 깊은 복사 동작 적용. CLONE_UNABLED()을 사용해서 복제를 막을 수 있음.

private:
	Vec2				m_Pos;			// 위치
	Vec2				m_Scale;		// 크기
	vector<CComponent*>	m_vecComponent; // 오브젝트가 소유하는 컴포넌트 들
	
private:
	int					m_iLayerIdx;	// 자신이 레이어의 몇 번째 인덱스인지.


public:
	Vec2 GetPos() { return m_Pos; }
	Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); } 

	Vec2 GetScale() { return m_Scale; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	int GetLayerIdx() { return m_iLayerIdx; }

protected:
	template<typename T>
	T* AddComponent(const wstring& _strName = L"")
	{
		T* pNewCom = new T(this);
		m_vecComponent.push_back(pNewCom);
		pNewCom->SetName(_strName);
		return pNewCom;
	}

public:
	virtual void begin() {};
	virtual void tick(float _DT);
	virtual void finaltick(float _DT) final;
	virtual void render(HDC _dc);

	// Destroy 함수
	void Destroy();


	// 충돌 이벤트
	virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
private:
	void SetDead();

public:
	// Clone(복사 생성자)을 사용하지 않는 순수가상함수가 정의된 부모 쪽에서 순수 가상 함수로 구현해야 하는 이유:
	// 만약 안한다면 Entity포인터로 반환될 뿐, 잘 작동하는데
	// 이 때 보통 CObj 자식 객체를 생성하고 Clone으로 받을 때 만약 CObj*라면 한 번 더 다이나믹 캐스트를 사용해야 함
	virtual CObj* Clone() = 0; // **추상 클래스 들은 명시적으로 Clone() = 0; 을 적어야 함**
	CObj();
	CObj(const CObj& _Origin);
	virtual ~CObj();
	
	friend class CLevel;
	friend class CTaskMgr;
};

