// C0-Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "global.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//getpath();
	path = "C:/Users/luxiaodou/Desktop/13071079_test.txt";

	bool flag = false;
	bool nflag = true;
	//path = "C:/Users/luxiaodou/Desktop/a.txt";
	infile.open(path, ios::in);
	program();
	cout << "Syntax Analyze complete!" << endl;
	infile.close();
	outfile.close();
	return 0;
}

