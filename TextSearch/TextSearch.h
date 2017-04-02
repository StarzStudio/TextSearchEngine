#ifndef TEXTSEARCH_H
#define TEXTSEARCH_H
////////////////////////////////////////////////////////////////////////
//  TextSearh.h - search a given pattern in a file                    //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <vector>
#include "KmpAlgorithm.h"
#include "searchAlgorithm.h"
#include <fstream>
#include "../BlockingQueue/BlockingQueue.h"
#include "../Tasks/Tasks.h"
class TextSearch {
	using File = std::string;
	using WorkItem = std::function<void()>;
public:
	TextSearch(std::string pattern) : _pattern(pattern) {
		
		defaultBlockingQueue = new BlockingQueue<std::string>();
	//	defaultAlgorithm = new KmpAlgorithm(pattern);
		//_pSearchAlgorithm = defaultAlgorithm;
		_pBlockingqueue = defaultBlockingQueue;
	}
	TextSearch() {
		defaultBlockingQueue = NULL;
		_pBlockingqueue = NULL;
	//	defaultAlgorithm = NULL;
		//_pSearchAlgorithm = NULL;
		
	}
	~TextSearch() {
		if (defaultBlockingQueue != NULL)
			delete defaultBlockingQueue;
	/*	if (defaultAlgorithm != NULL)
			delete defaultAlgorithm;*/
	}

	void putFile(File in_file) {
		if (_pBlockingqueue == NULL) return;
		_pBlockingqueue->enQ(in_file);
	}
	// argument: callback function
	 //void(*callback)(std::vector<std::string> result)
	void searchTotal();
	int search(std::string _fileName);

	
	void loadBlockingQueue(BlockingQueue<std::string>* in_pq) {
		_pBlockingqueue = in_pq;
	}
	/*void loadSearchAlgorithm(SearchAlgorithm* in_pSearchAlgorithm) {
		_pSearchAlgorithm = in_pSearchAlgorithm;
	}*/

private:
	BlockingQueue<std::string>* _pBlockingqueue;
	BlockingQueue<std::string>* defaultBlockingQueue;
	//std::string _fileName;
	std::string _pattern;
	std::vector<std::string> matchedFilesCollection;
	//SearchAlgorithm* _pSearchAlgorithm;
	//SearchAlgorithm* defaultAlgorithm;
	Tasks task;
};



#endif