#pragma once
#include "global.h"
#include <string>
using namespace std;

class TableItem
{
public:
	string	name;	//���ŵ�Ψһ��ʶ
	int		addr;	//���ŵĵ�ַ
	int		kind;	//��������������
	int		type;	//���ŵ���������
	int		value;	//���ŵ�ֵ
	int		number;	//��������������Ԫ�صĸ���

	TableItem();
	~TableItem();
};

