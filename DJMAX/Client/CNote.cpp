#include "pch.h"
#include "CNote.h"

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
	//:m_eType(NOTE)
{
}

CNote::CNote(const CNote& _Origin)
{
}

CNote::~CNote()
{
}

void CNote::begin()
{
}

void CNote::tick(float _DT)
{
}

void CNote::render(HDC _dc)
{
}
