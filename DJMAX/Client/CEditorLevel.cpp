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
#include "CGear_EditorLevel.h"

INT_PTR CALLBACK NoteEditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// 리스트의 iterator는 현재 수정(포커싱)중인 노트 객체를 오른 쪽 UI에 표시하면 좋을 것 같다.

CNote* g_pEditNote = nullptr;

void CEditorLevel::init()
{
#pragma region Background
	CBackground* pDefaultBg = new CBackground;
	pDefaultBg->SetTexture(FINDTEX(L"bga_off_bg"));
	AddObject(LAYER::BACK_GROUND, pDefaultBg);


#pragma endregion
#pragma region gear
	m_pGear = new CGear_EditorLevel;
	

	AddObject(LAYER::GEAR, m_pGear);

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
	m_pGear->m_pMusic = FINDSND(L"music1");
	m_pGear->m_pMusic->SetVolume(70);
	m_pGear->m_pMusic->SetPosition(0.f);
	m_pGear->m_pMusic->Play();

	m_pGear->m_pOwner = this;
}

void CEditorLevel::exit()
{
	// 그냥 나갈 경우: 데이터를 저장하지 않음
	// 아니면 다이아로그 창을 띄워서 노트를 저장할까요? 같은거 띄워도 좋을 듯.

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


void CEditorLevel::OpenNoteEditWindow(CNote* _pEditNote)
{
	g_pEditNote = _pEditNote;
	DialogBox(nullptr, /*MAKEINTRESOURCE(*/L"IDD_DIALOG_NOTE", CEngine::GetInst()->GetMainWind(), NoteEditProc);
}






// ==============================
// NoteEdit Dialog 프로시저 함수
// ==============================
//
INT_PTR CALLBACK NoteEditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{

		wstring strTimeBuf = L"";
		// 초기화 구문.
		// 콤보 박스 접근해서 띄우는 목록 구현하기.
		HWND hComboGEARLINE = GetDlgItem(hDlg, IDC_COMBO_GEARLINE);		// 콤보 박스 핸들 가져오기
		HWND hComboNOTETYPE = GetDlgItem(hDlg, IDC_COMBO_NOTETYPE);		// 콤보 박스 핸들 가져오기
		HWND hEditTAP		= GetDlgItem(hDlg, IDC_EDIT_TAPTIME);		// 에디트 컨트롤 핸들 가져오기
		HWND hEditRELEASE	= GetDlgItem(hDlg, IDC_EDIT_RELEASE_TIME);	// 에디트 컨트롤 핸들 가져오기

		strTimeBuf = std::to_wstring(g_pEditNote->GetNoteTapTime());
		SetDlgItemText(hDlg, IDC_EDIT_TAPTIME, strTimeBuf.c_str());

		strTimeBuf = std::to_wstring(g_pEditNote->GetNoteReleasedTime());
		SetDlgItemText(hDlg, IDC_EDIT_RELEASE_TIME, strTimeBuf.c_str());

		// 콤보 박스에 필요한 만큼 항목을 추가합니다.
		// hComboGEARLINE
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 0, (LPARAM)L"Left side");
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 1, (LPARAM)L"1");
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 2, (LPARAM)L"2");
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 3, (LPARAM)L"3");
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 4, (LPARAM)L"4");
		SendMessage(hComboGEARLINE, CB_ADDSTRING, 5, (LPARAM)L"Right side");

		// hComboNOTETYPE
		SendMessage(hComboNOTETYPE, CB_ADDSTRING, 0, (LPARAM)L"Default");
		SendMessage(hComboNOTETYPE, CB_ADDSTRING, 1, (LPARAM)L"Long");
		SendMessage(hComboNOTETYPE, CB_ADDSTRING, 2, (LPARAM)L"Sidetrack");
															  
		// 초기 선택 항목 설정
		// Note type
		switch (g_pEditNote->GetNoteType())
		{
		case NOTE_TYPE::DEFAULT:
			SendMessage(hComboNOTETYPE, CB_SETCURSEL, 0, 0); // 세 번째 인자: 인덱스와 같이 사용함.
			break;
		case NOTE_TYPE::LONG:
			SendMessage(hComboNOTETYPE, CB_SETCURSEL, 1, 0);
			break;
		case NOTE_TYPE::SIDETRACK:
			SendMessage(hComboNOTETYPE, CB_SETCURSEL, 2, 0);
			break;
		}

		// Line type
		switch (g_pEditNote->GetLineType())
		{
		case GEARLINE_TYPE::LEFTSIDE:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 0, 0);
			break;
		case GEARLINE_TYPE::_1:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 1, 0);
			break;
		case GEARLINE_TYPE::_2:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 2, 0);
			break;
		case GEARLINE_TYPE::_3:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 3, 0);
			break;
		case GEARLINE_TYPE::_4:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 4, 0);
			break;
		case GEARLINE_TYPE::RIGHTSIDE:
			SendMessage(hComboGEARLINE, CB_SETCURSEL, 5, 0);
			break;
		}
		return (INT_PTR)TRUE;

	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			//// 에디트 컨트롤 받아오기 
			wstring wstrInputData_tapTime;
			wstring wstrInputData_releaseTime;

			// 문자열 초기화
			wstrInputData_tapTime.resize(20, L' '); // 공백 문자로 초기화
			wstrInputData_releaseTime.resize(20, L' '); // 공백 문자로 초기화

			GetDlgItemTextW(hDlg, IDC_EDIT_TAPTIME, &wstrInputData_tapTime[0], 20);
			GetDlgItemTextW(hDlg, IDC_EDIT_RELEASE_TIME, &wstrInputData_releaseTime[0], 20);
			
			string strInputData_tapTime;
			string strInputData_releaseTime;
			
			strInputData_tapTime.assign(wstrInputData_tapTime.begin(), wstrInputData_tapTime.end());
			strInputData_releaseTime.assign(wstrInputData_releaseTime.begin(), wstrInputData_releaseTime.end());

			
			float changeSec = std::stof(strInputData_tapTime);
			g_pEditNote->SetNoteTapTime(changeSec);
			changeSec =	std::stof(strInputData_releaseTime);
			g_pEditNote->SetNoteReleasedTime(changeSec);

			// 콤보 박스 받아오기
			HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO_GEARLINE);
			int selectedIndex = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			if (selectedIndex != CB_ERR) 
			{
				// 콤보 박스에서 선택한 항목의 데이터를 가져오기 위한 배열 또는 데이터 구조를 사용
				// 예: 문자열 배열을 사용하는 경우
				GEARLINE_TYPE items[] = { GEARLINE_TYPE::LEFTSIDE, GEARLINE_TYPE::_1, GEARLINE_TYPE::_2, GEARLINE_TYPE::_3, GEARLINE_TYPE::_4, GEARLINE_TYPE::RIGHTSIDE };

				if (selectedIndex >= 0 && selectedIndex < _countof(items)) 
				{
					g_pEditNote->SetNoteLine(items[selectedIndex]);
					// selectedItem에 선택한 항목의 정보(예: 문자열)가 저장됨
				}
				else {
					// 선택한 항목의 인덱스가 유효하지 않음을 처리
					// 예: 오류 메시지를 표시하거나 기본값으로 처리
				}
			}

			hComboBox = GetDlgItem(hDlg, IDC_COMBO_NOTETYPE);
			selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

			if (selectedIndex != CB_ERR)
			{
				// 콤보 박스에서 선택한 항목의 데이터를 가져오기 위한 배열 또는 데이터 구조를 사용
				// 예: 문자열 배열을 사용하는 경우
				NOTE_TYPE items[] = { NOTE_TYPE::DEFAULT, NOTE_TYPE::LONG, NOTE_TYPE::SIDETRACK};

				if (selectedIndex >= 0 && selectedIndex < _countof(items)) {
					g_pEditNote->SetNoteType(items[selectedIndex]);
					// selectedItem에 선택한 항목의 정보(예: 문자열)가 저장됨
				}
				else {
					// 선택한 항목의 인덱스가 유효하지 않음을 처리
					// 예: 오류 메시지를 표시하거나 기본값으로 처리
				}
			}



			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}

