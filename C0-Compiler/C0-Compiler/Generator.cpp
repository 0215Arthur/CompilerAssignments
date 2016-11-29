#include "StdAfx.h"
#include "Generator.h"
#include "Table.h"
Generator::Generator(string path)
{
	asmfile.open(path);
}


Generator::~Generator()
{
}

void Generator::quad2asm(Quadruple quad)
{
	//todo:�Ȱ�.dataд��ȥ,Ȼ�������.text,.data��Ҫд��consttab��strtable�е�����
	//��������
	if (quad.op == "CON") {	//para1 - name, para2 - type para3 - value. all string type
		asmfile << quad.para1 << ": .word " << quad.para3 << endl;
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
		else {

		}
	}
	else if (quad.op == "FUNC") {
		int funcsize = symbolTable.find(quad.para1).value;
		string funcname = symbolTable.find(quad.para1).name;
		asmfile << funcname << ":" << endl;		//����label
		asmfile << "subi $sp, $sp, " << funcsize << endl;	//����ջ�ռ�
		asmfile << "sw $ra,0($sp)" << endl;		//����ra
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
	else if (quad.op == "=") {	//ȡ��ַ����ֵ�����ԭ��ַ
		int addr1 = symbolTable.find(quad.para1).addr;
		int addr2 = symbolTable.find(quad.para2).addr;
		if (addr2) {

		}
		else {	//addr2Ϊ0,˵����ȫ�ֱ���

		}
		//asmfile << 
	}
	else if (quad.op == "PRT") {
		if (quad.para3 == "0") {	//ֻ��string
			asmfile << "li $v0, 4" << endl;			//todo :check ����ַ����ǲ���v0 = 4
			asmfile << "la $a0," << quad.para1 << endl;
			asmfile << "syscall" << endl;
		}
		else if (quad.para3 == "1") {	//ֻ��exp
		}
		else if (quad.para3 == "2") {	//���߼���

		}
		else {
			cout << "error PRT" << endl;
		}
	}
	else if (quad.op == "CALL") {
		asmfile << "jal " << quad.para1 << endl;
	}
	else if (quad.op == "END") {
		asmfile << "lw $ra,0($sp)" << endl;
		//todo: �����������ٵĿռ���ջ
		asmfile << "jr $ra" << endl;
	}
	else if (quad.op == "LAB") {
		asmfile << quad.para1 << ":" << endl;
	}
	else if (quad.op == "GLBEND") {
		map<string, string>::iterator it;
		for (it = strTable.begin(); it != strTable.end(); it++) {	//д�������ַ�������
			asmfile << it->first << ": .asciiz \"" << it->second << "\"" << endl;
		}
		asmfile << ".text" << endl;
		asmfile << "j main" << endl;;
	}
	else if (quad.op == "GLBSTR") {
		asmfile << ".data" << endl;
	}
}

void Generator::work()
{
	int index = 0;
	int quadnum = quadTable.size();
	bool global = true;		//����ȫ�ֱ���
	for (; index < quadnum; index++) {
		Quadruple q = quadTable[index];
		if (q.op == "GLBEND") {
			global = false;	//ȫ�ֳ�������������
		}
		quad2asm(q);
	}
}

void Generator::close()
{
	asmfile.close();
}
