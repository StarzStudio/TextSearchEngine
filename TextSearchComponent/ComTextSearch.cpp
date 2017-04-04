////////////////////////////////////////////////////////////////////////
//  ComTextSearh.cpp - Declaration of the CComTextSearch              //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ComTextSearch.h"

// convert a BSTR to a std::string. 
std::string BstrToStdString(const BSTR bstr, int cp = CP_UTF8)
{
	std::wstring ws(bstr);
	std::string dst(ws.begin(), ws.end());
	return  dst;
}


STDMETHODIMP CComTextSearch::search(BSTR fileName, BSTR pattern, VARIANT_BOOL* result)
{
	// TODO: Add your implementation code here
	std::string _pattern = BstrToStdString(pattern);
	std::string _fileName = BstrToStdString(fileName);
	TextSearch seachEngine(_pattern);
	
	int _result = seachEngine.search(_fileName);
	if (_result == -1) {
		*result = VARIANT_FALSE;
	}
	else {
		*result = VARIANT_TRUE;
	}
	return S_OK;
}


STDMETHODIMP CComTextSearch::init_engine (BSTR in_pattern)
{
	std::string _pattern = BstrToStdString(in_pattern);
	// TODO: Add your implementation code here
	_pTextSearchEngine = new TextSearch(_pattern);
	_pTextSearchEngine->searchTotal();
	return S_OK;
}


STDMETHODIMP CComTextSearch::putFile(BSTR in_fileName)
{
	// TODO: Add your implementation code here
	std::string fileName = BstrToStdString(in_fileName);
	if (!_pTextSearchEngine) {
		 std::wcout << "\n  please init TextSearchEngine first";
		 return E_FAIL;;
	}
	_pTextSearchEngine->putFile(fileName);
	return S_OK;
}
