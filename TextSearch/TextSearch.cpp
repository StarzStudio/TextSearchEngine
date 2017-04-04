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
	std::string msg;
	logger.attach(&std::cout);
	logger.start();
	WorkItem  textSearchInSingleFile = [this]()
	{
		
		std::ostringstream dst;
		dst << "\n  working thread " << std::this_thread::get_id() << " start dequeueing and processing \n";
		std::string msg = dst.str();
		logger.write(msg);
		while (true)
		{
			std::string dequeuedFile = _pBlockingqueue->deQ();
			if (!dequeuedFile.compare(std::string("endOfTextSearch")))
			{
				//(*callback)(this->matchedFilesCollection);
				msg = "  find " + std::to_string(this->matchedFilesCollection.size()) + " files that contains the input string: " + _pattern + "\n";
				logger.write(msg);
				for (int i = 0; i < this->matchedFilesCollection.size(); i++) {
					msg = this->matchedFilesCollection[i] + "\n";
					logger.write(msg);
				}
				msg = "  Please keep waiting processing to completed \n";
				logger.write(msg);
				//fptr(true);
				logger.stop();
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
		
		//std::cout << "file: " << _fileName << " couldn't be found or opened" << std::endl;
		//Show::write("file: " + _fileName + " couldn't be found or opened\n");
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



int main()
{
	std::string file = "test.txt";
	std::string pattern = "algorithm";

	std::ostringstream dst;

	TextSearch exe;


	Show::attach(&std::cout);
	Show::start();
	Show::write("\n");

	

	//exe.loadSearchAlgorithm(pAlgorithm);

	int result = exe.search(file);
	if (result == -1) {
		dst << "pattern doesn't exist\n" ;
		Show::write(dst.str());
	}
	else {
		dst << "pattern starts at position \n";
		Show::write(dst.str());
	}

	Show::stop("\n  stopping static logger");
    return 0;
}

#endif