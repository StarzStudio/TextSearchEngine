#ifndef CLIENT_H
#define CLIENT_H

////////////////////////////////////////////////////////////////////////
//  Client.h                                                          //
//  ver 1.0                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Windows 10                                         //
//  Application:   Text Search Component, 775 DO project 1            //
//  Author:        Xing Zhou, Syracuse University                     //
//                 Software Engineering                               //
//                 xzhou118@syr.edu                                   //
////////////////////////////////////////////////////////////////////////

#include "../FileMgrComponent/FileMgrComponent_i.h"
#include <atlbase.h>
#include <atlsafe.h>
#include <iostream>

class Client{
public:
	void search();

};
#endif