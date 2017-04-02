#ifndef UTILITIES_H
#define UTILITIES_H
///////////////////////////////////////////////////////////////////////
// Utilities.h - small, generally usefule, helper classes            //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2016                              //
// Platform:      Mac Book Pro, OS X EI Captain 10.11                //
// Application:   Dependency analysis, 687 OOD Project3              //
// Author:      Xing Zhou, Syracuse University, Software Engineering //
//              xzhou118@syr.edu                                     //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes StringHelper and Converter and a global
* function putline().  This class will be extended continuously for
* awhile to provide convenience functions for general C++ applications.
*
* Build Process:
* --------------
* Required Files: Utilities.h, Utilities.cpp
*
* Build Command: devenv Project2.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.1 : 06 Feb 2015
* - fixed bug in split which turns a comma separated string into
*   a vector of tokens.
* - added comments
* ver 1.0 : 05 Feb 2016
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#include <string>
#include <vector>
#include <sstream>
#include <functional>

namespace Utilities
{
    class StringHelper
    {
    public:
        static std::vector<std::string> split(const std::string& src);
        static void Title(const std::string& src, char underline = '-');
        static void title(const std::string& src);
    };

    void putline();

    template <typename T>
    class Converter
    {
    public:
        static std::string toString(const T& t);
        static T toValue(const std::string& src);
    };

    template <typename T>
    std::string Converter<T>::toString(const T& t)
    {
        std::ostringstream out;
        out << t;
        return out.str();
    }

    template<typename T>
    T Converter<T>::toValue(const std::string& src)
    {
        std::istringstream in(src);
        T t;
        in >> t;
        return t;
    }
}
#endif
