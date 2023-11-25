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

public: // Get, Set �Լ�

	vector<int>*	GetVecJudge()						{ return m_vecJudge; }
	void			SetVecJudge(vector<int>* _vecJudge) { m_vecJudge = _vecJudge; }
private:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void tick() override;
};

// 3. ������ ������ �����̳� (����, ����Ʈ) (�����̳� �̸��� Ư������ �ʰ� �ϵ��� �ؿ�.)
		// �ڽ��� ��� ������ �ۼ��ϸ� ������ �ڷ�� �� �� ���� ��.
// 4. tick()�� ������� �ʴ� ������Ʈ�� ó��
// ���� ������ �ٲپ�� ��.
// �𸮾� ����)
// �𸮾� ������ ���� �����̶� ������ ���� �����.
// tick()�� �ʿ� ���� �Լ�����, bool���� Obj�ʿ� �ϳ� �ξ ƽ�� ����ϴ� �ֵ鸸 ���� ��Ƴ���(�����̳�).
// ������ӿ����� ���� �������� �������� �ʱ⿡ �ǹ̰� ���ٰ� �ϳ׿�.
// 5. ��ư UI�� FSM ����?
// 6. ���� Ž����κ��� ���ϴ� ���� �������� ��..........
// 7. ���콺�� ������� �ʴ� ��ư ����