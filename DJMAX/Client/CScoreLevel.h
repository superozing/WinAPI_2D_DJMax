#pragma once
#include "CLevel.h"

class CSound;
class CPlayRank;
class CNumTexture;
class CMusicDifficult;

class CScoreLevel
	: public CLevel
{
private:
	vector<int>*	m_vecJudge;

	CSound*			m_ClearMusic;

	CPlayRank*	pPlayRank;

	CNumTexture* m_numTexArr[3];
	CNumTexture* m_JudgePercent;
	CNumTexture* m_TotalScore;

	CMusicDifficult* m_MusicDifficult;


private:
	void JudgeScoreEnter();

public: // Get, Set 함수

	vector<int>*	GetVecJudge()						{ return m_vecJudge; }
	void			SetVecJudge(vector<int>* _vecJudge) { m_vecJudge = _vecJudge; }
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

// 3. 에디터 레벨의 컨테이너 (벡터, 리스트) (컨테이너 이름을 특정하지 않게 하도록 해요.)
		// 자신의 기술 문서에 작성하면 본인의 자료로 쓸 수 있을 것.
// 4. tick()을 사용하지 않는 오브젝트의 처리
// 엔진 구조를 바꾸어야 함.
// 언리얼 예시)
// 언리얼 엔진은 지금 엔진이랑 구조가 많이 비슷함.
// tick()이 필요 없는 함수들은, bool값을 Obj쪽에 하나 두어서 틱을 사용하는 애들만 따로 모아놓기(컨테이너).
// 리듬게임에서는 별로 프레임이 증가하지 않기에 의미가 없다고 하네요.
// 5. 버튼 UI에 FSM 쓰기?
// 6. 파일 탐색기로부터 원하는 파일 가져오는 법..........
// 7. 마우스를 사용하지 않는 버튼 선택