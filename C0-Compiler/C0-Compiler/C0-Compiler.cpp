// C0-Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "global.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//getpath();
	//path = "C:/Users/luxiaodou/Desktop/13071079_test.txt";
	path = "C:/Users/luxiaodou/Desktop/a.txt";
	infile.open(path, ios::in);
	while (infile.good()) {
		getsym();
		output();
	}
	cout << "Word Analyze complete!" << endl;
	infile.close();
	outfile.close();
	return 0;
}

