#include "stdafx.h"
#include "ClassFactory.h"
#include "CorProfilerCallback.h"

namespace JitGrabber
{
	ULONG ClassFactory::m_scRef = 0;
	mutex ClassFactory::m_mutexRef;

    //*****************************************************************************
    //
    //********** Class factory code.
    //
    //*****************************************************************************


    //*****************************************************************************
    // QueryInterface is called to pick a v-table on the co-class.
    //*****************************************************************************
    HRESULT STDMETHODCALLTYPE ClassFactory::QueryInterface(
        REFIID      riid,
        void        **ppvObject)
    {
        HRESULT     hr;

        // Avoid confusion.
        *ppvObject = nullptr;

        // Pick the right v-table based on the IID passed in.
        if (riid == IID_IUnknown)
            *ppvObject = (IUnknown *)this;
        else if (riid == IID_IClassFactory)
            *ppvObject = (IClassFactory *)this;

        // If successful, add a reference for out pointer and return.
        if (*ppvObject)
        {
            hr = S_OK;
            AddRef();
        }
        else
            hr = E_NOINTERFACE;
        
        return hr;
    }


    //*****************************************************************************
    // CreateInstance is called to create a new instance of the coclass for which
    // this class was created in the first place.  The returned pointer is the
    // v-table matching the IID if there.
    //*****************************************************************************
    HRESULT STDMETHODCALLTYPE ClassFactory::CreateInstance(
        IUnknown    *pUnkOuter,
        REFIID      riid,
        void        **ppvObject)
    {
        HRESULT     hr = E_FAIL;

        // Avoid confusion.
        *ppvObject = NULL;

        // Aggregation is not supported by these objects.
        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;

        CorProfilerCallback* pCorProfilerCallback = new CorProfilerCallback();
        if (pCorProfilerCallback == 0)
            return E_OUTOFMEMORY;

        hr = pCorProfilerCallback->QueryInterface(riid, ppvObject);
        if (FAILED(hr))
            delete pCorProfilerCallback;
        return hr;
    }

    HRESULT STDMETHODCALLTYPE
        ClassFactory::LockServer(
            BOOL fLock)
    {
        // @FUTURE: Should we return E_NOTIMPL instead of S_OK?
        return S_OK;
    }

}
