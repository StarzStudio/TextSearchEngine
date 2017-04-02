// CComFileMgr.h : Declaration of the CCComFileMgr

#pragma once
#include "resource.h"       // main symbols

#include "FileMgrComponent_i.h"
#include "../FileMgr/FileMgr.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace FileManager;

// CCComFileMgr

class ATL_NO_VTABLE CCComFileMgr :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCComFileMgr, &CLSID_CComFileMgr>,
	public IDispatchImpl<ICComFileMgr, &IID_ICComFileMgr, &LIBID_FileMgrComponentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCComFileMgr()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CCOMFILEMGR)


BEGIN_COM_MAP(CCComFileMgr)
	COM_INTERFACE_ENTRY(ICComFileMgr)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		if (!_pFileMgr) {
			delete _pFileMgr;
		}
	}

public:

	FileMgr * _pFileMgr;
	STDMETHOD(addPattern)(BSTR in_pattern);
	STDMETHOD(addPath)(BSTR in_path);
	STDMETHOD(search)();
};



OBJECT_ENTRY_AUTO(__uuidof(CComFileMgr), CCComFileMgr)
