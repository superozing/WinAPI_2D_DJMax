#include "pch.h"
#include "CNote.h"
#include "CLogMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CGear_PlayLevel.h"

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
 


void CNote::operator=(const NoteInfo& _other)
{
	m_fTapTime = _other.m_fTapTime;
	m_fReleasedTime = _other.m_fReleasedTime;
	m_eType = _other.m_eType;
	m_Line = _other.m_Line;
	SetNoteLine(_other.m_Line);
}

CNote::CNote()
	:m_eType(NOTE_TYPE::DEFAULT)
	, m_fTapTime(0.f)
	, m_fReleasedTime(0.f)
	, m_Line()
	, m_pNoteTexture(nullptr)
	, m_pOwner(nullptr)
	, m_blendFunc{}
{
	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}

CNote::CNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line, CGear* _owner)
	: m_eType(_type)
	, m_fTapTime(_tapTime)
	, m_fReleasedTime(_pressTime)
	, m_Line(_line)
	, m_pNoteTexture(nullptr)
	, m_pOwner(_owner)
	, m_blendFunc{}
{
	SetNoteLine(_line);

	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}


CNote::CNote(const CNote& _Origin)
	: m_eType(_Origin.m_eType)
	, m_fTapTime(_Origin.m_fTapTime)
	, m_fReleasedTime(_Origin.m_fReleasedTime)
	, m_Line(_Origin.m_Line)
	, m_pOwner(_Origin.m_pOwner)
	, m_blendFunc{}
{
	SetNoteLine(m_Line);

	// blend function setting
	m_blendFunc.BlendOp = AC_SRC_OVER;
	m_blendFunc.BlendFlags = 0;

	m_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255
	m_blendFunc.AlphaFormat = AC_SRC_ALPHA; // 0
}

CNote::~CNote()
{
}

void CNote::SetNoteLine(GEARLINE_TYPE _line)
{
	// 자신의 위치(offset)를 라인으로 바꾸어야 한다.
	switch (_line)
	{
	case GEARLINE_TYPE::LEFTSIDE:
		m_pNoteTexture = FINDTEX(L"sidetrack_atlas");
		SetPos(Vec2(103.3f, GetPos().y));
		break;
	case GEARLINE_TYPE::RIGHTSIDE:
		m_pNoteTexture = FINDTEX(L"sidetrack_atlas");
		SetPos(Vec2(103.3f * 3, GetPos().y));
		break;

	case GEARLINE_TYPE::_1:
		m_pNoteTexture = FINDTEX(L"note_white");
		SetPos(Vec2(103.3f, GetPos().y));

		break;
	case GEARLINE_TYPE::_4:
		m_pNoteTexture = FINDTEX(L"note_white");
		SetPos(Vec2(103.3f * 4, GetPos().y));

		break;

	case GEARLINE_TYPE::_2:
		m_pNoteTexture = FINDTEX(L"note_blue");
		SetPos(Vec2(103.3f * 2, GetPos().y));
		break;
	case GEARLINE_TYPE::_3:
		m_pNoteTexture = FINDTEX(L"note_blue");
		SetPos(Vec2(103.3f * 3, GetPos().y));

		break;

	default:
		LOG(LOG_LEVEL::ERR, L"노트의 라인이 설정되지 않아 이미지가 설정되지 않음.");
	}
}


void CNote::render(HDC _dc, float _curTime, float _speed, float _offset)
{
	if (nullptr != m_pNoteTexture)
	{
		int XDest = int(GetPos().x);
		// y 좌표
		int YDest = int((_curTime + _offset - m_fReleasedTime) * (NOTE_MOVE_SECOND * _speed)) + GEAR_LINE_POS;
		// 높이
		int hDest = int((m_fReleasedTime - m_fTapTime) * (NOTE_MOVE_SECOND * _speed));
		// render 예외 처리
		bool isRender = ((bool)m_eType && !(YDest + hDest > -50 && YDest < 750))
			|| (!(bool)m_eType && (YDest < -50 || YDest > 750));
		if (isRender)
			return;

		// 원본 x, y 값
		POINT vSrc = { (int)m_pNoteTexture->GetWidth(), (int)m_pNoteTexture->GetHeight() };


		switch (m_eType)
		{
		// 만약 자신이 기본 노트라면 기본 노트를 출력
		case NOTE_TYPE::DEFAULT:// 기본 노트
			AlphaBlend(_dc
				, XDest,	YDest
				, NOTE_WIDTH,	NOTE_HEIGHT
				, m_pNoteTexture->GetDC()
				, 0, 0
				, vSrc.x, vSrc.y
				, m_blendFunc);
			break;
		// 만약 자신이 롱 노트라면 기본 노트를 늘려서 출력
		case NOTE_TYPE::LONG:// 롱 노트
			AlphaBlend(_dc
				, XDest,	YDest
				, NOTE_WIDTH,	hDest
				, m_pNoteTexture->GetDC()
				, 0, 0
				, vSrc.x, vSrc.y
				, m_blendFunc);
			break;
		// 만약 자신이 사이드트랙 노트라면 두 칸을 차지하도록 해서 출력
		case NOTE_TYPE::SIDETRACK:// 사이드트랙 노트
			AlphaBlend(_dc
				, XDest,	YDest
				, NOTE_SIDE_WIDTH,	hDest
				, m_pNoteTexture->GetDC()
				, 0, 0
				, 240, vSrc.y
				, m_blendFunc);
			break;
		}
	}

}


void CNote::Save(FILE* _pFile)
{
	// NOTE_TYPE
	fwrite(&m_eType, sizeof(NOTE_TYPE), 1, _pFile);

	// GEARLINE_TYPE - 나와야 하는 라인
	fwrite(&m_Line, sizeof(GEARLINE_TYPE), 1, _pFile);

	// TapTime - tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)
	fwrite(&m_fTapTime, sizeof(float), 1, _pFile);

	// ReleasedTime - 누르기를 끝내는 시간(롱 노트, 사이드 트랙에서만 사용 가능)
	fwrite(&m_fReleasedTime, sizeof(float), 1, _pFile);
}

CNote& CNote::Load(FILE* _pFile, CGear* _owner)
{
	// NOTE_TYPE
	fread(&m_eType, sizeof(NOTE_TYPE), 1, _pFile);

	// GEARLINE_TYPE - 나와야 하는 라인
	fread(&m_Line, sizeof(GEARLINE_TYPE), 1, _pFile);

	// TapTime - tap 할 시간(현재 음악 진행도와 비교할 것, 0.01초 단위로 수정 가능)
	fread(&m_fTapTime, sizeof(float), 1, _pFile);

	// ReleasedTime - 누르기를 끝내는 시간(롱 노트, 사이드 트랙에서만 사용 가능)
	fread(&m_fReleasedTime, sizeof(float), 1, _pFile);

	m_pOwner = _owner;

	return *this;
}