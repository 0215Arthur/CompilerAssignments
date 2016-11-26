#include "StdAfx.h"
#include "Generator.h"
Generator::Generator(string path)
{
	asmfile.open(path);
}


Generator::~Generator()
{
}

void Generator::quad2asm(Quadruple quad)
{
	//todo:�Ȱ�.dataд��ȥ,Ȼ�������.text
	//.data��Ҫд��consttab��strtable�е�����
	//��������
	if (quad.op == "CON") {	//para1 - name, para2 - type para3 - value. all string type
		if (quad.para2 == "INT") {
			asmfile << quad.para1 << ": .word " << quad.para3 << endl;
		}
		else if (quad.para2 == "CHAR") {
			asmfile << quad.para1 << ": .asciiz \"" << quad.para3 << "\"" << endl;
		}
	}
	//todo: ȫ�ֱ����;ֲ�����Ӧ��ȡ��ͬ�Ĵ���ʽ,��Ϊ�ֲ���������ջ��
	else if (quad.op == "VAR") {	//para1 - name, para2 - type, para3 - no_use
		if (quad.para2 == "INT") {
			asmfile << quad.para1 << ": .space 4" << endl;
		}
		if (quad.para2 == "CHAR") {
			asmfile << quad.para1 << ": .space 4" << endl;	//todo:�������Կ��Ǿ���char���͵Ĵ洢�ռ�,�����ȱ���
		}
	}
	else if (quad.op == "ARR") {	//para1 - name, para2 - type, para3 - ele_num
		if (quad.para2 == "INT") {
			asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;
		}
		if (quad.para2 == "CHAR") {
			asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;	//todo:char�Ĵ���ռ��Ƿ���Ż�
		}
	}
	else if (quad.op == "PARA") {
		if (quad.para2 == "INT") {
			//todo:implement para generate, PARA��������ջ��
		}
	}
	else if (quad.op == "+") {
		asmfile << "la $t1, " << quad.para1 << endl;
		asmfile << "la $t2, " << quad.para2 << endl;
		asmfile << "add $t1,$t2,$t3" << endl;
		asmfile << "la $t4, " << quad.para3 << endl;
		asmfile << "sw $t3,0($t4)" << endl; //todo:check if it is right
	}
	else if (quad.op == "-") {
		asmfile << "la $t1, " << quad.para1 << endl;
		asmfile << "la $t2, " << quad.para2 << endl;
		asmfile << "sub $t1,$t2,$t3" << endl;
		asmfile << "la $t4, " << quad.para3 << endl;
		asmfile << "sw $t3,0($t4)" << endl; //todo:check if it is right
	}
	else if (quad.op == "*") {
		//todo:finish here
	}
	else if (quad.op == "/") {
		//todo:finish here
	}
	else if (quad.op == "PRT") {
		if (quad.para3 == "0") {	//ֻ��string
		}
		else if (quad.para3 == "1") {	//ֻ��exp
		}
		else if (quad.para3 == "2") {	//���߼���

		}
		else {
			cout << "error PRT" << endl;
		}
	}
}
