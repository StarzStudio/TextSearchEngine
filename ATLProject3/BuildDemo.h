// BuildDemo.h : Declaration of the CBuildDemo

#pragma once
#include "resource.h"       // main symbols



#include "ATLProject3_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CBuildDemo

class ATL_NO_VTABLE CBuildDemo :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBuildDemo, &CLSID_BuildDemo>,
	public IDispatchImpl<IBuildDemo, &IID_IBuildDemo, &LIBID_ATLProject3Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CBuildDemo()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BUILDDEMO)


BEGIN_COM_MAP(CBuildDemo)
	COM_INTERFACE_ENTRY(IBuildDemo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



  STDMETHOD(putString)(BSTR str);
  STDMETHOD(getString)(BSTR* str);
};

OBJECT_ENTRY_AUTO(__uuidof(BuildDemo), CBuildDemo)
