#ifndef CLIENT_H
#define CLIENT_H

////////////////////////////////////////////////////////////////////////
//  Client.h                                                          //
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
* This package serves as test executive to call FileMgr Component.
*
* Config:
* -------------------
* 1. provide path and patterns by using addPath(), addPattern(),
* 2. Then init FileMgr Component by calling initFileMgrComponent()
* 3. call search to start processing.
*
* Public interface:
* ----------------
* search()               start processing
* initFileMgrComponent();          init FileMgr Component
*
* Build Process:
* --------------
* Required files: 
		FileMgrComponent_i.h , FileMgrComponent_i.c
		FileMgr.h, FileMgr.cpp, IFileMgr.h,
		FileSystem.h, FileSystem.cpp
		TextSearchComponent_i.h， TextSearchComponent_i.c
		TextSearch.h, TextSearch.cpp
		BlockingQueue.h  BlockingQueue.cpp
		Utilities.h, Utilities.cpp
		Tasks.h, Tasks.cpp
		ThreadPool.h, ThreadPool.cpp

*
* Build Command: devenv TextSearch.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.2 : 30 Mar 2017
* - add callback function in searchTotal() to inform client of the finishing of program
* ver 1.1 : 28 Mar 2016
* - remove injected searchAlgorithm member, use std::string.find() to search substring
* ver 1.0 : 27 Mar 2017
* - first release
*
*/


#include "../FileMgrComponent/FileMgrComponent_i.h"
#include <atlbase.h>
#include <atlsafe.h>
#include <iostream>
#include <vector>
#include <string>

class Client{
	
	using pattern = std::string;
	using patterns = std::vector<pattern>;
	using path = std::string;
public:
	Client() {
		initFileMgrComponent();
	}
	~Client() {
		CoUninitialize();
	}

	//----< add pattern for FileMgr Component>-------

	void addPattern(pattern in_pattern) {
	
			BSTR patternBSTR = stdStringTOBSTR(in_pattern);
			HRESULT hr = pFileMgrComponent->addPattern(patternBSTR);

			if (!SUCCEEDED(hr))
			{
				std::wcout << L"\n   file manager add pattern failed\n\n";
				return;
			}
			else {
				std::wcout << L"\n   file manager add pattern successful\n\n";
			}
		
	}

	//----< add path for FileMgr Component >-------

	void addPath(path in_path) {

	
		BSTR pathBSTR = stdStringTOBSTR(in_path);
		HRESULT hr = pFileMgrComponent->addPath(pathBSTR);
		if (!SUCCEEDED(hr))
		{
			std::wcout << L"\n     init  file manager component failed\n\n";
		}
		else {
			std::wcout << L"\n    init file manager component successful\n\n";
		}
	}

	//----< provide string to be search for FileMgr Component to init text search engine >-------

	void provideTextSearchEngineStringToSearch(std::string in_stringToBeSearched) {
		BSTR stringToBeSearched = this->stdStringTOBSTR(in_stringToBeSearched);
		HRESULT hr = pFileMgrComponent->provideTextSearchEngineStringToSearch(stringToBeSearched);

		if (!SUCCEEDED(hr))
		{
			std::wcout << L"\n     provide searched string for text search engine failed\n\n";
		}
		else {
			std::wcout << L"\n    provide searched string for text search engine successful\n\n";
		}
	}

	//----< call this function to let FileMgr Component start processing >-------

	void search() {
			pFileMgrComponent->search();
		
	}

	//----< call this function init FileMgr Component >-------

	int initFileMgrComponent();
private:

	//----< change std string to BSTR type >-------

	BSTR stdStringTOBSTR(std::string in_string) {

		CComBSTR temp(in_string.c_str());
		BSTR res = temp.Detach();
		return res;
	}
	CComQIPtr<ICComFileMgr> pFileMgrComponent;
};
#endif