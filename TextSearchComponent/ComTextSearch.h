// ComTextSearch.h : Declaration of the CComTextSearch

#pragma once
#include "resource.h"       // main symbols



#include "TextSearchComponent_i.h"
#include "../TextSearch/TextSearch.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CComTextSearch

class ATL_NO_VTABLE CComTextSearch :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CComTextSearch, &CLSID_ComTextSearch>,
	public IDispatchImpl<IComTextSearch, &IID_IComTextSearch, &LIBID_TextSearchComponentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComTextSearch()
	{
	
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMTEXTSEARCH)


BEGIN_COM_MAP(CComTextSearch)
	COM_INTERFACE_ENTRY(IComTextSearch)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		_pTextSearchEngine = NULL;
		return S_OK;
	}

	void FinalRelease()
	{
		if (_pTextSearchEngine != NULL) {
			delete _pTextSearchEngine;
		}
	}

public:

	TextSearch* _pTextSearchEngine;
	STDMETHOD(search)(BSTR in_fileName, BSTR in_pattern, VARIANT_BOOL* result);
	STDMETHOD(init_engine)(BSTR in_pattern);
	STDMETHOD(putFile)(BSTR in_fileName);
};

OBJECT_ENTRY_AUTO(__uuidof(ComTextSearch), CComTextSearch)
