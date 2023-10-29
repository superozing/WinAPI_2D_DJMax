#pragma once

class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
};

struct FCamEvent
{
	CAM_EFFECT	Type;
	float		AccTime;
	float		Duration;
};


class CCamera
{
	SINGLETON(CCamera);
private:
	Vec2				m_vLookAt;
	Vec2				m_vDiff;
	CTexture*			m_Veil; // FadeIn, FadeOut에 사용할 텍스쳐

	list<FCamEvent>		m_EventList; // pushFront를 위해서 앞에
	UINT				m_Alpha;



public:
	void tick();
	void render(HDC _dc);
	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }

	void FadeIn(float _time)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_IN;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		m_EventList.push_back(evnt);
	}

	void FadeOut(float _time)
	{
		FCamEvent evnt = {};
		evnt.Type = CAM_EFFECT::FADE_OUT;
		evnt.AccTime = 0.f;
		evnt.Duration = _time;
		m_EventList.push_back(evnt);
	}

	// 카메라가 바라보고 있는 LookAt 지점과 해상도 중심위치의 차이값 만큼 실제 위치에 보정을 해준다.
	// 카메라가 바라보고 있는 지점의 물체들이 해상도 내부로 들어올 수 있게,
	// 카메라가 찍고있는 위치의 물체들이 화면에 나올 수 있게 한다.
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return m_vDiff + _vRenderPos; }
};

