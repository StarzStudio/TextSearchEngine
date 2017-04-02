#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H
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

class SearchAlgorithm {
public:
	virtual int search(std::string mainString) = 0;
	
};

#endif