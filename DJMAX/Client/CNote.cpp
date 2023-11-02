#include "pch.h"
#include "CNote.h"
#include "CLogMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

// ��Ʈ�� �߰��� ��, addobject�� ���� �ش� ������ ���ϴ� �ε����� �� �ٵ�.
// 1, ���̾ ��ӹ޴� �ٸ� ���̾�(���� ��� ��Ʈ)�� ����� ���� �� ���̾ addObject�� �޾��� ��쿡�� ���� �ڽ� ���̾ ����ִ� ���� �ƴϰ� �ڷᱸ���� ����ִ´ٴ���...

// �ƴϸ� ���ʿ� addObject�� ����� �ʿ䰡 ������?
// ��Ʈ�� �߰��ϴ� ���� ������ ������ ����̰�, ������ ����������
// �Ƴ�. �ϴ� tick�� render�� �޵��� ���־�� �Ѵ�.
// ��Ʈ���� �����ϰ� �ִ� �ڷᱸ���� ��� �ִ� ������Ʈ �ϳ� ����
// �ش� ������Ʈ�� tick�� ���� ��� �� ������Ʈ�� ��� �ִ� ��� ��Ʈ�鿡�� tick�� �ְ�, render�� �ְ� �ϸ� ȭ�鿡 �� �� �� ������?

// �ϴ� �غ��°� ���� ��.
// ��Ʈ�� �浹ü�� �����ϱ� tick�� ���� �ʿ��ұ�? ��� ������ ��� �Ѵ�.
// ������ render��ġ ����� �����ϴϱ� ��Ʈ���� ������ ��� ���� ����, render��ġ�� ��� �Ŀ� ����ϴϱ� ������ ��.
// �׷��� ��Ʈ���� ��� �ִ� ��ü�� �ʿ��ϰڳ׿�. ������ ���� �ϳ�, �÷��� ���� �ϳ�.
// �����Ϳ����� �߰��� �����͸� �߰��ϴ� ���� ���� �̷�������� ����Ʈ�� ����ϰ�,
// �÷��̿����� ���� Ž���� ���ؼ� ���͸� ����ؼ� ���Ϸκ��� �����͸� ��ƿ��� ���� ���ƺ��δ�.
// ��...���� ����... ������ �ϸ� �ȴ�.
 


CNote::CNote()
	:m_eType(NOTE_TYPE::DEFAULT)
	, m_fTapTime(0.f)
	, m_fReleasedTime(0.f)
	, m_Line()
	, m_pNoteTexture(nullptr)
	, m_pOwner(nullptr)
	, m_blendFunc{}
{
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
	, m_pNoteTexture(_Origin.m_pNoteTexture)
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
	// �ڽ��� ��ġ(offset)�� �������� �ٲپ�� �Ѵ�.
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
		LOG(LOG_LEVEL::ERR, L"��Ʈ�� ������ �������� �ʾ� �̹����� �������� ����.");
	}
}

void CNote::render(HDC _dc, float _curTime, float _speed)
{
	// ���� �ڽ��� �⺻ ��Ʈ��� �⺻ ��Ʈ�� ���
	// ���� �ڽ��� �� ��Ʈ��� �⺻ ��Ʈ�� �÷��� ���
	// ���� �ڽ��� ���̵�Ʈ�� ��Ʈ��� �� ĭ�� �����ϵ��� �ؼ� ���
	Vec2 vPos = GetPos();

	//if (nullptr != m_pNoteTexture)
	//{
	//	Vec2 vImgScale = Vec2((float)m_pNoteTexture->GetWidth(), (float)m_pNoteTexture->GetHeight());
	//	AlphaBlend(_dc
	//		, int(vPos.x), int(_curTime)//_speed)
	//		, 100, 20/*fLength*/
	//		, m_pNoteTexture->GetDC()
	//		, 0, 0
	//		, int(vImgScale.x), int(vImgScale.y)
	//		, m_blendFunc);
	//}
	if (nullptr != m_pNoteTexture)
	{
		Vec2 vImgScale = Vec2((float)m_pNoteTexture->GetWidth(), (float)m_pNoteTexture->GetHeight());
		AlphaBlend(_dc
			, int(vPos.x), int(_curTime)//_speed)
			, 100, (m_fReleasedTime - m_fTapTime) * 25 * _speed 
			, m_pNoteTexture->GetDC()
			, 0, 0
			, int(vImgScale.x), int(vImgScale.y)
			, m_blendFunc);
	}
}

