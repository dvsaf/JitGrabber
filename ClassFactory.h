#pragma once

namespace JittedCodeDumpProfiler
{

    class ClassFactory :
        public IClassFactory
    {
    public:

        ClassFactory()
            : m_cRef(1)
        { }

        virtual ~ClassFactory() {}

        static ULONG AllRefCount()
        {
            return m_scRef;
        }

        //
        // IUnknown methods.
        //

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID		riid,
            void		**ppvObject);

        virtual ULONG STDMETHODCALLTYPE AddRef()
        {
            InterlockedIncrement(&m_scRef);
            return InterlockedIncrement(&m_cRef);
        }

        virtual ULONG STDMETHODCALLTYPE Release()
        {
            InterlockedDecrement(&m_scRef);
            LONG		cRef = InterlockedDecrement(&m_cRef);
            if (cRef <= 0)
                delete this;
            return (cRef);
        }


        //
        // IClassFactory methods.
        //

        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
            IUnknown	*pUnkOuter,
            REFIID		riid,
            void		**ppvObject);

        virtual HRESULT STDMETHODCALLTYPE LockServer(
            BOOL		fLock);


    private:

        ULONG		m_cRef;						// Reference count.
        static ULONG		m_scRef;						// Reference count.
    };

}
