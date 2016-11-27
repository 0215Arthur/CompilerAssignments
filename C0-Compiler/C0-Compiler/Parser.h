#pragma once
#include "defination.h"
#include "error.h"
#include <set>
using namespace std;
class Parser {
public:
	static void program();	//�������ĵݹ��ӳ���
private:
	static void error(int errorid);
	//static void enter();		//todo: �޸��ĵ�,˵���˷����ѱ�ת��
	static void skip(set<int> symset);	//���������������
	static void conststate();		//������˵���ĵݹ��ӳ���
	static void constdef();	//����������ĵݹ��ӳ���
	static void varstate();		//������������ĵݹ��ӳ���
	static void vardef();		//�����������ĵݹ��ӳ���
	static void paralist();		//����������ʱ������ĵݹ��ӳ���
	static void compound();	//����������ĵݹ��ӳ���
	static void funcdef();	//�����з���ֵ���������ĵݹ��ӳ���
	static void voidfdef();	//�����޷���ֵ�ĺ��������ĵݹ��ӳ���
	static void mainfdef();	//���������������ĵݹ��ӳ���
	static void statement();		//�������ĵݹ��ӳ���
	static void expression(string &, int &);	//������ʽ�ĵݹ��ӳ���
	static void term(string &,int &);	//������ĵݹ��ӳ���
	static void factor(string &,int &);	//�������ӵĵݹ��ӳ���
	static void assignstate();	//����ֵ���ĵݹ��ӳ���
	static void ifstate();	//����if���ĵݹ��ӳ���
	static void condition(string );	//�����������ĵݹ��ӳ���
	static void whilestate();	//����whileѭ�����ĵݹ��ӳ���
	static void switchstate();	//����switch�ĵݹ��ӳ���
	static void casestate();	//����case�ĵݹ��ӳ���
	static void defaultstate();	//����default�ĵݹ��ӳ���
	static void printfstate();		//����printf�ĵݹ��ӳ���
	static void scanfstate();		//����scanf�ĵݹ��ӳ���
	static void returnstate();	//����return�ĵݹ��ӳ���
	static void calfunc(string &);	//���������õĵݹ��ӳ���
};