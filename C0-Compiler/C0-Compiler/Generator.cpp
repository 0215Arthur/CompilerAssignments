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
	return symbolTable.funcloc[symbolTable.find(name).father];	//全局变量的father为0
}

void Generator::quad2asm(Quadruple quad)
{
	//常量声明
	if (quad.op == "CON") {	//para1 - name, para2 - type para3 - value. all string type
		string name = quad.para1;
		string type = quad.para2;
		string value = quad.para3;
		if (global) {		//全局常量声明在数据段
			asmfile << name << ": .word " << value << endl;
		}
		else {		//局部常量存在栈中, 需要从符号表表中获取位置并存入
			int addr = symbolTable.find(quad.para1).addr;
			int val = atoi(value.c_str());
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
				asmfile << quad.para1 << ": .space 4" << endl;	
			}
		}
		else {
			//todo:考虑能不能对局部单一变量声明进行优化
		}
	}
	else if (quad.op == "ARR") {	//para1 - name, para2 - type, para3 - ele_num
		if (global) {
			if (quad.para2 == "INT") {
				asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;
			}
			if (quad.para2 == "CHAR") {
				asmfile << quad.para1 << ": .word 1:" << quad.para3 << endl;	//注意使用.word进行数组分配会将数组初始化为1
			}
		}
		else {
			//todo:考虑能不能对局部数组进行优化
		}
	}
	else if (quad.op == "PARA") {	//给para赋值需要先入栈再退栈
		string value_name = quad.para1;
		string count = quad.para2;
		string funcname = quad.para3;
		int addr = symbolTable.find(value_name).addr;
		int funcsize = symbolTable.findf(funcname).value;
		int offset = atoi(count.c_str()) * 4;
		asmfile << "lw $t1," << addr << "($sp)" << endl;
		asmfile << "subi $sp,$sp," << funcsize << endl;
		asmfile << "sw $t1," << offset << "($sp)" << endl;
		asmfile << "addi $sp,$sp," << funcsize << endl;
	}
	else if (quad.op == "FUNC") {
		int funcsize = symbolTable.findf(quad.para1).value;
		string funcname = symbolTable.findf(quad.para1).name;
		symbolTable.curfunction = funcname;
		symbolTable.curlevel = symbolTable.funcloc[funcname];
		asmfile << funcname << ":" << endl;		//给出label
		asmfile << "subi $sp, $sp," << funcsize << endl;	//开辟栈空间
		asmfile << "sw $ra,0($sp)" << endl;		//保存ra
	}
	else if (quad.op == "END") {	//memo: only used when there is no 'return' statement
		asmfile << "lw $ra,0($sp)" << endl;
		string curfunc = symbolTable.curfunction;
		int funcsize = symbolTable.findf(curfunc).value;
		if (curfunc == "main") {
			asmfile << "li $v0," << 10 << endl;
			asmfile << "syscall" << endl;
		}
		else {
			asmfile << "addi $sp,$sp," << funcsize << endl;
			asmfile << "jr $ra" << endl;
		}
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
			if (quad.op == "+") {	//加法
				asmfile << "add $t2,$t1,$t0" << endl;
			}
			else {			//减法
				asmfile << "sub $t2,$t0,$t1" << endl;
			}
			asmfile << "sw $t2," << addre << "($sp)" << endl;
		}
		else {
			if (quad.op == "*") {	//乘法
				asmfile << "mult $t0,$t1" << endl;
				asmfile << "mflo $t2" << endl;
			}
			else {			//除法
				asmfile << "div $t0,$t1" << endl;
				asmfile << "mflo $t2" << endl;
			}
			asmfile << "sw $t2," << addre << "($sp)" << endl;

		}
	}
	else if (quad.op == "LODARR") {	// LODARR arrayname indexname name
		// name = arrayname[indexname] indexname & name are local-only
		string arrayname = quad.para1;
		string indexname = quad.para2;
		string name = quad.para3;
		int indaddr = symbolTable.find(indexname).addr;
		int nameaddr = symbolTable.find(name).addr;
		if (is_not_global(arrayname)) {
			int arraddr = symbolTable.find(arrayname).addr;
			//asmfile << "lw $t0," << arraddr << "($sp)" << endl;	//todo: changed here
			asmfile << "lw $t1," << indaddr << "($sp)" << endl;
			asmfile << "mul $t1,$t1,4" << endl;
			asmfile << "addi $t1,$t1," << arraddr << endl;
			asmfile << "add $t1,$t1,$sp" << endl;
			asmfile << "lw $t0,0($t1)" << endl;
			asmfile << "sw $t0," << nameaddr << "($sp)" << endl;
		}
		else {
			asmfile << "la $t0," << arrayname << endl;
			asmfile << "lw $t1," << indaddr << "($sp)" << endl;
			asmfile << "mul $t1,$t1,4" << endl;
			asmfile << "add $t1,$t1,$t0" << endl;
			asmfile << "lw $t0,0($t1)" << endl;
			asmfile << "sw $t0," << nameaddr << "($sp)" << endl;
		}
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
		if (symbolTable.find(v_name).father == symbolTable.topfunction) {	//全局
			asmfile << "la $t0," << v_name << endl;
			asmfile << "lw $t1,0($t0)" << endl;
			asmfile << "sw $t1," << addr << "($sp)" << endl;
		}
		else {	//局部变量
			int vaddr = symbolTable.find(v_name).addr;
			asmfile << "lw $t0," << vaddr << "($sp)" << endl;
			asmfile << "sw $t0," << addr << "($sp)" << endl;
		}
	}
	else if (quad.op == "LODR") {	// LODR faction_value regi 用于函数值的回写
		string faction_value = quad.para1;
		string regi = quad.para2;
		int addr = symbolTable.find(faction_value).addr;
		asmfile << "sw " << regi << "," << addr << "($sp)" << endl;
	}
	else if (quad.op == "~") {	//~ name
		string name = quad.para1;
		int addr = symbolTable.find(name).addr;
		asmfile << "lw $t0," << addr << "($sp)" << endl;
		asmfile << "sub $t0,$0,$t0" << endl;
		asmfile << "sw $t0," << addr << "($sp)" << endl;
	}
	else if (quad.op == "=") {	//取地址→赋值→存回原地址  = name offset exname
		// name[offset] = exname
		string name = quad.para1;
		string offsetname = quad.para2;
		string exname = quad.para3;
		int addr1 = symbolTable.find(name).addr;
		int addr2 = symbolTable.find(exname).addr;
		int offsetaddr = symbolTable.find(offsetname).addr;
		int type = symbolTable.find(name).kind;
		if (type == ARR) {
			if (is_not_global(name)) {	//给局部变量赋值
				asmfile << "lw $t0," << offsetaddr << "($sp)" << endl;
				asmfile << "mul $t0,$t0,4" << endl;
				asmfile << "addi $t0,$t0," << addr1 << endl;
				asmfile << "add $t0,$t0,$sp" << endl;	//得到要赋值元素的地址于$t0
				if (is_not_global(exname)) {	//值是局部量
					asmfile << "lw $v0," << addr2 << "($sp)" << endl;
				}
				else {	//值是全局量
					asmfile << "la $t2," << exname << endl;
					asmfile << "lw $v0, 0($t2)" << endl;
				}
				asmfile << "sw $v0,0($t0)" << endl;
			}
			else {	//给全局变量赋值
				asmfile << "la $t0," << name << endl;
				asmfile << "lw $t1," << offsetaddr << "($sp)" << endl;
				asmfile << "mul $t1,$t1,4" << endl;
				asmfile << "add $t0,$t0,$t1" << endl;	//得到要赋值元素的地址于$t0
				if (is_not_global(exname)) {	//值是局部量
					asmfile << "lw $v0," << addr2 << "($sp)" << endl;
				}
				else {	//值是全局量
					asmfile << "la $t1," << exname << endl;
					asmfile << "lw $v0,0($t1)" << endl;
				}
				asmfile << "sw $v0,0($t0)" << endl;
			}
		}
		else {
			if (is_not_global(name)) {
				if (is_not_global(exname)) {
					asmfile << "lw $t0," << addr2 << "($sp)" << endl;
					asmfile << "sw $t0," << addr1 << "($sp)" << endl;
				}
				else {
					asmfile << "la $t0," << exname << endl;
					asmfile << "lw $t1,0($t0)" <<endl;
					asmfile << "sw $t1," << addr1 << "($sp)" << endl;
				}
			}
			else {
				if (is_not_global(exname)) {
					asmfile << "lw $t0," << addr2 << "($sp)" << endl;
					asmfile << "la $t1," << name << endl;
					asmfile << "sw $t0,0($t1)" << endl;
				}
				else {
					asmfile << "la $t0," << exname << endl;
					asmfile << "lw $t1,0($t0)" << endl;
					asmfile << "la $t0," << name << endl;
					asmfile << "sw $t1,0($t0)" << endl;
				}
			}
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
			asmfile << "bge $t0,$t1," << label << endl;
		}
		else if (quad.op == "GREAT") {
			asmfile << "bgt $t0,$t1," << label << endl;
		}
		else if (quad.op == "LESS") {
			asmfile << "blt $t0,$t1," << label << endl;
		}
		else if (quad.op == "LTE") {
			asmfile << "ble $t0,$t1," << label << endl;
		}
		else if (quad.op == "EQU") {
			if (exp_name2 == "$0") {
				asmfile << "beq $t0,$0," << label << endl;
			}
			else {
				asmfile << "beq $t0,$t1," << label << endl;
			}
		}
		else if (quad.op == "NEQ") {
			asmfile << "bne $t0,$t1," << label << endl;
		}
	}
	else if (quad.op == "PRT") {
		string strname = quad.para1;
		string exname = quad.para2;
		string type = quad.para3;

		if (type == "0") {	//只用string
			asmfile << "li $v0, 4" << endl;			
			asmfile << "la $a0," << strname << endl;
			asmfile << "syscall" << endl;
			asmfile << "la $a0," << "$enter" << endl;
			asmfile << "syscall" << endl;
		}
		else if (type == "1") {	//只用exp
			int addr = symbolTable.find(exname).addr;
			int type = symbolTable.find(exname).type;
			if (type == INTSYM) {
				asmfile << "li $v0, 1" << endl;
			}
			else if (type == CHARSYM) {
				asmfile << "li $v0, 11" << endl;
			}
			asmfile << "lw $a0," << addr << "($sp)" << endl;
			asmfile << "syscall" << endl;
			asmfile << "li $v0, 4" << endl;
			asmfile << "la $a0," << "$enter" << endl;
			asmfile << "syscall" << endl;
		}
		else if (type == "2") {	//二者兼有
			int exaddr = symbolTable.find(exname).addr;
			int type = symbolTable.find(exname).type;
			asmfile << "li $v0, 4" << endl;
			asmfile << "la $a0," << strname << endl;
			asmfile << "syscall" << endl;
			if (type == INTSYM) {
				asmfile << "li $v0, 1" << endl;
			}
			else if (type == CHARSYM) {
				asmfile << "li $v0, 11" << endl;
			}
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
		if (is_not_global(name)) {	//对全局需要修改.data中的内容
			if (t.type == INTSYM) {
				asmfile << "li $v0,5" << endl;
			}
			else {
				asmfile << "li $v0,12" << endl;
			}
			asmfile << "syscall" << endl;
			asmfile << "sw $v0," << addr << "($sp)" << endl;	//局部变量的修改保存在栈中	
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
	else if (quad.op == "RET") {	//RET exp_name ~ ~
		string name = quad.para1;
		int addr = symbolTable.find(name).addr;
		string curfunc = symbolTable.curfunction;
		int funcsize = symbolTable.findf(curfunc).value;

		if (curfunc == "main") {
			asmfile << "li $v0," << 10 << endl;
			asmfile << "syscall" << endl;
		}
		else {
			asmfile << "lw $v0," << addr << "($sp)" << endl;
			asmfile << "lw $ra, 0($sp)" << endl;
			asmfile << "addi $sp, $sp," << funcsize << endl;
			asmfile << "jr $ra" << endl;
		}
		
	}
	else if (quad.op == "GLBSTR") {
		asmfile << ".data" << endl;
	}
	else if (quad.op == "GLBEND") {
		map<string, string>::iterator it;
		for (it = strTable.begin(); it != strTable.end(); it++) {	//写入所有字符串常量
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
	global = true;		//声明全局变量
	for (; index < quadnum; index++) {
		Quadruple q = quadTable[index];
		if (q.op == "GLBEND") {
			global = false;	//全局常变量声明结束
		}
		quad2asm(q);
	}
}

void Generator::close()
{
	asmfile.close();
}
