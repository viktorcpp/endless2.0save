#pragma once

//#define DUK_COMPILING_DUKTAPE
//#include <duk_config.h>
#undef DUK_USE_DATE_NOW_WINDOWS_SUBMS
#define DUK_USE_DATE_NOW_WINDOWS

#include <duktape.h>
#undef DUK_USE_DATE_NOW_WINDOWS_SUBMS
#define DUK_USE_DATE_NOW_WINDOWS

#ifndef _DEBUG
#pragma comment(lib, "duktape.lib")
#else
#pragma comment(lib, "duktape_d.lib")
#endif
