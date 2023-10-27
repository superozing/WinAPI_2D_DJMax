#include "pch.h"
#include "CStateMachine.h"

#include "CState.h"
#include "CLogMgr.h"

CStateMachine::CStateMachine(CObj* _Owner)
	: CComponent(_Owner)
	, m_pCurState(nullptr)
{

}

CStateMachine::CStateMachine(const CStateMachine& _Origin)
	: CComponent(_Origin)
	, m_pCurState(nullptr)
{
	for (const auto& pair : _Origin.m_mapState)
	{
		CState* pClonedState = pair.second->Clone();
		pClonedState->m_pSM = this;
		m_mapState.insert(make_pair(pair.first, pClonedState));
	}

	if (nullptr != _Origin.m_pCurState)
	{
		UINT ID = _Origin.m_pCurState->GetStateID();
		map<UINT, CState*>::iterator iter = m_mapState.find(ID);
		if (iter != m_mapState.end())
		{
			m_pCurState = iter->second;
		}
	}
}

CStateMachine::~CStateMachine()
{
	for (const auto& pair : m_mapState)
	{
		delete pair.second;
	}

	for (const auto& pair : m_mapBlackboard)
	{
		delete pair.second;
	}
}

void CStateMachine::finaltick(float _DT)
{
	if (nullptr != m_pCurState)
	{
		m_pCurState->finaltick(_DT);
	}
}

void CStateMachine::AddState(UINT _id, CState* _State)
{
	CState* pFindState = FindState(_id);

	if (nullptr != pFindState)
	{
		LOG(LOG_LEVEL::ERR, L"!!이미 같은 아이디의 State 가 StateMachine 에 있음!!");
		return;
	}

	m_mapState.insert(make_pair(_id, _State));
	_State->m_pSM = this;
}

CState* CStateMachine::FindState(UINT _id)
{
	map<UINT, CState*>::iterator iter = m_mapState.find(_id);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CStateMachine::ChangeState(UINT _NextID)
{
	CState* pNextState = FindState(_NextID);

	if (nullptr == pNextState)
	{
		LOG(LOG_LEVEL::ERR, L"!!변경할 다음 상태가 없음!!");
		return;
	}

	// 기존 스테이트 마무리
	if (nullptr != m_pCurState)
	{
		m_pCurState->Exit();
	}

	// 새로운 스테이트를 현재 스테이트로 지정
	m_pCurState = pNextState;


	// 새로운 스테이트로 진입(초기작업 수행)
	m_pCurState->Enter();
}

void* CStateMachine::GetDataFromBlackboard(const wstring _strKey)
{
	map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
	if (iter == m_mapBlackboard.end())
	{
		LOG(LOG_LEVEL::ERR, L"!!블랙보드에 해당 키 데이터 없음!!");
		return nullptr;
	}
	return iter->second;
}
