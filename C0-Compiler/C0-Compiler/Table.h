#pragma once
#include "TableItem.h"
#include <vector>
#include <string>
using namespace std;
class Table
{
	//todo: not here
	int		size;				//��ǰ���ű�Ĵ�С
	int		tabtype;			//���ű������
	string	tablename;			//���ű������
	vector<TableItem> items;	//���ű����
public:
	Table(string name);															
	~Table();
	bool in_table(string name);	//���name�Ƿ��Ѿ������ڷ��ű���
	void settype(int type);		//���÷��ű�����
	void symbol_insert(TableItem item);	//�������
	TableItem find(string name);	//ȡ������Ϊname�ı���
	bool value_in_table(int val);	//��鳣�������Ƿ����valueΪval����

};

