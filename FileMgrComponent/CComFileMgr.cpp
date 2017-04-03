////////////////////////////////////////////////////////////////////////
//  CComFileMgr.cpp - Declaration of the CCComFileMgr                 //
//  ver 1.2                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CComFileMgr.h"


// CCComFileMgr


// convert a BSTR to a std::string. 
std::string BstrToStdString(const BSTR bstr, int cp = CP_UTF8)
{

	std::wstring ws(bstr);
	std::string dst(ws.begin(), ws.end());
	return  dst;
}


STDMETHODIMP CCComFileMgr::addPattern(BSTR in_pattern)
{
	// TODO: Add your implementation code here
	if (!_pFileMgr) {
		return E_FAIL;
	}
	std::string pattern = BstrToStdString(in_pattern);
	_pFileMgr->addPattern(pattern);
	return S_OK;
}


STDMETHODIMP CCComFileMgr::addPath(BSTR in_path)
{
	// TODO: Add your implementation code here
	std::string path = BstrToStdString(in_path);
	_pFileMgr = new FileMgr(path);
	
	return S_OK;
}


STDMETHODIMP CCComFileMgr::search()
{
	// TODO: Add your implementation code here
	if (!_pFileMgr) {
		return E_FAIL;
	}
	_pFileMgr->search();
	return S_OK;
}


STDMETHODIMP CCComFileMgr::provideTextSearchEngineStringToSearch(BSTR in_stringToBeSearched)
{
	// TODO: Add your implementation code here
	if (!_pFileMgr) {
		return E_FAIL;
	}
	std::string stringToBeSearched = BstrToStdString(in_stringToBeSearched);
	_pFileMgr->provideTextSearchEngineStringToSearch(stringToBeSearched);
	return S_OK;
}
