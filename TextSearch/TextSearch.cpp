////////////////////////////////////////////////////////////////////////
//  TextSearh.cpp - search a given pattern in a file                  //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////
#include "TextSearch.h"

//void(*fptr)(bool flag)
void TextSearch::TextSearch::searchTotal() {
	if (_pBlockingqueue == NULL) return;
	WorkItem  textSearchInSingleFile = [this]()
	{
		while (true)
		{
			std::string dequeuedFile = _pBlockingqueue->deQ();
			if (!dequeuedFile.compare(std::string("endOfTextSearch")))
			{
				//(*callback)(this->matchedFilesCollection);
				std::cout << "  find " << this->matchedFilesCollection.size() << " files that contains the input string" << std::endl;
				for (int i = 0; i < this->matchedFilesCollection.size(); i++) {
					std::cout << this->matchedFilesCollection[i] << std::endl;
				}
				//fptr(true);
				return;
			}
			if (this->search(dequeuedFile) != -1) {
				matchedFilesCollection.push_back(dequeuedFile);
			}
		}
	};
   	task.doWork(textSearchInSingleFile);
}

int TextSearch::search(std::string _fileName) {
	

	//if (_pSearchAlgorithm == NULL) return -1;
	std::ifstream ifs(_fileName);
	if (!ifs.good()) {
		std::cout << "file: " << _fileName << " couldn't be found or opened" << std::endl;
		return -1;
	}
	// load content from file to string
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));


	if (content.find(_pattern) != std::string::npos)
	{
		return 1;
	}
	else {
		return -1;
	}
	/*int result = _pSearchAlgorithm->search(content, _fileName);
	if (result == -1) {
		return result;
	}
	else {
		std::cout << "vector out index error caused on file: " << _pSearchAlgorithm->getCurrentFileInSearch() << std::endl;
	} */
	 
}

#ifdef TEST_TEXTSEARCH


class FileState {
	//bool canRead() { return _pContext->_pIn->good(); }

};

int main()
{
	std::string file = "test.txt";
	std::string pattern = "algorithm";


	TextSearch exe;

	//exe.loadSearchAlgorithm(pAlgorithm);

	int result = exe.search(file);
	if (result == -1) {
		std::cout << "pattern doesn't exist" << std::endl;
	}
	else {
		std::cout << "pattern starts at position " << result << std::endl;
	}
    return 0;
}

#endif