#pragma once

// default
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// debug
#include <crtdbg.h> // 메모리 누수 체크를 위한 crtdbg.h
#include <assert.h>

// container
#include <vector>
#include <list>
#include <map>
#include <string>

// pragma comment
#pragma comment(lib, "Msimg32.lib") // TranceparentBlt 사용 시 필요



// using
using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;


// global => define.h, struct.h, func.h (사용자 정의)
#include "global.h"

// GDI+ (알파 블렌딩)
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace::Gdiplus;

// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")