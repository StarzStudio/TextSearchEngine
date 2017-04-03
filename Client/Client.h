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
	void addPattern(pattern in_pattern) {
		_patterns.push_back(in_pattern);
	}
	void addPath(path in_path) {
		_path = in_path;
	}
	BSTR stdStringTOBSTR(std::string in_string) {
	
		CComBSTR temp(in_string.c_str());
		BSTR res = temp.Detach();
		return res;
	}

	void search() {

		BSTR pathBSTR = stdStringTOBSTR(this->_path);
		HRESULT hr = pFileMgrComponent->addPath(pathBSTR);
		if (!SUCCEEDED(hr))
		{
			std::wcout << L"\n     init  file manager component failed\n\n";
		} 
		else {
			std::wcout << L"\n    init file manager component successful\n\n";

			for (auto _pattern : this->_patterns) {
				BSTR patternBSTR = stdStringTOBSTR(_pattern);
				hr = pFileMgrComponent->addPattern(patternBSTR);

				if (!SUCCEEDED(hr))
				{
					std::wcout << L"\n   file manager add pattern failed\n\n";
					return;
				}
				else {
					std::wcout << L"\n   file manager add pattern successful\n\n";	
				}	
			}

			pFileMgrComponent->search();


		}
		
	}
	int initFileMgrComponent() {

		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		if (!SUCCEEDED(hr))
		{
			std::wcout << L"\n  could not initialize COM";
		}
		try
		{
			HRESULT hr;
			pFileMgrComponent.CoCreateInstance(CLSID_CComFileMgr);
			if (!pFileMgrComponent)
			{
				std::wcout << "\n  failed to create file manager component";
				return -1;
			}
			/*else {
				
			}*/
		}
		catch (std::exception& ex)
		{
			std::wcout << L"\n  " << ex.what() << L"\n\n";
			return -1;
		}
		std::wcout << L"\n\n";

		return 0;		
	}
private:
	path _path;
	patterns _patterns;
	CComQIPtr<ICComFileMgr> pFileMgrComponent;
};
#endif