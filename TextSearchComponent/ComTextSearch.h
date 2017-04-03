
#ifndef COMTEXTSEARCH_H
#define COMTEXTSEARCH_H
////////////////////////////////////////////////////////////////////////
//  ComTextSearh.h - Declaration of the CComTextSearch                //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package wraps TextSearch package as a component and expose to outside as a DLL.
*
* Config:
* -------------------
* Call init_engine(BSTR) first, it will new a instance for inside pTextSearch pointer and 
* let pTextSearch start dequeuing on it's default blocking queue.
*
* Public interface:
* ----------------
* putFile(BSTR)					     put filename into blocking queue.
* init_engine(BSTR)                   new a TextSearch instance for pTextSearch pointer inside.
*
* Build Process:
* --------------
* Required files: 
*                 
*                 TextSeach.h, TextSeach.cpp
*				  Tasks.h, Tasks.cpp
*                 ThreadPool.h, ThreadPool.cpp
*				  BlockingQueue.h  BlockingQueue.cpp
*			      Utilities.h, Utilities.cpp
*
*
*
* Build Command: devenv TextSearch.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 27 Mar 2017
* - first release
*
*/




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

	//----< search a single file >-------------------------------

	STDMETHOD(search)(BSTR in_fileName, BSTR in_pattern, VARIANT_BOOL* result);

	//----< new a instance for _pTextSearchEngine, and let it listening and dequeuing from queue >-------------------------------

	STDMETHOD(init_engine)(BSTR in_pattern);

	//----< push a file into blocking queue >-------------------------------

	STDMETHOD(putFile)(BSTR in_fileName);
};

OBJECT_ENTRY_AUTO(__uuidof(ComTextSearch), CComTextSearch)

#endif