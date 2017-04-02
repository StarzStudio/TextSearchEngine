////////////////////////////////////////////////////////////////////////
//  FileMgr.cpp - declares new parsing rules and actions              //
//  ver 1.1                                                           //
//  Language:      Visual C++ 2016                                    //
//  Platform:      Mac Book Pro, OS X EI Captain 10.11                //
//  Application:   dependency Analysis, 687 OOD Project3              //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University        //
//                 (315) 443-3948, jfawcett@twcny.rr.com              //
////////////////////////////////////////////////////////////////////////
#include "FileMgr.h"
#include "../Utilities/Utilities.h"




using namespace FileManager;

using namespace Utilities;
using Utils = StringHelper;



IFileMgr* FileMgr::pInstance_;

IFileMgr* IFileMgr::getInstance()
{
	return FileMgr::getInstance();
}


struct FileHandler : IFileEventHandler
{
	void execute(const std::string& fileSpec)
	{
		std::cout << "\n  --   " << fileSpec;
	}

	
};

struct DirHandler : IDirEventHandler
{
	void execute(const std::string& dirSpec)
	{
		std::cout << "\n  ++ " << dirSpec;
	}
};

struct DoneHandler : IDoneEventHandler
{
	void execute(size_t numFilesProcessed)
	{
		std::cout << "\n\n  Processed " << numFilesProcessed << " files";
	}
};


//----< test stub >--------------------------------------------------

#ifdef TEST_FILEMGR

#define  NO_useCOM_singleFileSearch
#define  useCOM_wholeFolderSearch
#define NO_normalCPP
//class CallBackContext {
//public:
//	 friend void callback(std::vector<std::string> in_matchedFilesCollection) {
//		for (auto fileName : in_matchedFilesCollection) {
//			std::cout << fileName << std::endl;
//		}
//	}
//
//
//};


int main()
{




#ifdef normalCPP


	// two way to init TextSearch:
	// first:
	TextSearch searchEngine(textPattern);
	// second
	/*BlockingQueue<std::string> fileNameQueue;
	SearchAlgorithm* pAlgorithm = new KmpAlgorithm(textPattern);
	TextSearch searchEngine();
	searchEngine.loadSearchAlgorithm(pAlgorithm);
	searchEngine.loadBlockingQueue(&fileNameQueue);*/
	searchEngine.searchTotal();



	std::string path = FileSystem::Path::getFullFileSpec("..");
	IFileMgr* pFmgr = FileMgrFactory::create(path);

	FileHandler fh;
	DirHandler dh;
	DoneHandler dnh;

	pFmgr->regForFiles(&fh);
	pFmgr->regForDirs(&dh);
	pFmgr->regForDone(&dnh);

	pFmgr->addPattern("*.h");
	pFmgr->addPattern("*.cpp");
	pFmgr->search();
	
	putline();

	std::cout << "\n\n";
#endif
	
#ifdef useCOM_singleFileSearch


	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (!SUCCEEDED(hr))
	{
		std::wcout << L"\n  could not initialize COM";
	}

	try
	{
		HRESULT hr;

		CComQIPtr<IComTextSearch> pTextSearchEngine;
		pTextSearchEngine.CoCreateInstance(CLSID_ComTextSearch);


		if (!pTextSearchEngine)
		{
			std::wcout << "\n  failed to create Text search component";
			return -1;
		}
		else {
			CComBSTR file(L"test.txt");
			CComBSTR pattern(L"algorithm");
		
			VARIANT_BOOL result = 0;
			hr = pTextSearchEngine->search(file, pattern, &result);

			if (SUCCEEDED(hr))
			{
				std::wcout << L"\n    search successful\n\n";
				if (result == VARIANT_TRUE) {
					std::wcout << L"\n    file contains pattern\n\n";
				}
				else {
					std::wcout << L"\n    file contains pattern\n\n";
				}
			}
			else {
				std::wcout << L"\n    search failed\n\n";
			}
		}
	}
	catch (std::exception& ex)
	{
		std::wcout << L"\n  " << ex.what() << L"\n\n";
		return -1;
	}
	std::wcout << L"\n\n";
	CoUninitialize();

	
#endif // using TextSearchComponent



#ifdef useCOM_wholeFolderSearch

	std::string path = FileSystem::Path::getFullFileSpec("..");
	IFileMgr* pFmgr = FileMgrFactory::create(path);

	FileHandler fh;
	DirHandler dh;
	DoneHandler dnh;

	pFmgr->regForFiles(&fh);
	pFmgr->regForDirs(&dh);
	pFmgr->regForDone(&dnh);

	pFmgr->addPattern("*.h");
	pFmgr->addPattern("*.cpp");
	pFmgr->search();


	std::cout << "\n\n";



#endif // using TextSearchComponent and search whole folder

}

#endif