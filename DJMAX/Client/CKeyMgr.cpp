#include "pch.h"
#include "CKeyMgr.h"
#include "CLogMgr.h"
#include "CEngine.h"

int g_KeySync[KEY::KEY_END] =
{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
	
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_TAB,
	VK_LSHIFT,
	VK_RSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,

	VK_ESCAPE,
	VK_RETURN,
	VK_BACK,

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_OEM_1,
	VK_OEM_7,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	// Capacity 확보
	m_vecKeyData.reserve(KEY::KEY_END);

	for (UINT i = 0; i < KEY_END; ++i)
	{
		m_vecKeyData.push_back(FKeyData{ (KEY)i, NONE, false }); // key, state, pressed
	}
}

void CKeyMgr::tick()
{
	// 현재 창이 Focus 상태가 아니라면 전부 NONE 상태로 바꾸는 작업
	if (nullptr == GetFocus())
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			if (TAP == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = PRESSED;
			}
			else if (PRESSED == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = RELEASED;
			}
			else if (RELEASED == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = NONE;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			// 이번 프레임에 눌렸는가
			if (GetAsyncKeyState(g_KeySync[m_vecKeyData[i].eKey]) & 0x8001)
			{
				// 이전 프레임에 눌렸는가
				if (m_vecKeyData[i].bPressed)
				{
					m_vecKeyData[i].eState = PRESSED;
				}
				else
				{
					m_vecKeyData[i].eState = TAP;
					m_vecKeyData[i].bPressed = true;
				}
			}
			else
			{
				// 이전 프레임에 눌렸는가
				if (m_vecKeyData[i].bPressed)
				{
					m_vecKeyData[i].eState = RELEASED;
					m_vecKeyData[i].bPressed = false;
				}
				else
				{
					m_vecKeyData[i].eState = NONE;
				}
			}
		}

		// 마우스 좌표
		POINT pt = {};
		GetCursorPos(&pt); // 화면에서 위치하는 커서의 절대적 위치(창을 기준으로 삼지 않음)
		ScreenToClient(CEngine::GetInst()->GetMainWind(), &pt); // 원하는 창을 기준으로 커서 위치를 변환
		m_vMousePos = pt;

		//if (KEY_TAP(KEY::LBTN))
		//{
		//	wstring str = L"mouse pos: ";
		//	str += std::to_wstring(m_vMousePos.x);
		//	str += L", ";
		//	str += std::to_wstring(m_vMousePos.y);
		//	LOG(LOG_LEVEL::LOG, str.c_str());
		//}
	}	
}

