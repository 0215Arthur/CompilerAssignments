#include "stdafx.h"
#include "global.h"
#include "Parser.h"
#include "Lexer.h"
#include "defination.h"
#include "Quadruple.h"

int tab = 0;
//int ttype = 0, tident = 0;

//û��ʵ������ĺ���,ֻ��Ϊ��console���������,��������
void tabf() {
	int i = 0;
	while (i < tab) {
		cout << "|---";
		i++;
	}
}


//TODO:�Ƿ�error����һ��
//�������������Ϣ�ĺ���,�ڿ����Ƿ���Ҫ����һ��	
void Parser::error(int errorid)
{
	errornum++;
	switch (errorid) {
	case CASE_TYPE_ERROR:
		cout << "Parser Error: line" << Lexer::line << ":" << "case����������,��ʶ�����Ͳ���ȷ!" << endl;
		break;
	case UNDEF_ID:
		cout << "Parser Error: line" << Lexer::line << ":" << "ʹ����δ����ı�ʶ��" << Lexer::token<<endl;
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
		/*case UNDEF_INPUT:
			cout << "Parser Error: line" << Lexer::line << ":"  << "���Ϸ�����!" << endl;
			break;*/
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
	default:
		cout << "Parser Error: line" << Lexer::line << ":" << "������δ֪����!" << endl;	//��������Զ������ִ�е�����
		break;
	}
}

//������::= �ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
void Parser::program() {
	/*tab += 1;*/
	tabf();
	cout << "program" << endl;

	Lexer::getsym();
	//����������
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
			Lexer::retrieve();
			funcdef();		//ע������ֻ������һ���з���ֵ�ĺ���
		}
	}

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

//������˵���� ::=  const���������壾;{ const���������壾;}
void Parser::conststate() {
	tab++;
	tabf();
	cout << "const statement!" << endl;
	do {
		if (Lexer::sym != CONSTSYM) {
			error(0);
		}
		Lexer::getsym();
		constdef();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
	} while (Lexer::sym == CONSTSYM);
	tab--;
	//cout << "this is a const statement!" << endl;
}

//���������壾 ::=   int����ʶ��������������{,����ʶ��������������}
//					| char����ʶ���������ַ���{ ,����ʶ���������ַ��� }
void Parser::constdef() {
	tab++;
	tabf();
	cout << "const defination" << endl;
	if (Lexer::sym == INTSYM) {
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		Lexer::getsym();
		if (Lexer::sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		Lexer::getsym();
		if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {	//���ӷ�������� ::= +��-
			Lexer::getsym();
		}
		if (Lexer::sym == NUMSYM) {		//��������::= �ۣ������ݣ��޷�������������

		}
		else {
			error(WRONG_TYPE);
		}
		Lexer::getsym();
		while (Lexer::sym == COMMA) {
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			Lexer::getsym();
			if (Lexer::sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			Lexer::getsym();
			if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
				Lexer::getsym();
			}
			if (Lexer::sym != NUMSYM) {
				error(WRONG_TYPE);
			}
			Lexer::getsym();
		}
	}
	else if (Lexer::sym == CHARSYM) {
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		Lexer::getsym();
		if (Lexer::sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		Lexer::getsym();
		if (Lexer::sym != CHARTY) {
			error(WRONG_TYPE);
		}
		Lexer::getsym();
		while (Lexer::sym == COMMA) {
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			Lexer::getsym();
			if (Lexer::sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			Lexer::getsym();
			if (Lexer::sym != CHARTY) {
				error(WRONG_TYPE);
			}
			Lexer::getsym();
		}
	}
	tab--;
	//cout << "this is a const defination!" << endl;
}

//������˵���� ::= ���������壾;{���������壾;}
void Parser::varstate() {
	tab++;
	tabf();
	cout << "var statement" << endl;
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
	//cout << "This is a var state!" << endl;
}

//���������壾::= �����ͱ�ʶ����(����ʶ����|����ʶ������[�����޷�����������]��){,(����ʶ����|����ʶ������[�����޷�����������]�� )}
void Parser::vardef() {
	tab++;
	tabf();
	cout << "var defination" << endl;
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		Lexer::getsym();
		if (Lexer::sym == IDSYM) {
			Lexer::getsym();
			if (Lexer::sym == LBRACK) {
				Lexer::getsym();
				if (Lexer::sym != NUMSYM) {
					error(WRONG_TYPE);
				}
				else {
					//�����޷�������
				}
				Lexer::getsym();
				if (Lexer::sym != RBRACK) {
					error(MISSING_RBRACK);
				}
				Lexer::getsym();
			}
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym == IDSYM) {
					Lexer::getsym();
					if (Lexer::sym == LBRACK) {
						Lexer::getsym();
						if (Lexer::sym != NUMSYM) {
							error(WRONG_TYPE);
						}
						else {
							//deal with no-sign number
						}
						Lexer::getsym();
						if (Lexer::sym != RBRACK) {
							error(MISSING_RBRACK);
						}
						Lexer::getsym();
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
	//cout << "This is a var defination" << endl;
}

//�������� ::=  �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}| ���գ�
void Parser::paralist() {
	tab++;
	tabf();
	cout << "paralist" << endl;
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		Lexer::getsym();
		if (Lexer::sym == IDSYM) {
			Lexer::getsym();
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym != INTSYM && Lexer::sym != CHARSYM) {
					error(WRONG_TYPE);
				}
				Lexer::getsym();
				if (Lexer::sym == IDSYM) {
					//not implemented
				}
				else {
					error(MISSING_IDENT);
				}
				Lexer::getsym();
			}
		}
	}
	tab--;
	//cout << "This is a paralist!" << endl;
}

//��������䣾 ::= �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
void Parser::compound() {
	tab++;
	tabf();
	cout << "compound" << endl;
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
	//cout << "This is a compound statement!" << endl;
}

//���з���ֵ�������壾:: = ������ͷ������(������������)�� �� { ����������䣾�� }��
void Parser::funcdef() {
	tab++;
	tabf();
	cout << "funcdef" << endl;
	if (Lexer::sym == INTSYM || Lexer::sym == CHARSYM) {
		Lexer::getsym();
		if (Lexer::sym != IDSYM) {
			error(MISSING_IDENT);
		}
		Lexer::getsym();
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		paralist();
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
		Lexer::getsym();
	}
	else {
		error(WRONG_TYPE);
	}
	tab--;
	//cout << "This is a fuction defination!" << endl;
}

//���޷���ֵ�������壾:: = void����ʶ������(������������)���� { ����������䣾�� }��
void Parser::voidfdef() {
	tab++;
	tabf();
	cout << "voidfdef" << endl;
	if (Lexer::sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	Lexer::getsym();
	if (Lexer::sym == IDSYM) {
		Lexer::getsym();
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		paralist();
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
		Lexer::getsym();
	}
	else {
		error(MISSING_IDENT);
	}
	tab--;
	//cout << "This is a void function define!" << endl;
}

//���������� ::= void main��(����)����{����������䣾��}��
void Parser::mainfdef() {
	tab++;
	tabf();
	cout << "main" << endl;
	if (Lexer::sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	Lexer::getsym();
	if (Lexer::sym != MAINSYM) {
		error(0);
	}
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
	//cout << "This is a main function" << endl;
	tab--;
}


//����䣾:: = ��������䣾����ѭ����䣾 | ��{ ��������У��� }�������з���ֵ����������䣾;
//				| ���޷���ֵ����������䣾; ������ֵ��䣾; ��������䣾; ����д��䣾; �����գ�; | �������䣾����������䣾;
void Parser::statement() {
	tab++;
	tabf();
	cout << "statement" << endl;
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
			calfunc();
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
	case PRINTFSYM:
		printfstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	case SCANFSYM:
		scanfstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	case SEMICOLON:
		Lexer::getsym();
		break;
	case SWITCHSYM:
		switchstate();
		Lexer::getsym();
		break;
	case RETURNSYM:
		returnstate();
		if (Lexer::sym != SEMICOLON) {
			error(MISSING_SEMI);
		}
		Lexer::getsym();
		break;
	default:
		break;
	}
	//cout << "This is a statement statement!" << endl;
	tab--;
}

//�����ʽ�� ::= �ۣ������ݣ��{���ӷ�����������}
void Parser::expression() {
	tab++;
	tabf();
	cout << "expression" << endl;
	if (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
		Lexer::getsym();
	}
	term();
	while (Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
		Lexer::getsym();
		term();
	}
	//cout << "This is a expression!" << endl;
	tab--;
}

//��� ::= �����ӣ�{���˷�������������ӣ�}
void Parser::term() {
	tab++;
	tabf();
	cout << "term" << endl;
	factor();
	while (Lexer::sym == MULTISYM || Lexer::sym == DEVIDESYM) {
		Lexer::getsym();
		factor();
	}
	//cout << "This is a term!" << endl;
	tab--;
}

//�����ӣ� ::= ����ʶ����������ʶ������[�������ʽ����]��|��(�������ʽ����)������������|���ַ��������з���ֵ����������䣾 
void Parser::factor() {
	tab++;
	tabf();
	cout << "factor" << endl;
	switch (Lexer::sym) {
	case IDSYM:
		Lexer::backup();
		Lexer::getsym();
		if (Lexer::sym == LBRACK) {
			Lexer::getsym();
			expression();
			if (Lexer::sym != RBRACK) {
				error(MISSING_RBRACK);
			}
			Lexer::getsym();
		}
		else if (Lexer::sym == LPARENT) {
			Lexer::retrieve();
			calfunc();
		}
		break;
	case LPARENT:
		Lexer::getsym();
		expression();
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		Lexer::getsym();
		break;
	case PLUSSYM:
	case MINUSSYM:
		Lexer::getsym();
		if (Lexer::sym == NUMSYM) {
			//not implement yet!
		}
		else {
			error(WRONG_TYPE);
		}
		Lexer::getsym();
		break;
		break;
	case NUMSYM:
		//todo:implement!
		Lexer::getsym();
		break;
	case CHARTY:
		//todo:implement!
		Lexer::getsym();
		break;
	default:
		error(0);
		break;
	}
	//cout << "This is a factor!" << endl;
	tab--;
}

//��������䣾:: = if ��(������������)������䣾
void Parser::ifstate() {
	tab++;
	tabf();
	cout << "if statement" << endl;
	if (Lexer::sym != IFSYM) {
		error(0);
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	condition();
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	statement();
	//cout << "This is an if statement!" << endl;
	tab--;
}

//��������::=  �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
void Parser::condition()
{
	tab++;
	tabf();
	cout << "condition" << endl;
	expression();
	if (Lexer::sym == LESS || Lexer::sym == LESSEQU || Lexer::sym == GREAT || Lexer::sym == GREATEQU || Lexer::sym == NEQUAL || Lexer::sym == EQUAL) {
		Lexer::getsym();
		expression();
	}
	//cout << "This is a condition statement!" << endl;
	tab--;
}

//����ֵ��䣾:: = ����ʶ�����������ʽ�� | ����ʶ������[�������ʽ����]�� = �����ʽ��
void Parser::assignstate() {
	tab++;
	tabf();
	cout << "assign statement" << endl;
	if (Lexer::sym != IDSYM) {
		error(MISSING_IDENT);
	}
	Lexer::getsym();
	if (Lexer::sym == LBRACK) {
		Lexer::getsym();
		expression();
		if (Lexer::sym != RBRACK) {
			error(MISSING_RBRACK);
		}
		Lexer::getsym();
	}
	if (Lexer::sym != ASSIGN) {
		error(0);
	}
	Lexer::getsym();
	expression();
	//cout << "This is an assign statement!" << endl;
	tab--;
}

//��ѭ����䣾:: = while ��(������������)������䣾
void Parser::whilestate() {
	tab++;
	tabf();
	cout << "while statement" << endl;
	if (Lexer::sym != WHILESYM) {
		error(0);
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	condition();
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	statement();
	//cout << "This is a while statement!" << endl;
	tab--;
}

//�������䣾:: = switch ��(�������ʽ����)�� �� { �����������ȱʡ�� �� }��
void Parser::switchstate() {
	tab++;
	tabf();
	cout << "switch statement" << endl;
	if (Lexer::sym != SWITCHSYM) {
		error(0);
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	Lexer::getsym();
	expression();
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	Lexer::getsym();
	if (Lexer::sym == LBRACE) {		//�������::=  ���������䣾{���������䣾}
		Lexer::getsym();
		while (Lexer::sym == CASESYM) {
			casestate();
		}
		defaultstate();
	}
	if (Lexer::sym != RBRACE) {
		error(MISSING_RBRACE);
	}
	//cout << "This is a switch statement!" << endl;
	tab--;
}

//���������䣾:: = case��������������䣾
void Parser::casestate() {
	tab++;
	tabf();
	cout << "case statement" << endl;
	if (Lexer::sym == CASESYM) {
		Lexer::getsym();
		//if (Lexer::sym != NUMSYM && Lexer::sym != QUOTE && Lexer::sym != PLUSSYM && Lexer::sym != MINUSSYM) {		//�������� ::= ��������|���ַ���
		//	error(WRONG_TYPE);
		//}
		if (Lexer::sym == NUMSYM || Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM) {
			if (Lexer::sym == PLUSSYM) {
				Lexer::getsym();
			}
			else if (Lexer::sym == MINUSSYM) {
				Lexer::getsym();
			}
			Lexer::getsym();
		}
		else if (Lexer::sym == CHARTY) {
			Lexer::getsym();
		}
		else {
			error(CASE_TYPE_ERROR);
		}
		if (Lexer::sym != COLON) {
			error(MISSING_COLON);
		}
		Lexer::getsym();
		statement();
	}
	else {
		error(0);	//û��case
	}
	//cout << "This is a case statement!" << endl;
	tab--;
}

//��ȱʡ��::=  default : ����䣾|���գ�
void Parser::defaultstate() {
	tab++;
	tabf();
	cout << "default statement" << endl;
	if (Lexer::sym == DEFAULTSYM) {
		Lexer::getsym();
		if (Lexer::sym != COLON) {
			error(MISSING_COLON);
		}
		Lexer::getsym();
		statement();
	}

	//cout << "This is a default statement!" << endl;
	tab--;
}

//������䣾::=  scanf ��(������ʶ����{,����ʶ����}��)��
void Parser::scanfstate() {
	tab++;
	tabf();
	cout << "scanf statement" << endl;
	if (Lexer::sym == SCANFSYM) {
		Lexer::getsym();
		if (Lexer::sym == LPARENT) {
			Lexer::getsym();
			if (Lexer::sym != IDSYM) {
				error(MISSING_IDENT);
			}
			Lexer::getsym();
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				if (Lexer::sym != IDSYM) {
					error(MISSING_IDENT);
				}
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
	//cout << "This is a scanf statement!" << endl;
	tab--;
}

//��д��䣾::= printf ��(�� ���ַ�����,�����ʽ�� ��)��| printf ��(�����ַ����� ��)��
//				| printf ��(�������ʽ����)��
void Parser::printfstate() {
	tab++;
	tabf();
	cout << "printf statement" << endl;
	string str, exp, type;
	Quadruple q;
	if (Lexer::sym != PRINTFSYM) {
		error(-1);	//��������������ߵ��˷�֧
	}
	Lexer::getsym();
	if (Lexer::sym != LPARENT) {
		error(MISSING_LPARENT);	//��ʧ�����žͲ�getsym��,������Ӱ������������
	}
	else {
		Lexer::getsym();
	}
	if (Lexer::sym == STRING) {
		//todo:����һ���ַ���������table��,��Ҫ�ܹ����ʵ�����λ��
		//note:ͬһ���ַ���������Ӧ�ñ���������,��������Ѿ�����ͬ���ַ�����ֹͣ����
		type = "0";
		Lexer::getsym();
		if (Lexer::sym == COMMA) {
			type = "2";
			Lexer::getsym();
			expression();
		}
	}
	else {
		type = "1";
		expression();
	}
	if (Lexer::sym != RPARENT) {
		error(MISSING_RPARENT);	//�ݴ���
	}
	else {
		Lexer::getsym();
	}
	q.fill("PRT", str, exp, type);
	//quadtable.push_back(q);
	//cout << "This is a printf statement!" << endl;
	tab--;
}

//��������䣾::=  return[��(�������ʽ����)��]     
void Parser::returnstate() {
	tab++;
	tabf();
	cout << "return statement" << endl;
	if (Lexer::sym != RETURNSYM) {
		error(0);
	}
	Lexer::getsym();
	if (Lexer::sym == LPARENT) {
		Lexer::getsym();
		expression();
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		Lexer::getsym();
	}
	//cout << "This is a return statement!" << endl;
	tab--;
}

//���з���ֵ����������䣾 :: = ����ʶ������(����ֵ��������)��
//���޷���ֵ����������䣾 :: = ����ʶ������(����ֵ��������)��
//��ֵ������ ::= �����ʽ��{,�����ʽ��}�����գ�
void Parser::calfunc() {
	tab++;
	tabf();
	cout << "call function" << endl;
	if (Lexer::sym == IDSYM) {
		Lexer::getsym();
		if (Lexer::sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		Lexer::getsym();
		if (Lexer::sym == IDSYM || Lexer::sym == PLUSSYM || Lexer::sym == MINUSSYM || Lexer::sym == LPARENT ||Lexer::sym == NUMSYM || Lexer::sym == CHARTY) {
			expression();
			while (Lexer::sym == COMMA) {
				Lexer::getsym();
				expression();
			}
		}
		if (Lexer::sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		Lexer::getsym();
	}
	else {
		error(0);
	}
	tab--;
}