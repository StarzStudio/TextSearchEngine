// CComFileMgr.cpp : Implementation of CCComFileMgr

#include "stdafx.h"
#include "CComFileMgr.h"


// CCComFileMgr


// convert a BSTR to a std::string. 
std::string BstrToStdString(const BSTR bstr, int cp = CP_UTF8)
{

	std::wstring ws(bstr);
	std::string dst(ws.begin(), ws.end());
	return  dst;

	//std::string dst;
	//if (!bstr)
	//{
	//	// define NULL functionality. I just clear the target.
	//	dst.clear();
	//	return dst;
	//}

	//// request content length in single-chars through a terminating
	////  nullchar in the BSTR. note: BSTR's support imbedded nullchars,
	////  so this will only convert through the first nullchar.
	//int res = WideCharToMultiByte(cp, 0, bstr, -1, NULL, 0, NULL, NULL);
	//if (res > 0)
	//{
	//	dst.resize(res);
	//	WideCharToMultiByte(cp, 0, bstr, -1, &dst[0], res, NULL, NULL);
	//}
	//else
	//{    // no content. clear target
	//	dst.clear();
	//}
	//return dst;
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
	_pFileMgr->search();
	return S_OK;
}
