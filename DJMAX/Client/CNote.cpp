#include "pch.h"
#include "CNote.h"
#include "CLogMgr.h"

#include "CAssetMgr.h"

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
	,m_fTapTime(0.f)
	,m_fPressTime(0.f)
	,m_Line()
	,m_pNoteTexture(nullptr)
{
}

CNote::CNote(NOTE_TYPE _type, float _tapTime, float _pressTime, GEARLINE_TYPE _line)
	: m_eType(_type)
	, m_fTapTime(_tapTime)
	, m_fPressTime(_pressTime)
	, m_Line(_line)
	, m_pNoteTexture(nullptr)
{
	SetNoteLine(_line);
}




CNote::CNote(const CNote& _Origin)

{
}

CNote::~CNote()
{
}

void CNote::SetNoteLine(GEARLINE_TYPE _line)
{
	switch (_line)
	{
	case GEARLINE_TYPE::LEFTSIDE:
		m_pNoteTexture = FINDTEX(L"sidetrack_atlas");
		break;
	case GEARLINE_TYPE::RIGHTSIDE:
		m_pNoteTexture = FINDTEX(L"sidetrack_atlas");
		break;

	case GEARLINE_TYPE::_1:
		m_pNoteTexture = FINDTEX(L"note_white");
		break;
	case GEARLINE_TYPE::_4:
		m_pNoteTexture = FINDTEX(L"note_white");
		break;

	case GEARLINE_TYPE::_2:
		m_pNoteTexture = FINDTEX(L"note_blue");
		break;
	case GEARLINE_TYPE::_3:
		m_pNoteTexture = FINDTEX(L"note_blue");
		break;

	default:
		LOG(LOG_LEVEL::ERR, L"��Ʈ�� ������ �������� �ʾ� �̹����� �������� ����.");
	}
}

void CNote::render(HDC _dc)
{
	
}

