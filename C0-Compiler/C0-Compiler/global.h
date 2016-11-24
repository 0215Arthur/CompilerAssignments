#pragma once
/////////////////////////global include/////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "error.h"
#include "Quadruple.h"
using namespace std;

//vector<Quadruple> quadtable;
extern int errornum;

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

///////////////////////////error.cpp//////////////////////////////////
void error(int errid);

/////////////////////////quad.cpp////////////////////////////////////


/////////////////////////quad2asm.cpp//////////////////////////////


