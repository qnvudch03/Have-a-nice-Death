#pragma once

//using namespace std;

#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <functional>

#include <d2d1.h>
#include <dwrite_1.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <tuple>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace fs = std::filesystem;

// 엔씨에 있을때 사용하던 방식 & 언리얼도 이렇게 씁니다.
using int8 = char;					// 정수 저장하는데 1bit 짜리
using int16 = short;
using int32 = int;
using int64 = long long;		// 매번 long long 쓰기 귀찮아서 int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#include "Defines.h"

