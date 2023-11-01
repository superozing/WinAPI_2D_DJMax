#include "pch.h"
#include "CNote.h"

// 노트를 추가할 떄, addobject를 쓰면 해당 레벨의 원하는 인덱스로 들어갈 텐데.
// 1, 레이어를 상속받는 다른 레이어(예를 들면 노트)를 만들고 만약 그 레이어가 addObject를 받았을 경우에는 이제 자신 레이어에 집어넣는 것이 아니고 자료구조에 집어넣는다던가...

// 아니면 애초에 addObject를 사용할 필요가 있을까?
// 노트를 추가하는 것은 에디터 레벨의 기능이고, 에디터 레벨에서는
// 아냐. 일단 tick와 render를 받도록 해주어야 한다.
// 노트들을 저장하고 있는 자료구조를 들고 있는 오브젝트 하나 만들어서
// 해당 오브젝트에 tick이 들어올 경우 그 오브젝트가 들고 있는 모든 노트들에게 tick을 주고, render를 주고 하면 화면에 잘 뜰 것 같은데?

// 일단 해보는게 좋을 듯.
// 노트에 충돌체가 없으니까 tick이 굳이 필요할까? 라는 생각도 들긴 한다.
// 어차피 render위치 계산은 간단하니까 노트에게 정보를 들게 하지 말고, render위치는 계산 식에 비례하니까 괜찮을 듯.
// 그러면 노트들을 담고 있는 객체가 필요하겠네요. 에디터 전용 하나, 플레이 전용 하나.
// 에디터에서는 중간에 데이터를 추가하는 것이 쉽게 이루어지도록 리스트를 사용하고,
// 플레이에서는 빠른 탐색을 위해서 벡터를 사용해서 파일로부터 데이터를 담아오는 것이 좋아보인다.
// 음...좋아 좋아... 구현만 하면 된다.
 


CNote::CNote()
	:m_eType(NOTE_TYPE::DEFAULT)
	,m_fTapTime(0.f)
	,m_fPressTime(0.f)
{
}

CNote::CNote(NOTE_TYPE _type, float _tapTime, float _pressTime)
	: m_eType(_type)
	, m_fTapTime(_tapTime)
	, m_fPressTime(_pressTime)
{
}

CNote::CNote(const CNote& _Origin)

{
}

CNote::~CNote()
{
}

void CNote::render(HDC _dc)
{
	
}

