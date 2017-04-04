#ifndef TEXTSEARCH_H
#define TEXTSEARCH_H
////////////////////////////////////////////////////////////////////////
//  TextSearh.h - search a given pattern in a file                    //
//  ver 1.2                                                           //
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
* This package can put filename into a blocking queue, and meanwhile hold a thread listening on that queue, keeping
* dequeueing fileName, open that file, and then search the given string in that file.
* 
* Config:
* -------------------
* Must pass the desired pattern when initialization. 
* Can inject a blocking queue from outside, otherwise it will hold a default queue instance inside.
*
* Public interface:
* ----------------
* putFile(std::string)                put filename into blocking queue
* searchTotal((void*)(bool));          start listening on blocking queue, dequeue filename and search in that file
*
* Build Process:
* --------------
* Required files: BlockingQueue.h  BlockingQueue.cpp
*                 Utilities.h, Utilities.cpp
*				  Tasks.h, Tasks.cpp
*                 ThreadPool.h, ThreadPool.cpp
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


// system header
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// user header 
#include "../BlockingQueue/BlockingQueue.h"
#include "../Tasks/Tasks.h"
#include "../Logger/Logger.h"



class TextSearch {
	using File = std::string;
	using WorkItem = std::function<void()>;
public:
	TextSearch(std::string pattern) : _pattern(pattern) {
		
		defaultBlockingQueue = new BlockingQueue<std::string>();
		_pBlockingqueue = defaultBlockingQueue;
	}
	TextSearch() {
		defaultBlockingQueue = NULL;
		_pBlockingqueue = NULL;
	}
	~TextSearch() {
		/*if (defaultBlockingQueue != NULL)
			delete defaultBlockingQueue;*/
	}

	//----< push a file into blocking queue >-------------------------------

	void putFile(File in_file) {
		if (_pBlockingqueue == NULL) return;
		_pBlockingqueue->enQ(in_file);
	}
	//----< start a thread listening and dequeuing from queue >-------------------------------

	void searchTotal();

	//----< search a single file >-------------------------------

	int search(std::string _fileName);

	//----< inject blocking queue instance from outside >-------------------------------

	void loadBlockingQueue(BlockingQueue<std::string>* in_pq) {
		_pBlockingqueue = in_pq;
	}
private:
	//----< reset ostringstream >-------------------------------
	
	//void cleanOStream() {
	//	dst.clear();
	//	dst.str("");
	//	//dst.seekp(0);
	//}
	Logger logger;
	BlockingQueue<std::string>* _pBlockingqueue;
	BlockingQueue<std::string>* defaultBlockingQueue;
	std::string _pattern;
	std::vector<std::string> matchedFilesCollection;
	Tasks task;
};



#endif