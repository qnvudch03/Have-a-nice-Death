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

// ������ ������ ����ϴ� ��� & �𸮾� �̷��� ���ϴ�.
using int8 = char;					// ���� �����ϴµ� 1bit ¥��
using int16 = short;
using int32 = int;
using int64 = long long;		// �Ź� long long ���� �����Ƽ� int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#include "Defines.h"

