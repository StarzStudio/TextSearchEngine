// Client.cpp : Defines the entry point for the console application.
//


#include "Client.h"




int main()
{
	Client c;
	std::string path = "..";
	std::string pattern1 = "*.h";
	std::string pattern2 = "*.cpp";
	c.addPath(path);
	c.addPattern(pattern1);
	c.addPattern(pattern2);
	c.search();

	int i;
	std::cin >> i;
}

