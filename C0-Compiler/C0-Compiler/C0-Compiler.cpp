// C0-Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "global.h"
#include "Lexer.h"
#include "Parser.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Lexer::getpath();
	//Lexer::path = "C:/Users/luxiaodou/Desktop/13071079_test.txt";
	Lexer::path = "13071079_test.txt";
	//path = "C:/Users/luxiaodou/Desktop/a.txt";
	Lexer::init();
	Parser::program();
	cout << "Syntax Analyze complete!" << endl;
	Lexer::close();
	return 0;
}

