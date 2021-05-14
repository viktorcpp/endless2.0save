#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <mutex>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <experimental/filesystem>
#include <io.h>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <windows.h>

#pragma comment(lib,  "winmm.lib")
#pragma comment(lib,  "ws2_32.lib")

#include    <winuser.h>
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#define WHEEL_DELTA   120
#endif

#include <resource.h>

using namespace std;
namespace fs = std::experimental::filesystem;
