#include "stdafx.h"
#include "global.h"

void quad2asm();	//�����ɵ���Ԫʽת��Ϊ������
void insertasmsym();	//���ɻ����ű�
void findsym(const string &);	//�ҵ������ڷ��ű��е�λ��
void	pushstack(int len);	//����ѹջ����
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