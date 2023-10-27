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
	CTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height); // ������ ������ FadeIn, FadeOut�� ���� �Լ�... ���߿� �� ���� ��������?
	CTexture* FindTexture(const wstring& _strKey);
};


/* ���
* �ؽ��� �Ǵ� ���带 ����ϰ� ���� Object �Ļ� Ŭ���� �ʿ��� 
* ����� CTexture*�� ���ϴ� �ؽ��ĸ�,
* ����� CSound*�� ���ϴ� ���带 ���� �Ŵ����κ��� ���� ����� �� �ִ�.
* LoadTexture�� ���ؼ� ���ϴ� �ؽ��ĸ� ���Ϸκ��� �ҷ��� �� �ִ�. 
* 	���� �ش� �ؽ��ĸ� �ҷ����µ��� ������ ���(��� ����, �ؽ��� �� Ʋ�� ��) ��ȯ�� nullptr.
* FindTexture�� ���ؼ� ���ϴ� �ؽ��ĸ� ã�ƿ� �� �ִ�. 
*	���� �ش� �ؽ��İ� map �ȿ� ���� ��� ��ȯ�� nullptr.
*/