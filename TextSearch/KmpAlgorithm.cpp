////////////////////////////////////////////////////////////////////////
//  KMP_algo.cpp - KMP algorithm                                      //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////

#include "KmpAlgorithm.h"




#ifdef TEST_KMP

#include <fstream>

int main()
{

	std::ifstream ifs("test.txt");
	if (!ifs.good()) {
		std::cout << "file couldn't be found or opened" << std::endl;
		exit(1);
	}

	// load content from file to string
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::string pattern = "This";
	
	KmpAlgorithm kmp(pattern);
    int result = kmp.search(content);
	if (result == -1) {
		std::cout << "pattern doesn't exist" << std::endl;
	}
	else {
		std::cout << "pattern starts at position " << result << std::endl;
	}
	return 0;
}

#endif