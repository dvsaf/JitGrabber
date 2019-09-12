// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "WindowsDefinitions.h"
#include "WindowsErrorsDefinitions.h"

#include "ComDefinitions.h"

#include "CorHeadersDefinitions.h"
#include "CorDefinitions.h"
#include "CorDebugDefinitions.h"
#include "CorProfilingDefinitions.h"

#include <iostream>
using std::cout;
using std::endl;
using std::hex;
using std::ios;

#include <iomanip>
using std::setfill;
using std::setw;
using std::setiosflags;

#include <string>
using std::string;
using std::wstring;

#include <codecvt>
using std::wstring_convert;
using std::codecvt_utf8_utf16;

#include <sstream>
using std::stringstream;

#include <vector>
using std::vector;

#include <mutex>
using std::mutex;
using std::scoped_lock;

#include "capstone/capstone.h"
