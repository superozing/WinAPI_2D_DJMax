#include "pch.h"
#include "CEditorLevel.h"

// Dialog 호출 위해 필요(ID값)
#include "resource.h"

// Manager
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CCamera.h"


// Level Object
#include "CPanelUI.h"
#include "CBtnUI.h"

// 리스트의 iterator는 현재 수정(포커싱)중인 노트 객체를 오른 쪽 UI에 표시하면 좋을 것 같다.



void CEditorLevel::init()
{
}

void CEditorLevel::enter()
{
	//OpenNoteModifyWindow();
	
}

void CEditorLevel::exit()
{
}

void CEditorLevel::tick()
{
	CLevel::tick();

}


void CEditorLevel::OpenNoteModifyWindow()
{
	//DialogBox(nullptr, MAKEINTRESOURCE(IDC_CLIENT), CEngine::GetInst()->GetMainWind(), CreateTileProc);
}






// ==============================
// CreateTile Dialog 프로시저 함수
// ==============================

//INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK)
//		{
//			// IDC_COL, IDC_ROW 에디트 컨트롤에 입력한 숫자를 알아내서
//			// EditorLevel 의 타일을 해당 수치에 맞게 생성시킨다.
//			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);
//			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
//
//			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
//			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(pCurLevel);
//
//			if (nullptr != pEditorLevel)
//			{
//				pEditorLevel->CreateTile(Row, Col);
//			}
//
//			// 다이얼로그 윈도우 종료
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		else if (LOWORD(wParam) == IDCANCEL)
//		{
//			// 다이얼로그 윈도우 종료
//			EndDialog(hDlg, LOWORD(wParam));
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}

