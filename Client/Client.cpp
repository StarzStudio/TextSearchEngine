////////////////////////////////////////////////////////////////////////
//  Client.cpp                                                        //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////

#include "Client.h"

int Client::initFileMgrComponent() {

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (!SUCCEEDED(hr))
	{
		std::wcout << L"\n  could not initialize COM";
	}
	try
	{
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


int main(int argc, char *argv[])
{
	std::string path = argv[2];
	std::string stringToBeSearched = argv[1];
	Client c;
	c.addPath(path);
	for (int i = 3; i < argc; i++)
	{
		c.addPattern(argv[i]);
	}

	c.provideTextSearchEngineStringToSearch(stringToBeSearched);
	c.search();

	
	// wait all the file to be dequeued and print out their results
	::Sleep(3000);
	exit(0);
}

