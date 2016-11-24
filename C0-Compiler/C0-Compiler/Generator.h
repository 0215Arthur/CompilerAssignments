#pragma once
#include <iostream>
#include <fstream>
#include "Quadruple.h"
using namespace std;

class Generator {
	//todo: check private and public 
	void insertasmsym();	//���ɻ����ű�
	void findsym(const string &);	//�ҵ������ڷ��ű��е�λ��
	void pushstack(int len);	//����ѹջ����
	void setlab();	//�����µ�label
	void jumpasm();	//������תָ��
	void assignasm();	//���ɸ�ֵ���
	void ifasm(); //�����������
	void switchasm();	//���ɷ�֧���
	void constdeclasm();	//�����������
	void vardeclasm();	//�����������
	void callasm();	//�����������
	void paraasm();	//�����������
	void scanfasm();	//����scanf
	void printfasm();	//����printf
	void returnasm();	//����return���
public:
	Generator(string asmfilepath);
	~Generator();
	void quad2asm(Quadruple quad);//�����ɵ���Ԫʽת��Ϊ������
private:
	ofstream asmfile;	//Ŀ������ļ�
};

