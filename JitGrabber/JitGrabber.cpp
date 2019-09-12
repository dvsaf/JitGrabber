// JittedCodeDumpProfiler.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "ClassFactory.h"
using JitGrabber::ClassFactory;

#include "CorProfilerCallback.h"
using JitGrabber::CorProfilerCallback;
using JitGrabber::CLSID_CorProfilerCallback;

//void wprint_guid(const GUID& guid)
//{
//    wcerr << setw(2) << setfill(L'0') << hex << guid.Data1 << L"-" << guid.Data2 << L"-" << guid.Data3 << L"-"
//    << guid.Data4[0] << guid.Data4[1] << guid.Data4[2] << guid.Data4[3]
//    << guid.Data4[4] << guid.Data4[5] << guid.Data4[6] << guid.Data4[7] << endl;
//}

extern "C" HRESULT __stdcall DllGetClassObject(/* _In_ */ REFCLSID rclsid, /* _In_ */ REFIID riid, /* _Outptr_ */ LPVOID* ppv)
{
//    wcerr << L"[DllGetClassObject]" << endl;
//    wprint_guid(rclsid);
//    wprint_guid(CLSID_CorProfilerCallback);
//
//    wcerr << (IsEqualGUID(rclsid, CLSID_CorProfilerCallback) ? L"  true" : L"  false") << endl;

    if (rclsid == CLSID_CorProfilerCallback)
    {
//        wcerr << L" equal" << endl;
		ClassFactory* pClassFactory = new ClassFactory();
		if (pClassFactory == 0)
			return E_OUTOFMEMORY;

		HRESULT hr = pClassFactory->QueryInterface(riid, ppv);
		if (FAILED(hr))
			delete pClassFactory;
		return hr;
	}
    else
        return CLASS_E_CLASSNOTAVAILABLE;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
//    wcerr << L"[DllCanUnloadNow]" << endl;

    return CorProfilerCallback::AllRefCount() == 0 ? S_OK : S_FALSE;
}
