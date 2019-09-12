#pragma once

namespace JitGrabber
{

    class ClassFactory :
        public IClassFactory
    {

    public:

		ClassFactory()
		{

		}

		virtual ~ClassFactory() { }

        //
        // IUnknown methods.
        //

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID		riid,
            void		**ppvObject);

		virtual ULONG STDMETHODCALLTYPE AddRef()
		{
			scoped_lock lock(m_mutexRef);

			++m_scRef;
			return ++m_cRef;
		}

        virtual ULONG STDMETHODCALLTYPE Release()
        {
			scoped_lock lock(m_mutexRef);

			--m_scRef;
			--m_cRef;

			if (m_cRef == 0)
			{
				delete this;
				return 0;
			}
			else
				return m_cRef;
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

		ULONG m_cRef;
		static ULONG m_scRef;

		static mutex m_mutexRef;

	};

}
