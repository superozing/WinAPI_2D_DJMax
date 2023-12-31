﻿#pragma once

// default
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <algorithm>

// video frame
#include <mfapi.h>
#include <mfidl.h>
#include <Mfreadwrite.h>
#include <mfreadwrite.h>
#include <shlwapi.h>

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "gdiplus.lib")

// FIleIO
#include <commdlg.h>

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

// DirectShow
#include "dshow.h"


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


// using
using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;

// global => define.h, struct.h, func.h (사용자 정의)
#include "global.h"