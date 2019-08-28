#pragma once

static const IID IID_IUnknown = { 0x00000000, 0x0000, 0x0000, { 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

struct IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void **ppvObject) = 0;

	virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;

	virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

};

static const IID IID_IClassFactory = { 0x00000001, 0x0000, 0x0000, { 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

struct IClassFactory : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE CreateInstance(
		/* [annotation][unique][in] */
		_In_opt_  IUnknown * pUnkOuter,
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][iid_is][out] */
		_COM_Outptr_  void** ppvObject) = 0;

	virtual HRESULT STDMETHODCALLTYPE LockServer(
		/* [in] */ BOOL fLock) = 0;

};


