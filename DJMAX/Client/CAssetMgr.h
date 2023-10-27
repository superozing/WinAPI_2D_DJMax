#pragma once

class CTexture;
class CSound;

class CAssetMgr
{
	SINGLETON(CAssetMgr);
private:
	map<wstring, CTexture*>	m_mapTex;
	map<wstring, CSound*>	m_mapSound;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height); // 지금은 오로지 FadeIn, FadeOut을 위한 함수... 나중에 쓸 일이 있으려나?
	CTexture* FindTexture(const wstring& _strKey);
};


/* 사용
* 텍스쳐 또는 사운드를 사용하고 싶은 Object 파생 클래스 쪽에서 
* 멤버로 CTexture*로 원하는 텍스쳐를,
* 멤버로 CSound*로 원하는 사운드를 에셋 매니저로부터 얻어와 사용할 수 있다.
* LoadTexture를 통해서 원하는 텍스쳐를 파일로부터 불러올 수 있다. 
* 	만약 해당 텍스쳐를 불러오는데에 실패할 경우(경로 문제, 텍스쳐 명 틀림 등) 반환은 nullptr.
* FindTexture를 통해서 원하는 텍스쳐를 찾아올 수 있다. 
*	만약 해당 텍스쳐가 map 안에 없을 경우 반환은 nullptr.
*/