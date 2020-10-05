#pragma once
#include <iomanip>
#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;
struct Table {
	int cols;
	vector<int> colWidth;
	vector<int> colAlign;
	Table(int cols, vector<int> colWidth, vector<int> colAlign):
		cols(cols), colWidth(colWidth), colAlign(colAlign){}

	void cell(const int& width, string val, bool _right = 0) {
		cout << (_right ? std::right : std::left) << std::setw(width)
		     << std::setfill(' ') << val;
	}
	void printRow(vector<string> vals) {
		for (int i =0; i < cols; i++)
			cell(colWidth[i], vals[i], colAlign[i]);
		cout << "\n";
	} 

};


