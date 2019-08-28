#pragma once

namespace JitGrabber
{

    class ClassFactory :
        public IClassFactory
    {

    public:

		static ClassFactory SingleObject()
		{
			return m_sSingleObject;
		}

        //
        // IUnknown methods.
        //

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID		riid,
            void		**ppvObject);

		virtual ULONG STDMETHODCALLTYPE AddRef()
		{
			return 1;
		}

        virtual ULONG STDMETHODCALLTYPE Release()
        {
			return 1;
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

		static ClassFactory m_sSingleObject;

	};

}
