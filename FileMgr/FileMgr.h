﻿#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
// FileMgr.h - find files matching specified patterns                //
//             on a specified path                                   //
// ver 3.0                                                           //
// Modified by Xing Zhou										     //
// Author: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a class, FileMgr, and object factory function,
* Create().  It's mission is to search the directory tree, rooted at
* a specified path, looking for files that match a set of specified
* patterns.
*
* It provides virtual functions file(...), dir(...), and done(), which
* an application can override to provide application specific processing
* for the events: file found, directory found, and finished processing.
*
* The package also provides interface hooks that serve the same purpose
* but allow multiple receivers for those events.

* Config:
* -------------------
* Call provideTextSearchEngineStringToSearch(std::string) to init Text Search Engine before using/
*
* Required Files:
* ---------------
*
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
* Build Process:
* --------------
*   devenv FileMgr.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 3.0 : 03 Apr 2017
* - will call text search component
* ver 2.2 : 28 Aug 2016
* - added more prologue comments
* ver 2.1 : 31 Jul 2016
* - added virtual file, dir, and done functions
* - this lets application override instead of registering for event
* ver 2.0 : 12 Mar 2016
* - fixes bug in directory recursion in find(path)
* - reduces scope of for loop in find for efficiency
* ver 1.0 : 11 Mar 2016
* - first release
*/

#include "IFileMgr.h"
#include "../FileSystem/FileSystem.h"
#include "../TextSearch/TextSearch.h"
#include "../TextSearchComponent/TextSearchComponent_i.h"
#include <atlbase.h>
#include <atlsafe.h>
#include <iostream>
#include <sstream>
#include "../Logger/Logger.h"

using namespace ATL;

namespace FileManager
{
	class FileMgr : public IFileMgr
	{
		using Pattern = std::string;
		using Patterns = std::vector<Pattern>;
		using File = std::string;
		using Files = std::vector<File>;
		using Dir = std::string;
		using Dirs = std::vector<Dir>;
		using Path = std::string;
		using fileSubscribers = std::vector<IFileEventHandler*>;
		using dirSubscribers = std::vector<IDirEventHandler*>;
		using doneSubscribers = std::vector<IDoneEventHandler*>;
	public:
		virtual ~FileMgr() { 

			CoUninitialize();
			 if (pText) {
				 delete pText;
			 }
		}

		//----< set default file pattern >-------------------------------

		FileMgr(const std::string& path)
		{
			// default: search anything
			path_ = FileSystem::Path::getFullFileSpec(path);
			patterns_.push_back("*.*");
			pInstance_ = this;
			logger.attach(&std::cout);
			logger.start();
			pText = NULL;
		}
		//----< return instance of FileMgr >-----------------------------

		static IFileMgr* getInstance()
		{
			return pInstance_;
		}
		//----< add file pattern, removing default on first call >-------

		void addPattern(const std::string& patt)
		{
			if (patterns_.size() == 1 && patterns_[0] == "*.*")
				patterns_.pop_back();
			patterns_.push_back(patt);
		}

		//----< provide search string for text Search engine >------

		void provideTextSearchEngineStringToSearch(const std::string& in_stringToBeSearched) {
		
			initTextSearchComponent(in_stringToBeSearched);
		}

		//----< applications can overload this or reg for fileEvt >------

		virtual void file(const File& f)
		{
			std::string msg;
			++numFilesProcessed;
			for (auto pEvtHandler : fileSubscribers_)
			{
				pEvtHandler->execute(f);
			}
			CComBSTR temp(f.c_str());
			BSTR fileName = temp.Detach();
			
			HRESULT hr = pTextSearchEngine->putFile(fileName);
			if (!SUCCEEDED(hr))
			{
				msg = "\n  could not put file name: " + f + " into queue";
				logger.write(msg);
			}
			msg =  "\n> enqueue file: " + f;
			logger.write(msg);
			//std::cout << "\n  --   putting file: " << f << " into blocking queue";
			//pText->putFile(f);
		}
		//----< applications can overload this or reg for dirEvt >-------

		virtual void dir(const Dir& fpath)
		{
			for (auto pEvtHandler : dirSubscribers_)
			{
				pEvtHandler->execute(fpath);
			}
			if (fpath.find(".git") ==  std::string::npos) {
			//	std::cout << "\n  ++ " << fpath;
			}
			
		}
		//----< applications can overload this or reg for doneEvt >------

		virtual void done()
		{
			std::string msg;
			for (auto pEvtHandler : doneSubscribers_)
			{
				pEvtHandler->execute(numFilesProcessed);
			}
			std::string endSignal("endOfTextSearch");
			//pText->putFile(endSignal);
			CComBSTR temp(endSignal.c_str());
			BSTR signal = temp.Detach();
			HRESULT hr = pTextSearchEngine->putFile(signal);
			if (!SUCCEEDED(hr))
			{
				msg = "\n  could not put end signal into queue";
				logger.write(msg);
		
			}
			
			msg =  "\n\n  Processed " + std::to_string(numFilesProcessed) + " files in the path: \"" + 
				path_ + "\" \n\n";
			logger.write(msg);
			
			return;
		}
		//----< start search on previously specified path >--------------

		void search()
		{
			find(path_);
			done();
		}
		//----< search current path including subdirectories >-----------

		void find(const std::string& path)
		{
			Path fpath = FileSystem::Path::getFullFileSpec(path);
			dir(fpath);
			for (auto patt : patterns_)
			{
				Files files = FileSystem::Directory::getFiles(fpath, patt);
				for (auto f : files)
				{
					// This _file name is with relative path as suffix
					File _file = FileSystem::Path::fileSpec(path, f);
					file(_file);
				}
			}
			Dirs dirs = FileSystem::Directory::getDirectories(fpath);
			for (auto d : dirs)
			{
				if (d == "." || d == "..")
					continue;
				Path dpath = fpath + "\\" + d;
				find(dpath);
			}
		
		}
		//----< applications use this to register for notification >-----

		void regForFiles(IFileEventHandler* pHandler)
		{
			fileSubscribers_.push_back(pHandler);
		}
		//----< applications use this to register for notification >-----

		void regForDirs(IDirEventHandler* pHandler)
		{
			dirSubscribers_.push_back(pHandler);
		}
		//----< applications use this to register for notification >-----

		void regForDone(IDoneEventHandler* pHandler)
		{
			doneSubscribers_.push_back(pHandler);
		}

		//----< init text search engine object directly >-------------------------------

		void initNormalTextSearchEngine() {
			pText = new TextSearch("algorithm");
			pText->searchTotal();
		}

		//----< inti text search engine component >-------------------------------

		int initTextSearchComponent(std::string in_stringToBeSearched) {

			std::string msg;
			HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
			if (!SUCCEEDED(hr))
			{
				msg = "\n  could not initialize COM";
				logger.write(msg);
			}
			try
			{
				HRESULT hr;
				pTextSearchEngine.CoCreateInstance(CLSID_ComTextSearch);
				if (!pTextSearchEngine)
				{
					msg =  "\n  failed to create Text search component";
					logger.write(msg);
					return -1;
				}
				else {
					CComBSTR path(L"..");
					BSTR pattern = stdStringTOBSTR(in_stringToBeSearched);

					VARIANT_BOOL result = 0;
					hr = pTextSearchEngine->init_engine(pattern);

					if (SUCCEEDED(hr))
					{
						msg = "\n   init textSearch component successful\n\n";
						logger.write(msg);
					}
					else {
						msg =  "\n   init textSearch component failed\n\n";
						logger.write(msg);
						return -1;
					}
				}
			}
			catch (std::exception& ex)
			{
				std::wcout << L"\n  " << ex.what() << L"\n\n";
				return -1;
			}
		
			return 1;
		}


	private:
		//----< change std string to BSTR type >-------

		BSTR stdStringTOBSTR(std::string in_string) {

			CComBSTR temp(in_string.c_str());
			BSTR res = temp.Detach();
			return res;
		}
		Logger logger;
		std::string _stringToBeSearched;
		Path path_;
		Patterns patterns_;
		size_t numFilesProcessed = 0;
		fileSubscribers fileSubscribers_;
		dirSubscribers dirSubscribers_;
		doneSubscribers doneSubscribers_;
		static IFileMgr* pInstance_;
		CComQIPtr<IComTextSearch> pTextSearchEngine;

		TextSearch *pText;
		//bool textSearchEngineFinishProcessing;
	};

	inline IFileMgr* FileMgrFactory::create(const std::string& path)
	{
		return new FileMgr(path);
	}
}
#endif
