﻿#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

// Level
#include "CLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"
#include "CSelectLevel.h"
#include "CPlayLevel.h"
#include "CScoreLevel.h"

// Manager
#include "CLogMgr.h"
#include "CAssetMgr.h"

CLevelMgr::CLevelMgr()
	:m_pCurLevel(nullptr)
	,m_arrLevels{}
{
}

CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
			delete m_arrLevels[i];
	}
}


void CLevelMgr::init()
{
	// 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL]	= new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL]	= new CEditorLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::SELECT_LEVEL] = new CSelectLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL]	= new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::SCORE_LEVEL]	= new CScoreLevel;
	/*레벨 추가 시 추가적으로 생성해주어야 함.*/


	////// Asset Load
	LOG(LOG_LEVEL::LOG, L"에셋을 불러옵니다.");
#pragma region LOAD_TEXTURE
	// 공용
	LOADTEX(L"background_default",		L"texture\\outgame\\title_bg.png");				// 배경화면 (기본)
	LOADTEX(L"background_shine",		L"texture\\outgame\\bg_shine.png");				// 배경화면 (그라데이션)
	LOADTEX(L"background_strip",		L"texture\\outgame\\striped_bg-side-side.png");	// 배경화면 (사선)
	LOADTEX(L"background_strip_square", L"texture\\outgame\\strip_square.png");			// 배경화면 (사선2)
	LOADTEX(L"bga_off_bg",				L"texture\\outgame\\bga_off_bg.png");			// 배경화면 (사선2)
	
	LOADTEX(L"logo_small",			L"texture\\outgame\\title_logo.png");			// 로고 (소)
	LOADTEX(L"logo_large",			L"texture\\outgame\\credit_logo.png");			// 로고 (대)

	LOADTEX(L"rank_atlas",			L"texture\\ingame\\result\\rank_atlas");		// 랭크 아틀라스(a,b,c,s)
	LOADTEX(L"star",				L"texture\\ingame\\result\\star_1.png");			// 별모양
	LOADTEX(L"end_atlas",			L"texture\\ingame\\result\\end_atlas.png");		// max combo, perfect play 아틀라스
	
	LOADTEX(L"popup",				L"texture\\outgame\\popup.png");				// popup 창
	
	// icon
	LOADTEX(L"icon_speed_atlas",	L"texture\\ingame\\icon\\speed_atlas.png");		// 속도 아이콘 아틀라스
	LOADTEX(L"icon_fever_atlas",	L"texture\\ingame\\icon\\fever_atlas.png");		// fever모드 아이콘 아틀라스(사실 이걸 아틀라스로 만들 필요가 있을까?)
	LOADTEX(L"icon_chaos_slideup",	L"texture\\ingame\\icon\\chaos_slideup");		// chaos - slideup. 노트를 입력할 수록 점점 속도가 빨라지는 기믹

	// combo
	LOADTEX(L"combo_num_atlas",		L"texture\\ingame\\combo\\combo_Number_atlas.png");		// 콤보 숫자 아틀라스 (콤보 전용)
	LOADTEX(L"combo_txt",			L"texture\\ingame\\combo\\combo_Number_atlas.png");		// 콤보 텍스트 이미지

	// fever
	LOADTEX(L"fever_bar_atlas",		L"texture\\ingame\\combo\\fever_bar_prog_atlas.png");	// fever 바
	LOADTEX(L"fever_bg_atlas",		L"texture\\ingame\\combo\\fever_note_bg_atlas.png");	// fever 기어 백그라운드
	LOADTEX(L"fever_sidetxt_atlas",	L"texture\\ingame\\combo\\fever_note_txt_atlas.png");	// fever 기어 사이드 텍스트 이미지
	LOADTEX(L"fever_txt",			L"texture\\ingame\\combo\\fever_txt.png");				// fever 텍스트 이미지
	LOADTEX(L"fever_mul_atlas",		L"texture\\ingame\\combo\\fever_txt_atlas.png");		// fever 배율 아틀라스
	LOADTEX(L"fever_ring_atlas",	L"texture\\ingame\\combo\\fever_x2_ring_atlas.png");	// fever ring 아틀라스

	// judge
	LOADTEX(L"judge_atlas",			L"texture\\ingame\\combo\\judge_txt_atlas.png");		// 콤보 텍스트 이미지

	// effect
	LOADTEX(L"effect_energe_atlas", L"texture\\ingame\\effect\\energe_1_atlas.png");		// 이펙트 에너지 아틀라스
	LOADTEX(L"effect_fire_atlas", L"texture\\ingame\\effect\\fire_1_atlas.png");			// 이펙트 불꽃 아틀라스
	LOADTEX(L"effect_smoke_atlas", L"texture\\ingame\\effect\\smoke_1_atlas.png");			// 이펙트 연기 아틀라스

	// level select
	LOADTEX(L"LevelSelectBtn_Editor_MouseOn", L"texture\\1-cutout.png");			// 레벨 선택 버튼 UI - 에디터 마우스
	LOADTEX(L"LevelSelectBtn_Select_MouseOn", L"texture\\2-cutout.png");			// 레벨 선택 버튼 UI - 선택 마우스
	LOADTEX(L"LevelSelectBtn_Editor_Default", L"texture\\ModeSelect1.png");			// 레벨 선택 버튼 UI - 에디터 기본
	LOADTEX(L"LevelSelectBtn_Select_Default", L"texture\\ModeSelect2.png");			// 레벨 선택 버튼 UI - 선택 기본

	// pause
	LOADTEX(L"Pause_txt",				L"texture\\ingame\\pause\\Pause_title_txt.png");			// pause 텍스트 이미지
	LOADTEX(L"Pause_numimg_atlas",		L"texture\\ingame\\pause\\Pause_restart_num_atlas.png");	// pause->restart 선택 시 띄워줄 숫자 아틀라스
	LOADTEX(L"Pause_select_atlas",		L"texture\\ingame\\pause\\Pause_select_atlas.png");			// pause 선택지
	LOADTEX(L"Pause_speedBackground",	L"texture\\ingame\\pause\\Pause_speed_bg.png");				// pause 에서 간이 설정 변경 - speed 배경
	/*background animation render on off 추가해야해.*/

	// note
	LOADTEX(L"sidetrack_come_atlas",	L"texture\\ingame\\note\\analog_stroke_atlas.png");			// sidetrack 예고 애니메이션 아틀라스
	LOADTEX(L"sidetrack_atlas",			L"texture\\ingame\\note\\note_analog_shine_atlas.png");		// 노트 - sidetrack
	LOADTEX(L"note_blue",				L"texture\\ingame\\note\\Note_b.png");						// 노트 - 파랑(안 쪽에 위치)
	LOADTEX(L"note_white",				L"texture\\ingame\\note\\Note_w.png");						// 노트 - 하양(바깥 쪽에 위치)

	// gear
	LOADTEX(L"gear_blueline_click",		L"texture\\ingame\\gear\\Gear_clicked_line_w.png");			// gear - 파란 라인 클릭
	LOADTEX(L"gear_whiteline_click",	L"texture\\ingame\\gear\\Gear_clicked_line_b.png");			// gear - 하얀 라인 클릭
	LOADTEX(L"gear_click_atlas",		L"texture\\ingame\\gear\\btn_4k_hit_176_atlas.png");		// gear - 파란 클릭
	LOADTEX(L"gear_default",			L"texture\\ingame\\gear\\gear_default_redline.png");		// gear - 기어 이미지
	/*gear line shine 효과 추가해야 해.*/

	// coolbomb
	LOADTEX(L"coolbomb_atlas",			L"texture\\ingame\\coolbomb\\coolbomb_atlas.png");			// coolbomb - 기본 판정 아틀라스
	LOADTEX(L"coolbomb_max_atlas",		L"texture\\ingame\\coolbomb\\coolbomb_max_atlas.png");		// coolbomb - max 판정 아틀라스
#pragma endregion  
	
	// Sound Load
#pragma region LOAD_SOUND
	LOADSND(L"mainBGM", L"sound\\DM.wav");					// 메인 BGM

	// effect sound
	LOADSND(L"effect_swoosh", L"sound\\swoosh-sound-effect.wav");					// 바람 효과음
	LOADSND(L"effect_interface", L"sound\\interface-effect.wav");					// 인터페이스 효과음
	LOADSND(L"effect_fast", L"sound\\fast-whoosh.wav");					// 인터페이스 효과음

	
	// 음원은 근데... 파일에서 불러오는 기능이 있으면 그 기능을 사용하면 되지 않을까?
	// 일단 불러오자.
	LOADSND(L"mainBGM", L"sound\\Grievous Lady.wav");		// 음원 1

#pragma endregion

	LOG(LOG_LEVEL::LOG, L"에셋을 저장했습니다.");
	////// 
	
	// init level
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// level 실행
	::ChangeLevel(LEVEL_TYPE::START_LEVEL);

}

void CLevelMgr::tick()
{
	if (nullptr != m_pCurLevel)
		m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	if (nullptr == m_pCurLevel)
		return;

	// 화면 Clear
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	Rectangle(_dc, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// 레벨 render
	m_pCurLevel->render(_dc);

	// Log manager tick(겸사겸사)
	CLogMgr::GetInst()->tick(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	// 만약 현재 레벨 => 현재 레벨로 이동 시 레벨을 전환하는 의미가 없음.
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	// 레벨 생성 여부
	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->enter();

	m_pCurLevel->begin();
}