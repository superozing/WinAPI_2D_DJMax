#include "pch.h"
#include "CAnimator.h"

#include "CPathMgr.h"
#include "CAnim.h"

//#include "CLogMgr.h"

CAnimator::CAnimator(CObj* _Owner)
	:CComponent(_Owner) // CComponent 쪽에는 기본 생성자를 정의하지 않았기 때문에, 받아온 소유자를 인자로 넣어줌.
	,m_CurAnim(nullptr)
	,m_bRepeat(false)
{
}

 // 깊은 복사 재정의 -> Clone() 사용 위해서.
CAnimator::CAnimator(const CAnimator& _Origin)
	: CComponent(_Origin)
	, m_CurAnim(nullptr)
	, m_bRepeat(_Origin.m_bRepeat)
{
	for (const auto& pair : _Origin.m_mapAnim)
	{
		CAnim* pAnim = pair.second->Clone();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(pair.first, pAnim));
	}

	if (nullptr != _Origin.m_CurAnim)
	{
		m_CurAnim = FindAnim(_Origin.m_CurAnim->GetName());
	}
}


CAnimator::~CAnimator()
{
	// 모든 애니메이션을 지움.
	for (const auto& pair : m_mapAnim)
	{
		delete pair.second;
	}
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_bRepeat = _bRepeat; // 반복 여부 설정
	m_CurAnim = FindAnim(_strName); // 애니메이션 불러오기

	// 애니메이션 불러오기 실패한 경우
	if (!m_CurAnim)
	{
		// LOG 띄워주면 좋을 듯?
	}
}

void CAnimator::Stop()
{	
}

CAnim* CAnimator::FindAnim(const wstring& _strName)
{
	// 찾기
	auto iter = m_mapAnim.find(_strName);
	
	// 실패
	if (iter == m_mapAnim.end())
	{
		// LOG 띄워주면 좋을 듯?
		return nullptr;
	}
	// 성공
	return iter->second;
}


// 1.키 문자열 2.아틀라스 텍스쳐 3.LeftTop 4.CutSize 5.Offset 6.Duration 7.프레임 개수 
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _Altas, 
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
{
	// 이미 있는 애니메이션인가 확인
	CAnim* pAnim = FindAnim(_strName);
	if (IsValid(pAnim))
	{
		return;
	}

	pAnim = new CAnim;
	
	// 소유주
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _Altas, _vLeftTop, _vCutSize, _vOffset, _Duration, _MaxFrm);
	m_mapAnim.insert(make_pair(_strName, pAnim));

}

// 1.키 문자열 2.아틀라스 텍스쳐 3.LeftTop 4.CutSize 5.Offset 6.Duration 7.프레임 개수 
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _Altas,
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm, int _row)
{
	// 이미 있는 애니메이션인가 확인
	CAnim* pAnim = FindAnim(_strName);
	if (IsValid(pAnim))
	{
		return;
	}

	pAnim = new CAnim;

	// 소유주
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _Altas, _vLeftTop, _vCutSize, _vOffset, _Duration, _MaxFrm, _row);
	m_mapAnim.insert(make_pair(_strName, pAnim));

}

void CAnimator::SaveAnimations(const wstring& _strRelativePath)
{
	wstring strFolderPath = CPathMgr::GetContentPath();
	strFolderPath += _strRelativePath;

	// 애니메이션의 Save 함수를 전부 호출해줌.
	for (const auto& pair : m_mapAnim)
	{
		wstring strFilePath = strFolderPath + L"\\" + pair.first + L".txt";
		if (!pair.second->Save(strFilePath))
		{
			//LOG(ERR, L"Animation Save 실패");
		}
	}
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	// 새 Anim 객체 생성 -> 애니메이션 Load()
	CAnim* pNewAnim = new CAnim;

	if (!pNewAnim->Load(strFilePath))
	{
		//LOG(ERR, L"Animation Load 실패");
		delete pNewAnim;
		return;
	}

	pNewAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));

}

void CAnimator::finaltick(float _DT)
{
	// 파일 입출력 때 실패 할 확률이 넘쳐나니까 유효한 애니메이션인지 체크해요.
	if (IsValid(m_CurAnim))
	{
		// 현재 애니메이션이 종료되었는데 반복 상태가 true라면
		if (m_bRepeat && m_CurAnim->IsFinish())
		{
			// 처음 0프레임 세팅으로 되돌림.
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}
}

void CAnimator::render(HDC _dc)
{
	if (IsValid(m_CurAnim))
	{
		m_CurAnim->render(_dc);
	}
}