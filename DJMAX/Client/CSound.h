#pragma once

#include "CAsset.h"


class CSound
	: public CAsset
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;

public:
	virtual bool Load(const wstring& _strFilePath) override;

	// 사운드 재생
	void Play(bool _bLoop = false);

	// 배경음악으로 재생
	void PlayToBGM(bool _bLoop = false);

	// 정지
	void Stop(bool _bReset = false);

	// 볼륨 설정 (0 ~ 100)
	void SetVolume(float _fVolume);

	// 사운드 재생 위치 (0 ~ 100)
	void SetPosition(float _fPosition); // 0 ~ 100 

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);

public:
	// 사운드 파일의 길이 반환(int) -> 실수 값 필요 시 형변환 후 사용
	int		GetSoundLengthInIntSec();			
	// 입력 시간으로 음악의 진행도 옮기기
	void	SetPositionInSec(float _fTimeSec);	
	// 사운드 파일이 현재 몇 초를 재생중인지 float으로 반환
	float	GetCurrentPositionInSec();

public:
	CSound();
	virtual ~CSound();
};

