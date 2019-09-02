// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
//#include <windows.h>


#include "WindowsDefinitions.h"
#include "WindowsErrorsDefinitions.h"

#include "ComDefinitions.h"

#include "CorHeadersDefinitions.h"
#include "CorDefinitions.h"
#include "CorDebugDefinitions.h"
#include "CorProfilingDefinitions.h"

#include <iostream>
using std::cerr;
using std::wcerr;
using std::endl;
using std::hex;
using std::ios;

#include <iomanip>
using std::setfill;
using std::setw;
using std::setiosflags;

#include <string>
using std::wstring;

#include <sstream>
using std::wstringstream;

#include <mutex>
using std::mutex;
using std::scoped_lock;

#include "capstone/capstone.h"

#define __FUNCTIONW__ ""
