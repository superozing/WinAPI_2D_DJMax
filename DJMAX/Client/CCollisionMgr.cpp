#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
{

}
CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	// tick ���� �浹 ó���� �� ���̾� ���� ó��
	for (UINT iRow = 0; iRow < 32; ++iRow)
	{
		for (UINT iCol = iRow; iCol < 32; ++iCol)
		{
			if (!(m_LayerCheck[iRow] & (1 << iCol)))
				continue;
			// �浹�� ó���ؾ� �� ���̾� �� ��� �浹 ó��
			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

// ���̾� ���� �浹�ϵ��� �Ͻʽÿ�
void CCollisionMgr::CheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}

	// 1�� <<�� �о üũ
	m_LayerCheck[row] |= (1 << col);
}

// ���̾� ���� �浹���� �ʵ��� �Ͻʽÿ�
void CCollisionMgr::UncheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}

	// 1�� <<�� �о üũ
	m_LayerCheck[row] &= ~(1 << col);
}

void CCollisionMgr::CollisionBtwLayer(LAYER _Left, LAYER _Right)
{
	// ���� ������ nullptr�̶�� (1�� �������̰ų� ���� �߻� ��) return
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (nullptr == pCurLevel)
		return;

	// �浹 �˻縦 ���ؼ� �ش� ���̾� ���� �浹ü�� �޾ƿ�
	const vector<CCollider*>& vecLeft = pCurLevel->GetLayer(_Left)->GetColliders();
	const vector<CCollider*>& vecRight = pCurLevel->GetLayer(_Right)->GetColliders();


	// ���� �ٸ� ���̾�� �浹 �˻�
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				COLLIDER_ID ID(vecLeft[i]->GetID(), vecRight[j]->GetID());

				map<COLLIDER_ID, bool>::iterator iter = m_mapID.find(ID);

				if (iter == m_mapID.end())
				{
					// �ش� �浹ü ���� �浹 �˻縦 ó�� ������
					m_mapID.insert(make_pair(ID, false));
					iter = m_mapID.find(ID);
				}


				// ���� �浹 ���̴�.
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					if (false == iter->second)
					{
						// �Ѵ� Dead ���°� �ƴ϶��
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							// ������ �浹�� ���� ����.
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}
					}

					else
					{
						// �������� �浹 ���̾���.
						// �� �� �ϳ� �̻� Dead ����
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{
							vecLeft[i]->EndOverlap(vecRight[j]);
							vecRight[j]->EndOverlap(vecLeft[i]);
						}
						else
						{
							vecLeft[i]->Overlap(vecRight[j]);
							vecRight[j]->Overlap(vecLeft[i]);
						}
					}
					iter->second = true;
				}

				// ���� �浹���� �ʰ� �ִ�.
				else
				{
					if (iter->second)
					{
						// �������� �浹�ϰ� �־���.
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}
					iter->second = false;
				}
			}
		}
	}

	// ���� ���̾� ������ �浹 �˻�
	else
	{

	}
}

bool CCollisionMgr::IsCollision(CCollider* _Left, CCollider* _Right)
{
	// �� �浹ü�� �����ִ°�?
	if (fabs(_Left->GetScale().x / 2.f + _Right->GetScale().x / 2.f) >= fabs(_Left->GetPos().x - _Right->GetPos().x)
		&& fabs(_Left->GetScale().y / 2.f + _Right->GetScale().y / 2.f) >= fabs(_Left->GetPos().y - _Right->GetPos().y))
	{
		return true;
	}

	return false;
}
