#pragma once
class CCamera
{
	SINGLETON(CCamera);
private:
	Vec2	m_vLookAt;
	Vec2	m_vDiff;

public:
	void tick();
	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }

	// ī�޶� �ٶ󺸰� �ִ� LookAt ������ �ػ� �߽���ġ�� ���̰� ��ŭ ���� ��ġ�� ������ ���ش�.
	// ī�޶� �ٶ󺸰� �ִ� ������ ��ü���� �ػ� ���η� ���� �� �ְ�,
	// ī�޶� ����ִ� ��ġ�� ��ü���� ȭ�鿡 ���� �� �ְ� �Ѵ�.

	// Real -> Render
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	
	// Render -> Real
	Vec2 GetRealPos(Vec2 _vRenderPos) { return m_vDiff + _vRenderPos; }
};

