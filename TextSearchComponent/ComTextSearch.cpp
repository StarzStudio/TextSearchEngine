// ComTextSearch.cpp : Implementation of CComTextSearch

#include "stdafx.h"
#include "ComTextSearch.h"


// CComTextSearch


// convert a BSTR to a std::string. 
std::string BstrToStdString(const BSTR bstr, int cp = CP_UTF8)
{
	std::wstring ws(bstr);
	std::string dst(ws.begin(), ws.end());
	return  dst;
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


STDMETHODIMP CComTextSearch::init_engine(BSTR in_pattern)
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
