#pragma once
#include "global.h"
#include <string>
using namespace std;

class TableItem
{
public:
	string	name;	//���ŵ�Ψһ��ʶ
	int		addr;	//���ŵĵ�ַ,��Բ����Լ���ʱ��������
	int		kind;	//��������������
	int		type;	//���ŵ���������
	int		value;	//���ŵ�ֵ
	int		number;	//��������������Ԫ�صĸ���
	int		level;	//����������

	TableItem();
	TableItem(string na, int add, int kin, int typ, int val, int num,int level);
	~TableItem();
};

