// JittedCodeDumpProfiler.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "ClassFactory.h"
using JittedCodeDumpProfiler::ClassFactory;

#include "CorProfilerCallback.h"
using JittedCodeDumpProfiler::CorProfilerCallback;


// typedef long HRESULT


// Returns a class factory to create an object of the requested type.
extern "C" HRESULT __stdcall DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    wcerr << L"[" __FUNCTIONW__ "]" << endl;

    ClassFactory *pClassFactory;      // To create class factory object.

    if (rclsid == __uuidof(CorProfilerCallback))
    {
        // Allocate the new factory object.
        pClassFactory = new ClassFactory();
        if (!pClassFactory)
            return E_OUTOFMEMORY;

        // Pick the v-table based on the caller's request.
        HRESULT hr = pClassFactory->QueryInterface(riid, ppv);

        // Always release the local reference, if QI failed it will be
        // the only one and the object gets freed.
        pClassFactory->Release();

        return hr;
    }
    else
        return CLASS_E_CLASSNOTAVAILABLE;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
    wcerr << L"[" __FUNCTIONW__ "]" << endl;

    return ClassFactory::AllRefCount() + CorProfilerCallback::AllRefCount() == 0 ? S_OK : S_FALSE;
}