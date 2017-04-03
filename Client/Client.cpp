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




int main()
{
	Client c;
	std::string path = "..";
	std::string pattern1 = "*.h";
	std::string pattern2 = "*.cpp";
	std::string stringToBeSearched = "algorithm";
	c.addPath(path);
	c.addPattern(pattern1);
	c.addPattern(pattern2);
	c.provideTextSearchEngineStringToSearch(stringToBeSearched);
	c.search();

	int i;
	std::cin >> i;
}

