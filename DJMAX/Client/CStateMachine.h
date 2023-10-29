#pragma once
#include "CComponent.h"

class CState;

// FSM, Finite State Machine(유한 상태 기계)
class CStateMachine :
    public CComponent
{
private:
    // 해당 오브젝트의 State 저장
    map<UINT, CState*>  m_mapState;
    // 현재 State
    CState*             m_pCurState;

    // 칠판 - 필요한 기본적인 정보들 기록하는 것에 간이로 사용
    map<wstring, void*> m_mapBlackboard;


public:
    // State 추가
    void        AddState(UINT _id, CState* _State);

    // State 가져오기
    CState*     FindState(UINT _id);

    // State 변경
    void        ChangeState(UINT _NextID);

    // 칠판에 정보 추가
    template<typename T>
    void AddDataToBlackboard(const wstring& _strKey, const T& _Data);

    // 칠판에서 정보 가져오기
    void* GetDataFromBlackboard(const wstring _strKey);




public:
    virtual void finaltick(float _DT) override;


public:
    CLONE(CStateMachine);

    CStateMachine(CObj* _Owner);
    CStateMachine(const CStateMachine& _Origin);
    ~CStateMachine();
};

template<typename T>
inline void CStateMachine::AddDataToBlackboard(const wstring& _strKey, const T& _Data)
{
    map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
    if (iter != m_mapBlackboard.end())
    {
        LOG(LOG_LEVEL::ERR, L"!!블랙보드에 해당 데이터 키 이미 있음!!");
        return;
    }

    T* pData = new T;
    *pData = _Data;
    m_mapBlackboard.insert(make_pair(_strKey, pData));
}
