#include "pch.h"
#include "CEditorLevel.h"

// Dialog 호출 위해 필요(ID값)
#include "resource.h"

// Manager
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"


// Level Object
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CBackground.h"
#include "CNote.h"
#include "CGear.h"

// 리스트의 iterator는 현재 수정(포커싱)중인 노트 객체를 오른 쪽 UI에 표시하면 좋을 것 같다.


void CEditorLevel::init()
{
#pragma region Background
	CBackground* pDefaultBg = new CBackground;
	pDefaultBg->SetTexture(FINDTEX(L"bga_off_bg"));
	AddObject(LAYER::BACK_GROUND, pDefaultBg);


#pragma endregion
#pragma region gear
	m_pGear = new CGear;
	m_pGear->m_pMusic = FINDSND(L"mainBGM");
	m_pGear->m_pMusic->SetVolume(70);
	m_pGear->m_pMusic->SetPosition(0.f);
	

	AddObject(LAYER::GEAR, m_pGear);

#pragma endregion
#pragma region note
	FINDTEX(L"sidetrack_come_atlas");		// sidetrack 예고 애니메이션 아틀라스
	FINDTEX(L"sidetrack_atlas");			// 노트 - sidetrack
	FINDTEX(L"note_blue");					// 노트 - 파랑(안 쪽에 위치)
	FINDTEX(L"note_white");					// 노트 - 하양(바깥 쪽에 위치)



#pragma endregion
#pragma region coolbomb




#pragma endregion
#pragma region effect




#pragma endregion
#pragma region Sound

#pragma endregion
	
}

void CEditorLevel::enter()
{
	// 원하는 곡을 선택하고, 그 곡과 이어져 있는 파일을 한꺼번에 불러올 수 있어야 해요.
	//		곡과 채보 파일의 이어져 있는 정보를 담는 파일도 따로 만드는 것이 좋아보임.
	// 만약 해당 곡에 연동되어 있는 파일이 없다면, 해당 곡에 해당하는 파일을 생성해서 그 파일에 저장
	// 불러온 곡이 이미 만들어져 있다면 해당 곡과 파일을 읽을 텐데... 이 때 reserve + 추가적으로 입력될 노트 수(한 200칸 정도면 괜찮으려나?)를 해놓고 불러옴.
	CCamera::GetInst()->FadeIn(1.f);

	m_pGear->LoadNoteData();

	//m_pGear->SaveNoteData();
	CSound* snd = m_pGear->GetSound();
	snd = FINDSND(L"music1");
	snd->Play(); 
}

void CEditorLevel::exit()
{
	// 모든 데이터를 저장해요.

}

// 오 ㅋㅋ
void CEditorLevel::tick()
{
	CLevel::tick();
	//노트 수정 방식
	//	수정할 노트는 iterator로 가리키고, 오른 쪽에 UI를 띄워서 해당 노트의 정보를 계속해서 띄울 것.
	//수정할 노트를 방향키 또는 DialogBox를 이용해서 수정할 수 있다.
	/// 방향키를 이용한 수정
	//	0.01초 단위로 좌우 방향키를 사용해서 노트 출력 타이밍을 조절할 수 있고,
	//	가리키는 데이터를 상하 방향키를 사용해서 움직일 수 있다.
	//	또한 노트를 가리킬 때, 상하 방향키 뿐만 아니라 마우스로 해당 노트를 클릭할 경우 선택 되어야 한다.
	/// DialogBox를 이용한 수정
	//	만약 방향키를 사용한 0.01초 단위의 조정이 아닌, 노트의 정보(노트의 종류, 입력되는 키)의 세부적인 조정을 위해서 스페이스 바 입력시 Dialog를 띄운다.
	//OpenNoteModifyWindow(); // 노트를 이터레이터로 항상 가리키고 있음. 반





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

