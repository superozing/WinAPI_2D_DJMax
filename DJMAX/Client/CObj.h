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
	// ������Ʈ�� ��� �޴� ������Ʈ ���� �˾ƾ� �ϴ� ��.
	// 1. GENERATED_OBJECT()��ũ�� ���Ǹ� ���� �߻�ȭ ����
	// 2. �θ� ���� tick, finaltick, render�� SuperŰ���带 ����� �����Ű��(������Ʈ ����)
	// 3. �����ڿ��� AddComponent("������Ʈ��")�� ���� ������Ʈ �߰�. AddComponent ���ο��� ���� �Ҵ��� �ڵ����� ������.
	// 4. �����ڿ��� ����� ��� ���� ��Ʋ�󽺳� �ؽ��ĸ� ���� �Ŵ����� ���� �ҷ���.
	// 5. �ִϸ����� ������Ʈ ��� �� render�� ������ �ص� �ǹ� ����
	// 6. ����� ��� ����� ���� ������ ��õ
	// 7. CreateAnimation() ���� LoadAnimation() ���� ����
	// 8. LOG(); ��ũ�θ� ���� ������ ���� ������ �ִ� ���� �α׸� ��쵵�� ����
	// 9. Pos ���� ���� SetPos�� �ٽ� �� �־��ֱ� ���� ����
	// 10. Begin�� �ʿ��� ������Ʈ�� override �ؼ� ������ �� ����ϱ�
	// 11. ��ü ���� �� ���̾ ���� �� �˸��� Layer�ε��� ����
	// 12. �������� �ظ��ؼ� Movement component�� �̿��ϱ�
	// 13. CLONE()�� ���ؼ� ���� �� ���� ���� ���� ����. CLONE_UNABLED()�� ����ؼ� ������ ���� �� ����.

private:
	Vec2				m_Pos;			// ��ġ
	Vec2				m_Scale;		// ũ��
	vector<CComponent*>	m_vecComponent; // ������Ʈ�� �����ϴ� ������Ʈ ��
	
private:
	int					m_iLayerIdx;	// �ڽ��� ���̾��� �� ��° �ε�������.


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

	// Destroy �Լ�
	void Destroy();


	// �浹 �̺�Ʈ
	virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
	virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
private:
	void SetDead();

public:
	// Clone(���� ������)�� ������� �ʴ� ���������Լ��� ���ǵ� �θ� �ʿ��� ���� ���� �Լ��� �����ؾ� �ϴ� ����:
	// ���� ���Ѵٸ� Entity�����ͷ� ��ȯ�� ��, �� �۵��ϴµ�
	// �� �� ���� CObj �ڽ� ��ü�� �����ϰ� Clone���� ���� �� ���� CObj*��� �� �� �� ���̳��� ĳ��Ʈ�� ����ؾ� ��
	virtual CObj* Clone() = 0; // **�߻� Ŭ���� ���� ��������� Clone() = 0; �� ����� ��**
	CObj();
	CObj(const CObj& _Origin);
	virtual ~CObj();
	
	friend class CLevel;
	friend class CTaskMgr;
};

