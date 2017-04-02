#ifndef KMPALGORITHM_H
#define KMPALGORITHM_H
////////////////////////////////////////////////////////////////////////
//  KmpAlgorithm.h - KMP algorithm                                     //
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
#include "searchAlgorithm.h"

class KmpAlgorithm : public SearchAlgorithm {
public:
	KmpAlgorithm(std::string in_pattern)  {
		this->R = 256;
		pat = in_pattern;
		// build DFA from pattern
		int m = pat.length();
		dfa = std::vector<std::vector<int>>(R, std::vector<int>(m));
		dfa[pat[0]][0] = 1;
		for (int x = 0, j = 1; j < m; j++) {
			for (int c = 0; c < R; c++)
				dfa[c][j] = dfa[c][x];     // Copy mismatch cases.
			dfa[pat[j]][j] = j + 1;   // Set match case.
			x = dfa[pat[j]][x];     // Update restart state.
		}
	}

	int search(std::string txt) {

		// simulate operation of DFA on text
		int m = pat.length();
		int n = txt.length();
		int i, j;
		for (i = 0, j = 0; i < n && j < m; i++) {
			j = dfa[txt[i]][j];
		}
		if (j == m) return i - m;    // found
		return -1;                    // not found
	}


	void switchPattern(std::string in_pattern) {
		pat = in_pattern;
	}
private:
	int R;
	std::vector<std::vector<int>> dfa;
	std::string pat; // sub string to be searched inside main string

};

#endif
