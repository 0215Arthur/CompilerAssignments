#include "stdafx.h"
#include "global.h"
#include "Parser.h"
#include "Lexer.h"
#include "defination.h"
#include "Quadruple.h"

int tab = 0;
bool debug = false;	//�Ƿ�������ģʽ,���Parser�еĴ���
//int ttype = 0, tident = 0;
string name = "";
string zeroname = "$value0";
int addr, kind, type, number;
long long value;
int temp_index = 0, lab_index = 0;
bool retsign = false;
//debug�ú���,ֻ��Ϊ��console���������,��������
void tabf() {
	int i = 0;
	while (i < tab) {
		cout << "|---";
		i++;
	}
}

//������ת��Ϊ�ַ���,����������Ԫʽ
string num2str(long long n) {
	return to_string(n);
}

//����һ���������ʱ������,todo:ע�����������Ҫ�޸�
string newtmpname() {
	string a = "$temp";
	string b = num2str(temp_index++);
	return a + b;
}

string newlab() {
	string a = "Lab";
	string b = num2str(lab_index++);
	return a + b;
}

//������ת��Ϊ�ַ���,����������Ԫʽ
string type2str(int type) {
	if (type == INTSYM) {
		return "INT";
	}
	else if (type == CHARSYM) {
		return "CHAR";
	}
	else if (type == VOIDSYM) {
		return "VOID";
	}
	else {
		return "";
	}
}


string op2str(int op) {
	if (op == PLUSSYM) {
		return "+";
	}
	else if (op == MINUSSYM) {
		return "-";
	}
	else if (op == MULTISYM) {
		return "*";
	}
	else if (op == DEVIDESYM) {
		return "/";
	}
	else {
		return "";
	}
}

//�������������Ϣ�ĺ���,�ڿ����Ƿ���Ҫ����һ��	
void Parser::error(int errorid)
{
	errorNum++;
	switch (errorid) {
	case CASE_TYPE_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "case����������,��ʶ�����Ͳ���ȷ!" << endl;
		break;
	case UNDEF_ID:
		cout << "Parser Error: line" << Lexer::line << ":" << "ʹ����δ����ı�ʶ��" << Lexer::token << endl;
		break;
	case MULTI_DEF:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ض����ʶ��" << Lexer::token << endl;
		break;
	case ID_TOO_LONG:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʶ������!" << endl;
		break;
	case PROGRAM_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "����ṹ����!" << endl;
		break;
	case STR_CONTENT_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ַ������ַǷ�����!" << endl;
		break;
	case STR_TOO_LONG:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ַ�������,��벻Ҫ����" << STRING_MAXLENGTH << "���ַ�!" << endl;
		break;
	case ZERO_HEAD_NUM:
		cout << "Parser Error: line" << Lexer::line << ":" << "�������ֲ�����ǰ����!" << endl;
		break;
	case NUM_HEAD_IDENT:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʶ�����������ֿ�ͷ!" << endl;
		break;
	case NUM_TOO_LARGE:
		cout << "Parser Error: line" << Lexer::line << ":" << "���ֹ���! �벻Ҫ����32λ�����������Χ!" << endl;
		break;
	case CHAR_MISS_QUOTE:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ַ����Ͷ�ʧ������!" << endl;
		break;
	case CHAR_CONTENT_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ַ����ݲ��Ϸ�!" << endl;
		break;
	case CHAR_OVERFLOW:
		cout << "Parser Error: line" << Lexer::line << ":" << "�ַ�ascii�����!" << endl;
		break;
	case NEQUAL_MISS:
		cout << "Parser Error: line" << Lexer::line << ":" << "����ʹ�ò��Ⱥ�! Ӧʹ��'!='" << endl;
		break;
	case MISSING_SEMI:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�ֺ�! ����ֺ��Ƿ�ƥ��!" << endl;
		break;
	case MISSING_RPARENT:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ������!" << endl;
		break;
	case MISSING_RBRACK:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ��������!" << endl;
		break;
	case MISSING_RBRACE:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�Ҵ�����!" << endl;
		break;
	case MISSING_IDENT:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ��ʶ��!" << endl;
		break;
	case MISSING_LPARENT:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ������!" << endl;
		break;
	case MISSING_LBRACK:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ��������!" << endl;
		break;
	case MISSING_LBRACE:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�������!" << endl;
		break;
	case MISSING_PLUS:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�ӺŻ����!" << endl;
		break;
	case MISSING_MULTI:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�˺Ż����!" << endl;
		break;
	case ASSIGN_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ֵʱ��������!" << endl;
		break;
	case RETURN_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "����ֵ����!" << endl;
		break;
	case MISSING_MAIN:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧmain����!" << endl;
		break;
	case MISSING_RETURN:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧreturn���!" << endl;
		break;
	case EXPRESSION_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "���ʽ����!" << endl;
		break;
	case OUT_OF_TABLE:
		cout << "Parser Error: line" << Lexer::line << ":" << "���ű�����!" << endl;
		break;
	case OUT_OF_ARRAY:
		cout << "Parser Error: line" << Lexer::line << ":" << "�������!" << endl;
		break;
	case WRONG_TYPE:
		cout << "Parser Error: line" << Lexer::line << ":" << "�������ʹ���!" << endl;
		break;
	case MISSING_ASSIGN:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧ�Ⱥ�!" << endl;
		break;
	case MISSING_COLON:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧð��!" << endl;
		break;
	case MISSING_VOID:
		cout << "Parser Error: line" << Lexer::line << ":" << "��ʧvoid�ؼ���!" << endl;
		break;
	case MISSING_DOUQUOTE:
		cout << "Parser Error: line" << Lexer::line << ":" << "����ȱʧ!" << endl;
		break;
	case CONST_TYPE_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "�������ʹ���,����ֻ������int����char���ͣ�" << endl;
		break;
	case ERROR_PARA_NUM:
		cout << "Parser Error: line" << Lexer::line << ":" << "��������ʱ���������쳣��" << endl;
		break;
	default:
		cout << "Parser Error: line" << Lexer::line << ":" << "������δ֪����!" << endl;	//��������Զ������ִ�е�����
		break;
	}
}

//���������������,������Ҫ�����ķ��ż�,�������з��ż��е��ַ�
void Parser::skip(set<int> symset)
{
	while (symset.count(Lexer::sym)) {
		Lexer::getsym();
	}
}

//������::= �ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
void Parser::program() {
	if (debug) {
		tabf();
		cout << "program" << endl;
	}

	Lexer::getsym();
	//����������
	quadTable.push_back(Quadruple("GLBSTR", "", "", ""));
	if (Lexer::sym == CONSTSYM) {
		conststate();
	}

	//�����������
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {	//��ҪԤ���ж��Ǳ������廹���з���ֵ��������
		Lexer::backup();
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		Lexer::getsym();

		if (Lexer::sym == COMMA || Lexer::sym == LBRACK) {		//����
			Lexer::retrieve();
			varstate();		//���б���������Ӧ�����ﴦ�����
		}
		else if (Lexer::sym == LPARENT) {
			Lexer::retrieve();	//���ﲻ��
		}
	}
	quadTable.push_back(Quadruple("GLBEND", "", "", ""));
	//����һ���̶���0
	symbolTable.con_insert(zeroname, INTSYM,0);
	symbolTable.setzero(zeroname);
	//����������
	while (Lexer::sym == INTSYM || Lexer::sym == CHARSYM || Lexer::sym == VOIDSYM) {
		if (Lexer::sym == VOIDSYM) {
			Lexer::backup();
			Lexer::getsym();
			if (Lexer::sym == MAINSYM) {
				Lexer::retrieve();
				break;
			}
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			Lexer::getsym();
			if (Lexer::sym == LPARENT) {
				Lexer::retrieve();
				voidfdef();
			}
			else {
				error(MISSING_LPARENT);
			}
		}
		else {
			Lexer::backup();
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			Lexer::getsym();
			if (Lexer::sym == LPARENT) {
				Lexer::retrieve();
				funcdef();
			}
			else {
				error(MISSING_LPARENT);
			}
		}
	}

	//����main����
	if (Lexer::sym == VOIDSYM) {
		mainfdef();
	}
	else {
		error(0);
	}
}

//������˵���� ::=  const���������壾;{ const���������壾;}	//qfinish
void Parser::conststate() {
	if (debug) {
		tab++;
		tabf();
		cout << "const statement!" << endl;
	}

	do {
		if (Lexer::sym != CONSTSYM) {
			error(0);	//�������򲻿��ܵ���˷�֧
		}
		Lexer::getsym();
		constdef();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
	} while (Lexer::sym == CONSTSYM);
	tab--;
}

//���������壾 ::=   int����ʶ��������������{,����ʶ��������������}
//					| char����ʶ���������ַ���{ ,����ʶ���������ַ��� }
void Parser::constdef() {
	//todo:��ֵͬ�ĳ������Ժϲ���һ��,���Ż�
	int sign = 1;	//sign == 1 Ϊ����, -1Ϊ����
	if (debug) {
		tab++;
		tabf();
		cout << "const defination" << endl;
	}

	if (Lexer::sym == INTSYM) {
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		else {
			name = Lexer::token;
			Lexer::getsym();
		}
		if (Lexer::sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		Lexer::getsym();
		if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {	//���ӷ�������� ::= +��-
			if (Lexer::sym == MINUSSYM) {
				sign = -1;
			}
			Lexer::getsym();
		}
		if (Lexer::sym == NUMTY) {		//��������::= �ۣ������ݣ��޷�������������
			value = Lexer::value * sign;
			if (symbolTable.con_insert(name, INTSYM, value)) {	//����ֵ����һ˵���Ѿ���������ͬ��ʶ���ĳ�/����
				error(MULTI_DEF);
			}
			else {
				quadTable.push_back(Quadruple("CON", name, "INT", num2str(value)));
			}
		}
		else {
			error(WRONG_TYPE);
		}
		Lexer::getsym();
		while (Lexer::sym == COMMA) {
			sign = 1;
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			else {
				name = Lexer::token;
				Lexer::getsym();
			}
			if (Lexer::sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			Lexer::getsym();
			if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
				if (Lexer::sym == MINUSSYM) {
					sign = -1;
				}
				Lexer::getsym();
			}
			if (Lexer::sym != NUMTY) {
				error(WRONG_TYPE);
			}
			else {
				value = Lexer::value * sign;
				if (symbolTable.con_insert(name, INTSYM, value)) {
					error(MULTI_DEF);
				}
				else {
					quadTable.push_back(Quadruple("CON", name, "INT", num2str(value)));
				}
			}
			Lexer::getsym();
		}
	}
	else if (Lexer::sym == CHARSYM) {
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		name = Lexer::token;
		Lexer::getsym();
		if (Lexer::sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		Lexer::getsym();
		if (Lexer::sym != CHARTY) {
			error(WRONG_TYPE);
		}
		else {
			value = Lexer::value;
			if (symbolTable.con_insert(name, CHARSYM, value)) {
				error(MULTI_DEF);
			}
			else {
				quadTable.push_back(Quadruple("CON", name, "CHAR", num2str(value)));
			}
		}
		Lexer::getsym();
		while (Lexer::sym == COMMA) {
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			name = Lexer::token;
			Lexer::getsym();
			if (Lexer::sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			Lexer::getsym();
			if (Lexer::sym != CHARTY) {
				error(WRONG_TYPE);
			}
			else {
				value = Lexer::value;
				if (symbolTable.con_insert(name, CHARSYM, value)) {
					error(MULTI_DEF);
				}
				else {
					quadTable.push_back(Quadruple("CON", name, "CHAR", to_string(long long(value))));
				}
			}
			Lexer::getsym();
		}
	}
	else {
		error(CONST_TYPE_ERROR);	//����ֻ������int����char����
	}
	tab--;
}

//������˵���� ::= ���������壾;{���������壾;}	//qfinish
void Parser::varstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "var statement" << endl;
	}

	vardef();
	if (Lexer::sym != SEMICOLON) {
		error(MISSING_SEMI);
	}
	Lexer::getsym();
	while (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		Lexer::backup();
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		Lexer::getsym();
		if (Lexer::sym == COMMA || Lexer::sym == LBRACK || Lexer::sym == SEMICOLON) {	//not proved
			Lexer::retrieve();
			vardef();
		}
		else if (Lexer::sym == LPARENT || Lexer::sym == VOIDSYM) {	//�����Ǳ�������
			Lexer::retrieve();
			break;
		}
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
	}
	tab--;
}

//���������壾::= �����ͱ�ʶ����(����ʶ����|����ʶ������[�����޷�����������]��){,(����ʶ����|����ʶ������[�����޷�����������]�� )}	//qfinish
void Parser::vardef() {
	if (debug) {
		tab++;
		tabf();
		cout << "var defination" << endl;
	}

	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		type = Lexer::sym;
		Lexer::getsym();
		if (Lexer::sym == IDSYM) {
			name = Lexer::token;
			Lexer::getsym();
			if (Lexer::sym == LBRACK) {	//��������
				Lexer::getsym();
				if (Lexer::sym != NUMTY) {
					error(WRONG_TYPE);
				}
				else {
					number = Lexer::value;	//��¼���鳤��
				}
				Lexer::getsym();
				if (Lexer::sym != RBRACK) {
					error(MISSING_RBRACK);
				}
				if (symbolTable.arr_insert(name, type, number)) {
					error(MULTI_DEF);
				}
				else {
					quadTable.push_back(Quadruple("ARR", name, type2str(type), num2str(number)));
				}
				Lexer::getsym();
			}
			else {	//��һ��������
				if (symbolTable.var_insert(name, type)) {
					error(MULTI_DEF);
				}
				else {
					quadTable.push_back(Quadruple("VAR", name, type2str(type), ""));
				}
			}
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym == IDSYM) {
					name = Lexer::token;
					Lexer::getsym();
					if (Lexer::sym == LBRACK) {	//����
						Lexer::getsym();
						if (Lexer::sym != NUMTY) {
							error(WRONG_TYPE);
						}
						else {
							number = Lexer::value;	//��¼�����С
						}
						Lexer::getsym();
						if (Lexer::sym != RBRACK) {
							error(MISSING_RBRACK);
						}
						if (symbolTable.arr_insert(name, type, number)) {
							error(MULTI_DEF);
						}
						else {
							quadTable.push_back(Quadruple("ARR", name, type2str(type), num2str(number)));
						}
						Lexer::getsym();
					}
					else {	//��һ��������
						if (symbolTable.var_insert(name, type)) {
							error(MULTI_DEF);
						}
						else {
							quadTable.push_back(Quadruple("VAR", name, type2str(type), ""));
						}
					}
				}
				else {
					error(MISSING_IDENT);
				}
			}
		}
		else
			error(MISSING_IDENT);
	}
	else {
		error(0);
	}
	tab--;
}

//�������� ::=  �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}| ���գ�	//qfinish
void Parser::paralist() {
	if (debug) {

		tab++;
		tabf();
		cout << "paralist" << endl;
	}
	number = 0;	//��ʼ��¼�����ĸ���
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		type = Lexer::sym;
		Lexer::getsym();
		if (Lexer::sym == IDSYM) {
			name = Lexer::token;
			if (symbolTable.para_insert(name, type)) {
				error(MULTI_DEF);
			}
			else {
				number++;
				//quadTable.push_back(Quadruple("PARA", name, type2str(type), ""));
			}
			Lexer::getsym();
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym != INTSYM && Lexer::sym != CHARSYM) {
					error(WRONG_TYPE);
				}
				else {
					type = Lexer::sym;
				}
				Lexer::getsym();
				if (Lexer::sym == IDSYM) {
					name = Lexer::token;
					if (symbolTable.para_insert(name, type)) {
						error(MULTI_DEF);
					}
					else {
						number++;
						//quadTable.push_back(Quadruple("PARA", name, type2str(type), ""));
					}
				}
				else {
					error(MISSING_IDENT);
				}
				Lexer::getsym();
			}
		}
	}
	tab--;
}

//��������䣾 ::= �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�	//qfinish
void Parser::compound() {
	if (debug) {
		tab++;
		tabf();
		cout << "compound" << endl;

	}
	if (Lexer::sym == CONSTSYM) {
		conststate();
	}
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		varstate();
	}
	while (Lexer::sym == IFSYM || Lexer::sym == WHILESYM || Lexer::sym == LBRACE || Lexer::sym == INTSYM || Lexer::sym == CHARSYM || Lexer::sym == VOIDSYM
		|| Lexer::sym == IDSYM || Lexer::sym == PRINTFSYM || Lexer::sym == SCANFSYM || Lexer::sym == RETURNSYM || Lexer::sym == SEMICOLON || Lexer::sym == SWITCHSYM) {
		statement();
	}
	tab--;
}

//���з���ֵ�������壾:: = ������ͷ������(������������)�� �� { ����������䣾�� }��
void Parser::funcdef() {
	if (debug) {
		tab++;
		tabf();
		cout << "funcdef" << endl;
	}
	retsign = false;
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		int ftype = Lexer::sym;
		string fname = "";
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		else {
			fname = Lexer::token;
			if (symbolTable.func_insert(fname, ftype, 0)) {	//ע����ʱ��û������para�ĸ���,����curlevel�Ѿ��ı�
				error(MULTI_DEF);
			}
			else {
				quadTable.push_back(Quadruple("FUNC", fname, type2str(ftype), ""));	//������ʼ,����label+����ջ�ռ�+���淵��ֵ
				Lexer::getsym();
			}
		}
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		paralist();
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		symbolTable.setfuncnum(fname, number);	//��ʱ������ʽ��������ӷ���
		Lexer::getsym();
		if (Lexer::sym != LBRACE) {
			error(MISSING_LBRACE);
		}
		Lexer::getsym();
		compound();
		if (Lexer::sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		Lexer::getsym();
	}
	else {
		error(WRONG_TYPE);
	}
	if (!retsign) {	//��û��return��ʱ�����END�����к����ķ���
		quadTable.push_back(Quadruple("END", "", "", ""));
	}
	symbolTable.setfuncsize();
	tab--;
}

//���޷���ֵ�������壾:: = void����ʶ������(������������)���� { ����������䣾�� }��
void Parser::voidfdef() {
	if (debug) {
		tab++;
		tabf();
		cout << "voidfdef" << endl;
	}
	retsign = false;
	if (Lexer::sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	else {
		type = Lexer::sym;
		Lexer::getsym();
	}
	if (Lexer::sym == IDSYM) {
		string fname = Lexer::token;
		if (symbolTable.func_insert(fname, type, 0)) {
			error(MULTI_DEF);
		}
		else {
			quadTable.push_back(Quadruple("FUNC", fname, "VOID", ""));	//������ʼ,����label+����ջ�ռ�+���淵��ֵ
			Lexer::getsym();
		}
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		paralist();
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		symbolTable.setfuncnum(fname, number);
		Lexer::getsym();
		if (Lexer::sym != LBRACE) {
			error(MISSING_LBRACE);
		}
		Lexer::getsym();
		compound();
		if (Lexer::sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		Lexer::getsym();
	}
	else {
		error(MISSING_IDENT);
	}
	tab--;
	if (!retsign) {
		quadTable.push_back(Quadruple("END", "", "", ""));
	}
	symbolTable.setfuncsize();
}

//���������� ::= void main��(����)����{����������䣾��}��
void Parser::mainfdef() {
	if (debug) {
		tab++;
		tabf();
		cout << "main" << endl;
	}
	if (Lexer::sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	Lexer::getsym();
	if (Lexer::sym != MAINSYM) {
		error(0);
	}
	symbolTable.func_insert("main", VOIDSYM, 0);	//������ֻ����һ������,����curlevel
	quadTable.push_back(Quadruple("FUNC", "main", "VOID", ""));	//������ֻ����һ��������ʽ
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	if (Lexer::sym != LBRACE) {
		error(MISSING_LBRACE);
	}
	Lexer::getsym();
	compound();
	if (Lexer::sym != RBRACE) {
		error(MISSING_RBRACE);
	}
	symbolTable.setfuncsize();
	tab--;
}

//����䣾:: = ��������䣾����ѭ����䣾 | ��{ ��������У��� }�������з���ֵ����������䣾;
//				| ���޷���ֵ����������䣾; ������ֵ��䣾; ��������䣾; ����д��䣾; �����գ�; | �������䣾����������䣾;
void Parser::statement() {
	if (debug) {
		tab++;
		tabf();
		cout << "statement" << endl;
	}
	switch (Lexer::sym) {
	case IFSYM: //ifstate
		ifstate();
		break;
	case WHILESYM:	//while state
		whilestate();
		break;
	case LBRACE:	//statement list
		Lexer::getsym();
		while (Lexer::sym == IFSYM || Lexer::sym == WHILESYM || Lexer::sym == LBRACE || Lexer::sym == INTSYM || Lexer::sym == CHARSYM || Lexer::sym == VOIDSYM
			|| Lexer::sym == IDSYM || Lexer::sym == PRINTFSYM || Lexer::sym == SCANFSYM || Lexer::sym == RETURNSYM || Lexer::sym == SEMICOLON || Lexer::sym == SWITCHSYM) {
			statement();
		}
		if (Lexer::sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		Lexer::getsym();
		break;
	case IDSYM:	//assignment or callfunc
		Lexer::backup();
		Lexer::getsym();
		if (Lexer::sym == LPARENT) {
			Lexer::retrieve();
			string temp = "";
			int temp_type = 0;
			calfunc(temp, temp_type);
		}
		else {
			Lexer::retrieve();
			assignstate();
		}
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	case PRINTFSYM:		//printstate
		printfstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	case SCANFSYM:		//scanstate
		scanfstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	case SEMICOLON:		//blankstate
		Lexer::getsym();
		break;
	case SWITCHSYM:		//switchstate
		switchstate();
		Lexer::getsym();
		break;
	case RETURNSYM:		//returnstate
		returnstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	default:
		break;
	}
	tab--;
}

//�����ʽ�� ::= �ۣ������ݣ��{���ӷ�����������}
void Parser::expression(string &exp_name, int &exp_type) {
	if (debug) {
		tab++;
		tabf();
		cout << "expression" << endl;
	}
	//���������õ���ر���
	int exp_value = 0;
	int op = 0;
	exp_type = NUMTY;
	exp_name = "";

	string term_name1 = "", term_name2 = "";
	int  term_type1=0, term_type2=0;

	//��ʽ��ʼ��������
	if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
		op = Lexer::sym;
		Lexer::getsym();
	}
	term(term_name1, term_type1);
	if (op == MINUSSYM) {
		quadTable.push_back(Quadruple("~", term_name1, "", ""));	//����ȡ������
	}

	while (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
		op = Lexer::sym;
		Lexer::getsym();
		term(term_name2, term_type2);
		if (op == PLUSSYM) {
			quadTable.push_back(Quadruple("+", term_name1, term_name2, term_name1));
		}
		else {
			quadTable.push_back(Quadruple("-", term_name1, term_name2, term_name1));
		}
	}
	if (term_type1 == INTSYM || term_type2 == INTSYM) {
		exp_type = INTSYM;
	}
	else {
		exp_type = CHARSYM;
	}
	tab--;
	exp_name = term_name1;
}

//��� ::= �����ӣ�{���˷�������������ӣ�}
void Parser::term(string &term_name, int &term_type) {
	if (debug) {
		tab++;
		tabf();
		cout << "term" << endl;
	}
	string factor_name1 = "", factor_name2 = "";
	int factor_type1=0, factor_type2=0;
	term_name = "";
	term_type = 0;

	factor(factor_name1, factor_type1);
	while (Lexer::sym == MULTISYM || Lexer::sym == DEVIDESYM) {
		int sign = Lexer::sym;
		Lexer::getsym();
		factor(factor_name2, factor_type2);
		if (sign == MULTISYM) {
			quadTable.push_back(Quadruple("*", factor_name1, factor_name2, factor_name1));
		}
		else {
			quadTable.push_back(Quadruple("/", factor_name1, factor_name2, factor_name1));
		}
	}
	if (factor_type1 == INTSYM || factor_type2 == INTSYM) {	//����termtype, ע��ֻҪ��������CHARSYM���,�����ΪINT��
		term_type = INTSYM;
	}
	else {
		term_type = CHARSYM;
	}
	term_name = factor_name1;
	tab--;
}

//�����ӣ� ::= ����ʶ����������ʶ������[�������ʽ����]��|��(�������ʽ����)������������|���ַ��������з���ֵ����������䣾 
void Parser::factor(string &factor_name, int &factor_type) {
	if (debug) {
		tab++;
		tabf();
		cout << "factor" << endl;
	}
	string name = "";
	factor_name = "";
	factor_type = 0;
	switch (Lexer::sym) {
	case IDSYM:	//������������з���ֵ�ĺ�������
		name = Lexer::token;
		if (!symbolTable.in_table(name)) {
			error(UNDEF_ID);
		}
		Lexer::backup();
		Lexer::getsym();
		if (Lexer::sym == LBRACK) {	//������
			Lexer::getsym();
			factor_name = newtmpname();
			factor_type = symbolTable.find(name).type;
			symbolTable.var_insert(factor_name, factor_type);
			string arrindex = "";
			int arrtype;
			expression(arrindex, arrtype);
			quadTable.push_back(Quadruple("LODARR", name, arrindex, factor_name));	//����Ϊname�������е�arrindex��Ԫ�ص�ֵ�浽factor_name��Ӧ����ʱ������
			if (Lexer::sym != RBRACK) {
				error(MISSING_RBRACK);
			}
			Lexer::getsym();
		}
		else if (Lexer::sym == LPARENT) {	//�Ǻ���,��calfunc��������ز���
			Lexer::retrieve();
			calfunc(factor_name, factor_type);
		}
		else {	//�ǵ�һ���� //todo:����ɽ����Ż�
			factor_name = newtmpname();
			factor_type = symbolTable.find(name).type;
			symbolTable.var_insert(factor_name, factor_type);
			quadTable.push_back(Quadruple("LODV", factor_name, name, ""));		//��name��ֵ���浽factor_name��Ӧ����ʱ������(λ��Stack)
		}
		break;
	case LPARENT:
		Lexer::getsym();
		expression(factor_name, factor_type);
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		Lexer::getsym();
		break;
	case MINUSSYM:
		Lexer::getsym();
		if (Lexer::sym == NUMTY) {
			factor_name = newtmpname();
			value = -1 * Lexer::value;		//ע����Ҫ��value���෴��
			factor_type = INTSYM;
			symbolTable.var_insert(factor_name, INTSYM);
			quadTable.push_back(Quadruple("LODI", factor_name, num2str(value), ""));
		}
		else {
			error(WRONG_TYPE);
		}
		Lexer::getsym();
		break;
	case PLUSSYM:
		Lexer::getsym();
	case NUMTY:
		factor_name = newtmpname();
		value = Lexer::value;
		factor_type = INTSYM;
		symbolTable.var_insert(factor_name, INTSYM);
		quadTable.push_back(Quadruple("LODI", factor_name, num2str(value), ""));
		Lexer::getsym();
		break;
	case CHARTY:
		factor_name = newtmpname();
		factor_type = CHARSYM;
		symbolTable.var_insert(factor_name, CHARSYM);
		quadTable.push_back(Quadruple("LODI", factor_name, num2str(Lexer::value), ""));
		Lexer::getsym();
		break;
	default:
		error(0);	//��������²�����ִ�����˷�֧
		break;
	}
	tab--;
}

//��������䣾:: = if ��(������������)������䣾
void Parser::ifstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "if statement" << endl;
	}
	if (Lexer::sym != IFSYM) {
		error(0);	//������������������ߵ��˷�֧
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	string label = newlab();
	condition(label);
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	statement();
	quadTable.push_back(Quadruple("LAB", label, "", ""));
	tab--;
}

//��������::=  �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
void Parser::condition(string label)
{
	if (debug) {
		tab++;
		tabf();
		cout << "condition" << endl;
	}
	int ctype;
	string exp_name1 = "", exp_name2 = "";
	expression(exp_name1, ctype);
	if (Lexer::sym == LESS || Lexer::sym == LESSEQU || Lexer::sym == GREAT || Lexer::sym == GREATEQU || Lexer::sym == NEQUAL || Lexer::sym == EQUAL) {
		int op = Lexer::sym;
		Lexer::getsym();
		expression(exp_name2, ctype);
		switch (op) {		//�������˵�Сtrick,��������Ҫ����label�ĸ���
		case LESS:
			quadTable.push_back(Quadruple("GTE", exp_name1, exp_name2, label));
			break;
		case LESSEQU:
			quadTable.push_back(Quadruple("GREAT", exp_name1, exp_name2, label));
			break;
		case GREAT:
			quadTable.push_back(Quadruple("LTE", exp_name1, exp_name2, label));
			break;
		case GREATEQU:
			quadTable.push_back(Quadruple("LESS", exp_name1, exp_name2, label));
			break;
		case NEQUAL:
			quadTable.push_back(Quadruple("EQU", exp_name1, exp_name2, label));
			break;
		case EQUAL:
			quadTable.push_back(Quadruple("NEQ", exp_name1, exp_name2, label));
			break;
		default:
			break;
		}
	}
	else {
		quadTable.push_back(Quadruple("EQU", exp_name1, "0", label));
	}
	tab--;
}

//����ֵ��䣾:: = ����ʶ�����������ʽ�� | ����ʶ������[�������ʽ����]�� = �����ʽ��	//todo:finish here
void Parser::assignstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "assign statement" << endl;
	}
	string exname = "";
	string name = "";
	int extype;
	string offsetname = zeroname;
	if (Lexer::sym != IDSYM) {
		error(MISSING_IDENT);
	}
	else {
		name = Lexer::token;
		int kind = symbolTable.getkind(name);
		if (kind != VAR && kind != ARR) {
			error(ASSIGN_ERROR);	//���Ǳ������͸�ֵ
		}
	}
	Lexer::getsym();
	if (Lexer::sym == LBRACK) {		//�����е�Ԫ�ظ�ֵ
		Lexer::getsym();
		expression(offsetname, type);
		if (Lexer::sym != RBRACK) {
			error(MISSING_RBRACK);
		}
		Lexer::getsym();
	}
	else {

	}
	if (Lexer::sym != ASSIGN) {
		error(0);
	}
	Lexer::getsym();
	expression(exname, extype);
	quadTable.push_back(Quadruple("=", name, offsetname, exname));
	tab--;
}

//��ѭ����䣾:: = while ��(������������)������䣾
void Parser::whilestate() {
	if (debug) {
		tab++;
		tabf();
		cout << "while statement" << endl;
	}
	string label1 = newlab(), label2 = newlab();
	if (Lexer::sym != WHILESYM) {
		error(0);	//�˷�֧���ɴ�
	}
	quadTable.push_back(Quadruple("LAB", label2, "", ""));
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	condition(label1);
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	statement();
	quadTable.push_back(Quadruple("JMP", label2, "", ""));
	quadTable.push_back(Quadruple("LAB", label1, "", ""));
	tab--;
}

//�������䣾:: = switch ��(�������ʽ����)�� �� { �����������ȱʡ�� �� }��
void Parser::switchstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "switch statement" << endl;
	}
	int exp_type;
	string exp_name = "";
	string labfin = newlab();
	if (Lexer::sym != SWITCHSYM) {
		error(0);	//�˷�֧���ɴ�
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	expression(exp_name, exp_type);
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	if (Lexer::sym == LBRACE) {		//�������::=  ���������䣾{���������䣾}
		Lexer::getsym();
		while (Lexer::sym == CASESYM) {
			casestate(exp_name, labfin);
		}
		defaultstate();
	}
	if (Lexer::sym != RBRACE) {
		error(MISSING_RBRACE);
	}
	quadTable.push_back(Quadruple("LAB", labfin, "", ""));
	tab--;
}

//���������䣾:: = case��������������䣾
void Parser::casestate(string exp_name, string label) {
	if (debug) {
		tab++;
		tabf();
		cout << "case statement" << endl;
	}
	string caselab = newlab();
	string convalue = newtmpname();
	if (Lexer::sym == CASESYM) {
		Lexer::getsym();
		if (Lexer::sym == NUMTY || Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
			if (Lexer::sym == PLUSSYM) {
				Lexer::getsym();
				value = Lexer::value;
			}
			else if (Lexer::sym == MINUSSYM) {
				Lexer::getsym();
				value = -1 * Lexer::value;
			}
			else {
				value = Lexer::value;
			}
			symbolTable.var_insert(convalue, INTSYM);
			quadTable.push_back(Quadruple("LODI", convalue, num2str(value), ""));
			Lexer::getsym();
		}
		else if (Lexer::sym == CHARTY) {
			Lexer::getsym();
			symbolTable.var_insert(convalue, INTSYM);
			quadTable.push_back(Quadruple("LODI", convalue, num2str(value), ""));
		}
		else {
			error(CASE_TYPE_ERROR);
		}
		if (Lexer::sym != COLON) {
			error(MISSING_COLON);
		}
		quadTable.push_back(Quadruple("NEQ", exp_name, convalue, caselab));
		Lexer::getsym();
		statement();
	}
	else {
		error(0);	//û��case
	}
	quadTable.push_back(Quadruple("JMP", label, "", ""));
	quadTable.push_back(Quadruple("LAB", caselab, "", ""));
	tab--;
}

//��ȱʡ��::=  default : ����䣾|���գ�
void Parser::defaultstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "default statement" << endl;
	}
	if (Lexer::sym == DEFAULTSYM) {
		Lexer::getsym();
		if (Lexer::sym != COLON) {
			error(MISSING_COLON);
		}
		Lexer::getsym();
		statement();
	}
	tab--;
}

//������䣾::=  scanf ��(������ʶ����{,����ʶ����}��)��
void Parser::scanfstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "scanf statement" << endl;
	}
	string name = "";
	if (Lexer::sym == SCANFSYM) {
		Lexer::getsym();
		if (Lexer::sym == LPARENT) {
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			name = Lexer::token;
			quadTable.push_back(Quadruple("SCF", name, "", ""));
			Lexer::getsym();
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym != IDSYM) {
					error(MISSING_IDENT);
				}
				name = Lexer::token;
				quadTable.push_back(Quadruple("SCF", name, "", ""));
				Lexer::getsym();
			}
			if (Lexer::sym != RPARENT) {
				error(MISSING_RPARENT);
			}
			Lexer::getsym();
		}
		else {
			error(MISSING_LPARENT);
		}
	}
	else {
		error(0);
	}
	tab--;
}

//��д��䣾::= printf ��(�� ���ַ�����,�����ʽ�� ��)��| printf ��(�����ַ����� ��)��
//				| printf ��(�������ʽ����)��
void Parser::printfstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "printf statement" << endl;
	}
	string str = "", exp_name = "", type = "";
	int exp_type;
	Quadruple q;
	if (Lexer::sym != PRINTFSYM) {
		error(0);	//��������������ߵ��˷�֧
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);	//��ʧ�����žͲ�getsym��,������Ӱ������������
	}
	else {
		Lexer::getsym();
	}
	if (Lexer::sym == STRING) {
		bool exist = false;
		string key = "";
		map<string, string>::iterator it;
		for (it = strTable.begin(); it != strTable.end(); it++) {
			if (Lexer::token == it->second) {
				key = it->first;
				exist = true;
				break;
			}
		}
		if (!exist) {	//���в�����,��Ӳ���
			key = "$string" + num2str(stbIndex++);
			strTable[key] = Lexer::token;
			str = key;
		}
		else {	//���д���,ֱ��ʹ����key
			str = key;
		}
		type = "0";
		Lexer::getsym();
		if (Lexer::sym == COMMA) {
			type = "2";
			Lexer::getsym();
			expression(exp_name, exp_type);
		}
	}
	else {
		type = "1";
		expression(exp_name, exp_type);
	}
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);	//�ݴ���
	}
	else {
		Lexer::getsym();
	}
	q.fill("PRT", str, exp_name, type);
	quadTable.push_back(q);
	tab--;
}

//��������䣾::=  return[��(�������ʽ����)��]     
void Parser::returnstate() {
	if (debug) {
		tab++;
		tabf();
		cout << "return statement" << endl;
	}
	string exp_name = "";
	int exp_type;
	if (Lexer::sym != RETURNSYM) {
		error(0);	//��������޷��ﵽ�˷�֧
	}
	Lexer::getsym();
	if (Lexer::sym == LPARENT) {
		Lexer::getsym();
		expression(exp_name, exp_type);
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		quadTable.push_back(Quadruple("RET", exp_name, "", ""));
		Lexer::getsym();
	}
	else {	//return���ޱ��ʽ
		quadTable.push_back(Quadruple("RET", "", "", ""));
	}
	retsign = true;
	tab--;
}

//���з���ֵ����������䣾 :: = ����ʶ������(����ֵ��������)��
//���޷���ֵ����������䣾 :: = ����ʶ������(����ֵ��������)��
//��ֵ������ ::= �����ʽ��{,�����ʽ��}�����գ�
void Parser::calfunc(string &fac_value, int &fac_type) {
	if (debug) {
		tab++;
		tabf();
		cout << "call function" << endl;
	}
	int exp_type;
	string func_name;
	string para_name;
	fac_value = newtmpname();	
	if (Lexer::sym == IDSYM) {
		func_name = Lexer::token;
		fac_type = symbolTable.find(func_name).type;
		symbolTable.var_insert(fac_value, fac_type);
		Lexer::getsym();
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		//Ԥ�����ò�����������Щ����ѧ= =
		int paracount = 0;
		int maxpara = symbolTable.find(func_name).number;
		if (Lexer::sym == IDSYM || Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM || Lexer::sym == LPARENT || Lexer::sym == NUMTY || Lexer::sym == CHARTY) {

			expression(para_name, exp_type);
			symbolTable.var_insert(para_name, exp_type);
			paracount += 1;
			quadTable.push_back(Quadruple("PARA", para_name, num2str(paracount), func_name));
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				expression(para_name, exp_type);
				symbolTable.var_insert(para_name, exp_type);
				paracount += 1;
				quadTable.push_back(Quadruple("PARA", para_name, num2str(paracount), func_name));
			}
		}
		if (paracount != maxpara) {
			error(ERROR_PARA_NUM);
		}
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		Lexer::getsym();
		quadTable.push_back(Quadruple("CALL", func_name, "", ""));
	}
	else {
		error(0);
	}
	quadTable.push_back(Quadruple("LODR", fac_value, "$v0", ""));	//�ں����ķ���ֵ(λ��$v0)д�ص�ջ��
	tab--;
}