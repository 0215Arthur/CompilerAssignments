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
public:
	string	topfunction;			//ȫ�ֲ�
	vector<TableItem> items;	//���ű����
	Table(string name);															
	~Table();
	int		offset;				//������ջ�е�ƫ��
	map<string, int>	funcloc;	//���Һ����ڷ��ű��ж�Ӧ��λ��
	int		curlevel;			//���ű�ǰ�����ʼλ��
	string	curfunction;		//��ǰ������

	//����
	bool in_table(string name);	//���name�Ƿ��Ѿ������ڷ��ű���(��ǰ�����ȫ�ֱ���)	
	bool fin_table(string name); //����Ƿ���ں�����Ϊname�ĺ���
	bool in_cur_level(string name);;	//��鵱ǰ����û��name����
	bool value_in_table(int val);	//�������Ƿ����valueΪval����
	int con_insert(string name, int type, int value);	//����ű�����ӳ���,����0��ʾ��ӳɹ�,1��ʾ���ʧ��,��ͬ
	int var_insert(string name, int type);				//����ű��в��뵥һ����
	int arr_insert(string name, int type, int num);		//����ű��в����������,���ķ��н���һά����
	int para_insert(string name, int type);			//����ű��в������
	int func_insert(string name, int type, int num);	//����ű��в��뺯��

	TableItem find(string name);	//ȡ������Ϊname�ı���
	TableItem findf(string name);	//ȡ������Ϊname�ĺ���

	bool is_con(string name);
	bool is_var(string name);
	bool is_arr(string name);
	bool is_para(string name);
	bool is_func(string name);

	int getkind(string name);
	int gettype(string name);
	int getvalue(string name);

	int setfuncnum(string name,int number);	//����0��ʾ���óɹ�,����ʧ��
	int setfuncsize();	//���ú�������ռ��ջ�ռ�Ĵ�С
	int setzero(string name);
};

