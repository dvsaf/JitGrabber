#pragma once

#include <stdint.h>
#include <stddef.h>

typedef uint32_t ULONG32;

typedef unsigned short USHORT;
typedef uint32_t ULONG;
typedef uint32_t     DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
//typedef unsigned short      WORD;
//typedef float               FLOAT;
//typedef FLOAT* PFLOAT;
//typedef BOOL near* PBOOL;
//typedef BOOL far* LPBOOL;
//typedef BYTE near* PBYTE;
//typedef BYTE far* LPBYTE;
//typedef int near* PINT;
//typedef int far* LPINT;
//typedef WORD near* PWORD;
//typedef WORD far* LPWORD;
//typedef long far* LPLONG;
//typedef DWORD near* PDWORD;
//typedef DWORD far* LPDWORD;
//typedef CONST void far* LPCVOID;
//
//typedef int                 INT;
typedef unsigned int        UINT;
//typedef unsigned int* PUINT;
//

typedef uintptr_t UINT_PTR;
typedef size_t SIZE_T;

typedef char16_t WCHAR;
typedef WCHAR* NWPSTR, * LPWSTR, * PWSTR;
typedef const WCHAR* LPCWSTR, * PCWSTR;


typedef void* PVOID;
typedef void* LPVOID;
typedef const BYTE* LPCBYTE;

typedef void* HANDLE;

struct GUID {
	unsigned int  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
};
typedef GUID IID;
typedef GUID CLSID;

#define REFGUID const GUID &
#define REFIID const IID &
#define REFCLSID const CLSID &

inline int IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
	return
		rguid1.Data1 == rguid2.Data1 &&
		rguid1.Data2 == rguid2.Data2 &&
		rguid1.Data3 == rguid2.Data3 &&
            rguid1.Data4[0] == rguid2.Data4[0] &&
            rguid1.Data4[1] == rguid2.Data4[1] &&
            rguid1.Data4[2] == rguid2.Data4[2] &&
            rguid1.Data4[3] == rguid2.Data4[3] &&
            rguid1.Data4[4] == rguid2.Data4[4] &&
            rguid1.Data4[5] == rguid2.Data4[5] &&
            rguid1.Data4[6] == rguid2.Data4[6] &&
            rguid1.Data4[7] == rguid2.Data4[7];
}

inline bool operator==(REFGUID guidOne, REFGUID guidOther)
{
	return !!IsEqualGUID(guidOne, guidOther);
}

inline bool operator!=(REFGUID guidOne, REFGUID guidOther)
{
	return !(guidOne == guidOther);
}

typedef uint32_t HRESULT;

// Разделить на 32/64
#define STDMETHODCALLTYPE 
