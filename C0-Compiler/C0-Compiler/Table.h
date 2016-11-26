#pragma once
#include "TableItem.h"
#include "defination.h"
#include <vector>
#include <string>
using namespace std;
class TableItem;
class Quadruple;
class Table
{
	//todo: not here
	int		size;				//��ǰ���ű�Ĵ�С
	int		tabtype;			//���ű������
	int		curlevel;			//��ǰ���ű�Ĳ��
	string	tablename;			//���ű������
	vector<TableItem> items;	//���ű����
public:
	Table(string name);															
	~Table();
	bool in_table(string name);	//���name�Ƿ��Ѿ������ڷ��ű���	//todo:��Ϊ�����ڵ�ǰ��ķ��ű���
	void settype(int type);		//���÷��ű�����
	void symbol_insert(TableItem item);	//�������
	TableItem find(string name);	//ȡ������Ϊname�ı���

	bool value_in_table(int val);	//��鳣�������Ƿ����valueΪval����
	bool is_con(string name);
	bool is_var(string name);
	bool is_arr(string name);
	bool is_para(string name);
	bool is_func(string name);
	int getkind(string name);
	int gettype(string name);
	int getvalue(string name);
	int setnum(string name,int number);	//����0��ʾ���óɹ�,����ʧ��
	void poplevel();	//���������еķ�����ջ

	int con_insert(string name, int type, int value);	//����ű�����ӳ���,����0��ʾ��ӳɹ�,1��ʾ���ʧ��,��ͬ
	int var_insert(string name, int type);				//����ű��в��뵥һ����
	int arr_insert(string name, int type, int num);		//����ű��в����������,���ķ��н���һά����
	int para_insert(string name, int type);			//����ű��в������
	int func_insert(string name, int type, int num);	//����ű��в��뺯��
	int temp_insert(string name, int type);	//���������ʱ������ֵ,������ʽ��ֵ�ȵ�

	void addlevel();
	void decllevel();
};

