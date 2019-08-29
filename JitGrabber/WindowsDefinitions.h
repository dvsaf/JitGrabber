#pragma once

#include <stdint.h>
#include <stddef.h>

typedef uint32_t ULONG32;

typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef unsigned long       DWORD;
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

typedef wchar_t WCHAR;
typedef WCHAR* NWPSTR, * LPWSTR, * PWSTR;
typedef const WCHAR* LPCWSTR, * PCWSTR;


typedef void* PVOID;
typedef void* LPVOID;
typedef const BYTE* LPCBYTE;

typedef void* HANDLE;

struct GUID {
	unsigned long  Data1;
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
	return (
		((unsigned long*)& rguid1)[0] == ((unsigned long*)& rguid2)[0] &&
		((unsigned long*)& rguid1)[1] == ((unsigned long*)& rguid2)[1] &&
		((unsigned long*)& rguid1)[2] == ((unsigned long*)& rguid2)[2] &&
		((unsigned long*)& rguid1)[3] == ((unsigned long*)& rguid2)[3]);
}

inline bool operator==(REFGUID guidOne, REFGUID guidOther)
{
	return !!IsEqualGUID(guidOne, guidOther);
}

inline bool operator!=(REFGUID guidOne, REFGUID guidOther)
{
	return !(guidOne == guidOther);
}

typedef long HRESULT;

// Разделить на 32/64
#define STDMETHODCALLTYPE 
