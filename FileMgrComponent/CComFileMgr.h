
#ifndef CCOMFILEMGR_H
#define CCOMFILEMGR_H
////////////////////////////////////////////////////////////////////////
//  CComFileMgr.h - Declaration of the CCComFileMgr                   //
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
* This package wrap the FileMgr static library
*
* Config:
* -------------------
* 1. call addPath(BSTR) first, it will new a instance for pFileMgr inside and pass the path for it to init.
* 2. call addPattern(BSTR) to add patterns for fileMgr and call search() to let FileMgr start processing.
* 3. call provideTextSearchEngineStringToSearch(BSTR) to init text search engine
* Then we can call search()
*
* Public interface:
* ----------------
* addPattern(BSTR)        add pattern for fileMgr
* addPath(BSTR);          add path for fileMgr and new an instance for _pFileMgr
* search()		          call search method in fileMgr library
* 
* Build Process:
* --------------
* Required files: 
*	FileMgr.h, FileMgr.cpp, IFileMgr.h,
*   FileSystem.h, FileSystem.cpp
*   TextSearchComponent_i.h， TextSearchComponent_i.c
*   TextSearch.h, TextSearch.cpp
*	BlockingQueue.h  BlockingQueue.cpp
*   Utilities.h, Utilities.cpp
*	Tasks.h, Tasks.cpp
*   ThreadPool.h, ThreadPool.cpp
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
		if (_pFileMgr) {
			delete _pFileMgr;
		}
	}

public:

	FileMgr * _pFileMgr;

	//----< add pattern for fileMgr >-------

	STDMETHOD(addPattern)(BSTR in_pattern);

	//----< add path for fileMgr and new an instance for _pFileMgr >-------

	STDMETHOD(addPath)(BSTR in_path);

	//----< call search method in  fileMgr >-------

	STDMETHOD(search)();

	//----< inject string to be searched for fileMgr to help it init text search engine >-------

	STDMETHOD(provideTextSearchEngineStringToSearch)(BSTR in_stringToBeSearched);
};



OBJECT_ENTRY_AUTO(__uuidof(CComFileMgr), CCComFileMgr)

#endif