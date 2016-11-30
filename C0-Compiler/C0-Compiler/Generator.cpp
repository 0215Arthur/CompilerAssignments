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

int is_not_global(string name) {
	return symbolTable.funcloc[symbolTable.find(name).father];	//ȫ�ֱ�����fatherΪ0
}

void Generator::quad2asm(Quadruple quad)
{
	//todo:�Ȱ�.dataд��ȥ,Ȼ�������.text,.data��Ҫд��ȫ������strtable�е�����
	//��������
	if (quad.op == "CON") {	//para1 - name, para2 - type para3 - value. all string type
		if (global) {		//ȫ�ֳ������������ݶ�
			asmfile << quad.para1 << ": .word " << quad.para3 << endl;
		}
		else {		//�ֲ���������ջ��, ��Ҫ�ӷ��ű���л�ȡλ�ò�����
			int addr = symbolTable.find(quad.para1).addr;
			int value = atoi(quad.para2.c_str());
			asmfile << "li $t0," << value << endl;
			asmfile << "sw $t0," << addr << "($sp)" << endl;
		}
	}
	else if (quad.op == "VAR") {	//para1 - name, para2 - type, para3 - no_use
		if (global) {
			if (quad.para2 == "INT") {
				asmfile << quad.para1 << ": .space 4" << endl;
			}
			if (quad.para2 == "CHAR") {
				asmfile << quad.para1 << ": .space 4" << endl;	//todo:�������Կ��Ǿ���char���͵Ĵ洢�ռ�,�����ȱ���
			}
		}
		else {
			//todo:�����ܲ��ܶԾֲ���һ�������������Ż�
		}
	}
	else if (quad.op == "ARR") {	//para1 - name, para2 - type, para3 - ele_num
		if (global) {
			if (quad.para2 == "INT") {
				asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;
			}
			if (quad.para2 == "CHAR") {
				asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;	//todo:char�Ĵ���ռ��Ƿ���Ż�, ע��ʹ��.word�����������Ὣ�����ʼ��Ϊ1
			}
		}
		else {
			//todo:�����ܲ��ܶԾֲ���������Ż�
		}
	}
	else if (quad.op == "PARA") {	//��para��ֵ��Ҫ����ջ����ջ
		string value = quad.para1;
		string count = quad.para2;
		string funcname = quad.para3;
		int offset = atoi(count.c_str()) * 4;
		int funcsize = symbolTable.find(funcname).value;
		asmfile << "subi $sp,$sp," << funcsize << endl;
		asmfile << "li $t0, " << value << endl;
		asmfile << "sw $t0," << offset << "($sp)" << endl;
		asmfile << "addi $sp,$sp," << funcsize << endl;
	}
	else if (quad.op == "FUNC") {
		int funcsize = symbolTable.find(quad.para1).value;
		string funcname = symbolTable.find(quad.para1).name;
		symbolTable.curfunction = funcname;
		symbolTable.curlevel = symbolTable.funcloc[funcname];
		asmfile << funcname << ":" << endl;		//����label
		asmfile << "subi $sp, $sp, " << funcsize << endl;	//����ջ�ռ�
		asmfile << "sw $ra,0($sp)" << endl;		//����ra
	}
	else if (quad.op == "END") {
		asmfile << "lw $ra,0($sp)" << endl;
		//todo: �����������ٵĿռ���ջ
		int funcsize = symbolTable.getvalue(symbolTable.curfunction);
		asmfile << "addi $sp,$sp," << funcsize << endl;
		asmfile << "jr $ra" << endl;
	}
	else if (quad.op == "+" || quad.op == "-" || quad.op == "*" || quad.op == "/") {
		string op1 = quad.para1;
		string op2 = quad.para2;
		string result = quad.para3;
		int addr1 = symbolTable.find(op1).addr;
		int addr2 = symbolTable.find(op2).addr;
		int addre = symbolTable.find(result).addr;
		asmfile << "lw $t0," << addr1 << "($sp)" << endl;
		asmfile << "lw $t1," << addr2 << "($sp)" << endl;
		if (quad.op == "+" || quad.op == "-") {
			if (quad.op == "+") {	//�ӷ�
				asmfile << "add $t0,$t1,$t2" << endl;
			}
			else {			//����
				asmfile << "sub $t0,$t1,$t2" << endl;
			}
			asmfile << "sw $t2," << addre << "($sp)" << endl;
		}
		else {
			if (quad.op == "*") {	//�˷�
				asmfile << "mult $t0,$t1" << endl;
				asmfile << "mflo $t2" << endl;
			}
			else {			//����
				asmfile << "div $t0,$t1" << endl;
				asmfile << "mflo $t2" << endl;
			}
			asmfile << "sw $t2," << addre << "($sp)" << endl;

		}
	}
	else if (quad.op == "LODARR") {	// LODARR arrayname index name
		string arrayname = quad.para1;
		string index = quad.para2;
		string name = quad.para3;
		int arradd = symbolTable.find(arrayname).addr;
		int addr = symbolTable.find(name).addr;
		int offset = atoi(index.c_str()) * 4 + arradd;
		asmfile << "lw $t0," << offset << "($sp)" << endl;
		asmfile << "sw $t0," << addr << "($sp)" << endl;
	}
	else if (quad.op == "LODI") {	//LODI name value ~
		string name = quad.para1;
		string value = quad.para2;
		int addr = symbolTable.find(name).addr;
		asmfile << "li $t0," << value << endl;
		asmfile << "sw $t0," << addr << "($sp)" << endl;
	}
	else if (quad.op == "LODV") {	//LODV name v_name ~
		string name = quad.para1;
		string v_name = quad.para2;
		int addr = symbolTable.find(name).addr;
		if (symbolTable.find(v_name).father == symbolTable.topfunction) {	//ȫ��
			asmfile << "la $t0," << v_name << endl;
			asmfile << "lw $t1,0($t0)" << endl;
			asmfile << "sw $t1," << addr << "($sp)" << endl;
		}
		else {	//�ֲ�����
			int vaddr = symbolTable.find(v_name).addr;
			asmfile << "lw $t0," << vaddr << "($sp)" << endl;
			asmfile << "sw $t0," << addr << "($sp)" << endl;
		}
	}
	else if (quad.op == "~") {	//~ name
		string name = quad.para1;
		int addr = symbolTable.find(name).addr;
		asmfile << "lw $t0," << addr << "($sp)" << endl;
	}
	else if (quad.op == "=") {	//ȡ��ַ����ֵ�����ԭ��ַ  = name offset exname
		// name[offset] = exname
		//todo : check here
		string name = quad.para1, offset = quad.para2, exname = quad.para3;
		int addr1 = symbolTable.find(name).addr;
		int addr2 = symbolTable.find(exname).addr;
		if (is_not_global(name)) {	//���ֲ�������ֵ
			addr1 += atoi(offset.c_str());
			if (is_not_global(name)) {	//ֵ�Ǿֲ���
				asmfile << "lw $v0," << addr2 << "($sp)" << endl;
			}
			else {	//ֵ��ȫ����
				asmfile << "la $t0," << symbolTable.find(exname).name << endl;
				asmfile << "lw $v0, 0($t0)" << endl;
			}
			asmfile << "sw $v0," << addr1 << "($sp)" << endl;
		}
		else {	//��ȫ�ֱ�����ֵ
			asmfile << "la $t0," << name << endl;
			int off = atoi(offset.c_str());
			if (is_not_global(name)) {	//ֵ�Ǿֲ���
				int localadd = symbolTable.find(exname).addr;
				asmfile << "lw $v0," << localadd << "($sp)" << endl;
			}
			else {	//ֵ��ȫ����
				asmfile << "la $t1," << symbolTable.find(exname).name << endl;
				asmfile << "lw $v0,0($t1)" << endl;
			}
			asmfile << "sw $v0," << off << "($t0)" << endl;
		}
	}
	else if (quad.op == "GTE" || quad.op == "GREAT" || quad.op == "LESS" ||
		quad.op == "LTE" || quad.op == "EQU" || quad.op == "NEQ") {
		string exp_name1 = quad.para1;
		string exp_name2 = quad.para2;
		string label = quad.para3;
		int addr1 = symbolTable.find(exp_name1).addr;
		int addr2 = symbolTable.find(exp_name2).addr;
		asmfile << "lw $t0," << addr1 << "($sp)" << endl;
		asmfile << "lw $t1," << addr2 << "($sp)" << endl;

		if (quad.op == "GTE") {
			asmfile << "BGE $t0,$t1," << label << endl;
		}
		else if (quad.op == "GREAT") {
			asmfile << "BGT $t0,$t1," << label << endl;
		}
		else if (quad.op == "LESS") {
			asmfile << "BLT $t0,$t1," << label << endl;
		}
		else if (quad.op == "LTE") {
			asmfile << "BLE $t0,$t1," << label << endl;
		}
		else if (quad.op == "EQU") {
			asmfile << "BEQ $t0,$t1," << label << endl;
		}
		else if (quad.op == "NEQ") {
			asmfile << "BNE $t0,$t1," << label << endl;
		}
	}
	else if (quad.op == "PRT") {
		string strname = quad.para1;
		string exname = quad.para2;
		string type = quad.para3;

		if (type == "0") {	//ֻ��string
			asmfile << "li $v0, 4" << endl;			//todo :check ����ַ����ǲ���v0 = 4
			asmfile << "la $a0," << strname << endl;
			asmfile << "syscall" << endl;
			asmfile << "la $a0," << "$enter" << endl;
			asmfile << "syscall" << endl;
		}
		else if (type == "1") {	//ֻ��exp
			int addr = symbolTable.find(exname).addr;
			asmfile << "li $v0, 1" << endl;
			asmfile << "lw $a0," << addr << "($sp)" << endl;
			asmfile << "syscall" << endl;
			asmfile << "li $v0, 4" << endl;
			asmfile << "la $a0," << "$enter" << endl;
			asmfile << "syscall" << endl;
		}
		else if (type == "2") {	//���߼���
			asmfile << "li $v0, 4" << endl;
			int exaddr = symbolTable.find(exname).addr;
			asmfile << "la $a0," << strname << endl;
			asmfile << "syscall" << endl;
			asmfile << "li $v0, 1" << endl;
			asmfile << "lw $a0," << exaddr << "($sp)" << endl;
			asmfile << "syscall" << endl;
			asmfile << "li $v0, 4" << endl;
			asmfile << "la $a0," << "$enter" << endl;
			asmfile << "syscall" << endl;
		}

	}
	else if (quad.op == "SCF") {
		string name = quad.para1;
		TableItem t = symbolTable.find(name);
		int addr = t.addr;
		if (is_not_global(name)) {	//��ȫ����Ҫ�޸�.data�е�����
			if (t.type == INTSYM) {
				asmfile << "li $v0,5" << endl;
			}
			else {
				asmfile << "li $v0,12" << endl;
			}
			asmfile << "syscall" << endl;
			asmfile << "sw $v0," << addr << "($sp)" << endl;	//�ֲ��������޸ı�����ջ��	
		}
		else {			
			if (t.type == INTSYM) {
				asmfile << "li $v0,5" << endl;
			}
			else {
				asmfile << "li $v0,12" << endl;
			}
			asmfile << "syscall" << endl;
			asmfile << "la $t0," << name << endl;
			asmfile << "sw $v0,0($t0)" << endl;
		}
	}
	else if (quad.op == "CALL") {
		asmfile << "jal " << quad.para1 << endl;
	}
	else if (quad.op == "LAB") {
		asmfile << quad.para1 << ":" << endl;
	}
	else if (quad.op == "JMP") {	//JMP LABEL
		string label = quad.para1;
		asmfile << "j " << label << endl;
	}
	else if (quad.op == "RET") {
		string name = quad.para1;
		int value = symbolTable.find(name).value;
		int funcsize = symbolTable.getvalue(symbolTable.curfunction);
		asmfile << "li $a0," << value << endl;	//todo : maybe not right here
		asmfile << "lw $ra, 0($sp)";
		asmfile << "addi $sp, $sp" << funcsize << endl;
		asmfile << "jr $ra" << endl;
	}
	else if (quad.op == "GLBSTR") {
		asmfile << ".data" << endl;
	}
	else if (quad.op == "GLBEND") {
		map<string, string>::iterator it;
		for (it = strTable.begin(); it != strTable.end(); it++) {	//д�������ַ�������
			asmfile << it->first << ": .asciiz \"" << it->second << "\"" << endl;
		}
		asmfile << ".text" << endl;
		asmfile << "j main" << endl;;
	}
}

void Generator::work()
{
	int index = 0;
	int quadnum = quadTable.size();
	global = true;		//����ȫ�ֱ���
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
