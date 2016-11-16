#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/////////////////////////global include/////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "error.h"
using namespace std;

///////////////////////////lexer.cpp//////////////////////////////////
//�������������
#define		PLUSSYM		1	// +
#define		MINUSSYM	2	// -
#define		MULTISYM	3	// *
#define		DEVIDESYM	4	// /
#define		QUOTE		5	//'
#define		LBRACK		6	//[
#define		RBRACK		7	//]
#define		LPARENT		8	//(
#define		RPARENT		9	//)
#define		LBRACE		10	//{
#define		RBRACE		11	//}
#define		COLON		12	//:
#define		COMMA		13	//,
#define		SEMICOLON	14	//;
#define		EQUAL		15	//==
#define		ASSIGN		16	//=
#define		LESS		17	//<
#define		LESSEQU		18	//<=
#define		GREAT		19	//>
#define		GREATEQU	20	//>=
#define		NEQUAL		21	//!=
#define		DOUQUOTE	22	//"

//����ֵ����
#define		IDSYM		23	//�����Ǳ�ʶ��
#define		NUMSYM		24	//����������(num type)
#define		CHARTY		25	//��������ĸ(char type)
#define		STRING		26	//�������ַ���

//������
#define		MAINSYM		27	//main
#define		INTSYM		28	//int
#define		CHARSYM		29	//char
#define		CONSTSYM	30	//const
#define		VOIDSYM		31	//void
#define		IFSYM		32	//if
#define		WHILESYM	33	//while
#define		SWITCHSYM	34	//switch
#define		CASESYM		35	//case
#define		DEFAULTSYM	36	//default
#define		SCANFSYM	37	//scanf
#define		PRINTFSYM	38	//printf
#define		RETURNSYM	39	//return

//�������ƶ���
#define NUM_MAXLENGTH 9
#define STRING_MAXLENGTH 500
#define IDENT_MAXLENGTH 100

//�ʷ�������Ҫ�õ���ȫ�ֱ���
extern char ch;
extern string token,inputline, path;
extern int sym, num, line, count, ll, lc;
extern ifstream infile;
extern ofstream outfile;

//�ʷ�����������ĺ���
void output();
int getsym();
void backup();
void retrieve();

/////////////////////////symbol table/////////////////////////////////
#define TABLESIZE 1000 //���ű��С
#define MAXLAYER 2	//���ű������
typedef struct	//�������
{
	string name;	//���ŵ�����
	int addr;	//���ŵĵ�ַ
	int kind;	//���ŵĴ����
	int type;	//���ŵ���������
	int value;	//���ŵ�ֵ
	int number;	//��������������Ԫ�صĸ���
} tableitem;

typedef struct		//������ű�
{
	tableitem item[TABLESIZE];	//��������洢��������
	int levelindex[MAXLAYER];
	int top;		//���ű�궥λ��
}symtable;

//////////////////////////syntax.cpp//////////////////////////////////
void enter();		//�����Ŵ�����ű�
void program();	//�������ĵݹ��ӳ���
void conststate();		//������˵���ĵݹ��ӳ���
void constdef();	//����������ĵݹ��ӳ���
void varstate();		//������������ĵݹ��ӳ���
void vardef();		//�����������ĵݹ��ӳ���
void paralist();		//����������ʱ������ĵݹ��ӳ���
void compound();	//����������ĵݹ��ӳ���
void funcdef();	//�����з���ֵ���������ĵݹ��ӳ���
void voidfdef();	//�����޷���ֵ�ĺ��������ĵݹ��ӳ���
void mainfdef();	//���������������ĵݹ��ӳ���
void statement();		//�������ĵݹ��ӳ���
void expression();	//������ʽ�ĵݹ��ӳ���
void term();	//������ĵݹ��ӳ���
void factor();	//�������ӵĵݹ��ӳ���
void assignstate();	//����ֵ���ĵݹ��ӳ���
void ifstate();	//����if���ĵݹ��ӳ���
void condition();	//�����������ĵݹ��ӳ���
void whilestate();	//����whileѭ�����ĵݹ��ӳ���
void switchstate();	//����switch�ĵݹ��ӳ���
void casestate();	//����case�ĵݹ��ӳ���
void defaultstate();	//����default�ĵݹ��ӳ���
void printfstate();		//����printf�ĵݹ��ӳ���
void scanfstate();		//����scanf�ĵݹ��ӳ���
void returnstate();	//����return�ĵݹ��ӳ���


///////////////////////////error.cpp//////////////////////////////////
void error(int errid);

/////////////////////////quad.cpp////////////////////////////////////


/////////////////////////quad2asm.cpp//////////////////////////////



#endif