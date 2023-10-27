#pragma once
#include "CComponent.h"

class CState;

// FSM, Finite State Machine(유한 상태 기계)
class CStateMachine :
    public CComponent
{
private:
    map<UINT, CState*>  m_mapState;
    CState* m_pCurState;

    // 칠판 - 필요한 기본적인 정보들 기록하는 것에 간이로 사용
    map<wstring, void*> m_mapBlackboard;


public:
    // 상태
    void        AddState(UINT _id, CState* _State);
    CState*     FindState(UINT _id);
    void        ChangeState(UINT _NextID);

    template<typename T>
    void AddDataToBlackboard(const wstring& _strKey, const T& _Data);

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
