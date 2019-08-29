// JittedCodeDumpProfiler.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "ClassFactory.h"
using JitGrabber::ClassFactory;

#include "CorProfilerCallback.h"
using JitGrabber::CorProfilerCallback;
using JitGrabber::CLSID_CorProfilerCallback;

extern "C" HRESULT __stdcall DllGetClassObject(/* _In_ */ REFCLSID rclsid, /* _In_ */ REFIID riid, /* _Outptr_ */ LPVOID* ppv)
{
    wcerr << L"[" __FUNCTIONW__ "]" << endl;

    if (rclsid == CLSID_CorProfilerCallback)
    {
        return ClassFactory::SingleObject().QueryInterface(riid, ppv);
    }
    else
        return CLASS_E_CLASSNOTAVAILABLE;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
    wcerr << L"[" __FUNCTIONW__ "]" << endl;

    return CorProfilerCallback::AllRefCount() == 0 ? S_OK : S_FALSE;
}
