#pragma once
#include "global.h"
#include <string>
using namespace std;

class TableItem
{
public:
	string	name;	//���ŵ�Ψһ��ʶ
	int		addr;	//�����������еĵ�ַ
	int		kind;	//��������������
	int		type;	//���ŵ���������
	int		value;	//���ŵ�ֵ,�Ժ������溯��ռ��ջ�ռ�Ĵ�С
	int		number;	//��������������Ԫ�صĸ���
	string	father;	//�Է����Ǻ���,�Ժ�����ָ���丸����

	TableItem();
	TableItem(string na, int add, int kin, int typ, int val, int num,string father);
	~TableItem();
};

