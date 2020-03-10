// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <d3dx9.h>
// 부가적인 기능들이 들어있다. 벡터, 행렬등등. 
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

#include <time.h>

#include "Include.h"