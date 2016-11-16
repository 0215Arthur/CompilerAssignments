#include "stdafx.h"
#include "global.h"



int ttype = 0, tident = 0;

void enter() {

}

//������::= �ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
void program() {
	getsym();

	//����������
	if (sym == CONSTSYM) {
		conststate();
	}

	//�����������
	if (sym == INTSYM || sym == CHARSYM) {	//��ҪԤ���ж��Ǳ������廹���з���ֵ��������
		backup();
		getsym();
		if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();

		if (sym == COMMA || sym == LBRACK) {		//����
			retrieve();
			varstate();		//���б���������Ӧ�����ﴦ�����
		}
		else if (sym == LPARENT) {
			retrieve();
			funcdef();		//ע������ֻ������һ���з���ֵ�ĺ���
		}
	}
	else {
		error(0);
	}

	//����������
	while (sym == INTSYM || sym == CHARSYM || sym == VOIDSYM) {
		if (sym == VOIDSYM) {
			backup();
			getsym();
			if (sym == MAINSYM) {
				break;
			}
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}
			getsym();
			if (sym == LPARENT) {
				retrieve();
				voidfdef();
			}
			else
			{
				error(MISSING_LPARENT);
			}
		}
		else {
			backup();
			getsym();
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}
			getsym();
			if (sym == LPARENT) {
				retrieve();
				funcdef();
			}
			else
			{
				error(MISSING_LPARENT);
			}
		}
	}

	//����main����
	if (sym == VOIDSYM) {
		mainfdef();
	}
	else
	{
		error(0);
	}

	cout << "This is a program!" << endl;
}

//������˵���� ::=  const���������壾;{ const���������壾;}
void conststate() {
	do
	{
		if (sym != CONSTSYM) {
			error(0);
		}
		getsym();
		constdef();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
	} while (sym == CONSTSYM);
	cout << "this is a const statement!" << endl;
}

//���������壾 ::=   int����ʶ��������������{,����ʶ��������������}
//					| char����ʶ���������ַ���{ ,����ʶ���������ַ��� }
void constdef() {
	if (sym == INTSYM) {
		getsym();
		if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();
		if (sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		getsym();
		if (sym == PLUSSYM || sym == MINUSSYM) {	//���ӷ�������� ::= +��-
			getsym();
		}
		if (sym == NUMSYM) {		//��������::= �ۣ������ݣ��޷�������������

		}
		else
		{
			error(WRONG_TYPE);
		}
		getsym();
		while (sym == COMMA) {
			getsym();
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}
			getsym();
			if (sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			getsym();
			if (sym == PLUSSYM || sym == MINUSSYM) {
				getsym();
			}
			if (sym != NUMSYM) {
				error(WRONG_TYPE);
			}
			getsym();
		}
	}
	else if (sym == CHARSYM) {
		getsym();
		if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();
		if (sym != ASSIGN) {
			error(MISSING_ASSIGN);
		}
		getsym();
		if (sym != CHARTY) {
			error(WRONG_TYPE);
		}
		getsym();
		while (sym == COMMA) {
			getsym();
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}
			getsym();
			if (sym != ASSIGN) {
				error(MISSING_ASSIGN);
			}
			getsym();
			if (sym != CHARTY) {
				error(WRONG_TYPE);
			}
			getsym();
		}
	}
	cout << "this is a const defination!" << endl;
}

//������˵���� ::= ���������壾;{���������壾;}
void varstate() {
	vardef();
	if (sym != SEMICOLON) {
		error(MISSING_SEMICOLON);
	}
	getsym();
	while (sym == INTSYM || sym == CHARSYM) {
		backup();
		getsym();
		if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();
		if (sym == COMMA || sym == LBRACK) {
			retrieve();
			vardef();
		}
		else if (sym == LPARENT || sym == VOIDSYM) {	//�����Ǳ�������
			retrieve();
			break;
		}
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
	}
	cout << "This is a var state!" << endl;
}

//���������壾::= �����ͱ�ʶ����(����ʶ����|����ʶ������[�����޷�����������]��){,(����ʶ����|����ʶ������[�����޷�����������]�� )}
void vardef() {
	if (sym == INTSYM || sym == CHARSYM) {
		getsym();
		if (sym == IDSYM) {
			getsym();
			if (sym == LBRACK) {
				getsym();
				if (sym != NUMSYM) {
					error(WRONG_TYPE);
				}
				else
				{
					//�����޷�������
				}
				getsym();
				if (sym != RBRACK)
				{
					error(MISSING_RBRACK);
				}
				getsym();
			}
			while (sym == COMMA) {
				getsym();
				if (sym == IDSYM) {
					getsym();
					if (sym == LBRACK) {
						getsym();
						if (sym != NUMSYM) {
							error(WRONG_TYPE);
						}
						else {
							//deal with no-sign number
						}
						getsym();
						if (sym != RBRACK) {
							error(MISSING_RBRACK);
						}
						getsym();
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
	cout << "This is a var defination" << endl;
}

//�������� ::=  �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}| ���գ�
void paralist() {
	if (sym == INTSYM || sym == CHARSYM) {
		getsym();
		if (sym == IDSYM) {
			getsym();
			while (sym == COMMA) {
				getsym();
				if (sym != INTSYM && sym != CHARSYM) {
					error(WRONG_TYPE);
				}
				getsym();
				if (sym == IDSYM) {
					//not implemented
				}
				else
				{
					error(MISSING_IDENT);
				}
				getsym();
			}
		}
	}
	cout << "This is a paralist!" << endl;
}

//��������䣾 ::= �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
void compound() {
	if (sym == CONSTSYM) {
		conststate();
	}
	if (sym == INTSYM || sym == CHARSYM) {
		varstate();
	}
	while (sym == IFSYM || sym == WHILESYM || sym == LBRACE || sym == INTSYM || sym == CHARSYM || sym == VOIDSYM
		|| sym == IDSYM || sym == PRINTFSYM || sym == SCANFSYM || sym == RETURNSYM || sym == SEMICOLON || sym == SWITCHSYM) {
		statement();
	}
	cout << "This is a compound statement!" << endl;
}

//���з���ֵ�������壾:: = ������ͷ������(������������)�� �� { ����������䣾�� }��
void funcdef() {
	if (sym == INTSYM || sym == CHARSYM) {
		getsym();
		if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();
		if (sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		getsym();
		paralist();
		if (sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		getsym();
		if (sym != LBRACE) {
			error(MISSING_LBRACE);
		}
		getsym();
		compound();
		if (sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		getsym();
	}
	else
	{
		error(WRONG_TYPE);
	}
	cout << "This is a fuction defination!" << endl;
}

//���޷���ֵ�������壾:: = void����ʶ������(������������)���� { ����������䣾�� }��
void voidfdef() {
	if (sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	getsym();
	if (sym == IDSYM) {
		getsym();
		if (sym != LPARENT) {
			error(MISSING_LPARENT);
		}
		getsym();
		paralist();
		if (sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		getsym();
		if (sym != LBRACE) {
			error(MISSING_LBRACE);
		}
		getsym();
		compound();
		if (sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		getsym();
	}
	else
	{
		error(MISSING_IDENT);
	}
	cout << "This is a void function define!" << endl;
}

//���������� ::= void main��(����)����{����������䣾��}��
void mainfdef() {
	if (sym != VOIDSYM) {
		error(MISSING_VOID);
	}
	getsym();
	if (sym != MAINSYM) {
		error(0);
	}
	getsym();
	if (sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	getsym();
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	getsym();
	if (sym != LBRACE) {
		error(MISSING_LBRACE);
	}
	compound();
	if (sym != RBRACE) {
		error(MISSING_RBRACE);
	}
	cout << "This is a main function" << endl;
}


//����䣾:: = ��������䣾����ѭ����䣾 | ��{ ��������У��� }�������з���ֵ����������䣾;
//				| ���޷���ֵ����������䣾; ������ֵ��䣾; ��������䣾; ����д��䣾; �����գ�; | �������䣾����������䣾;
void statement() {
	switch (sym)
	{
	case IFSYM: //ifstate
		ifstate();
		break;
	case WHILESYM:	//while state
		whilestate();
		break;
	case LBRACE:	//statement list
		getsym();
		while (sym == IFSYM || sym == WHILESYM || sym == LBRACE || sym == INTSYM || sym == CHARSYM || sym == VOIDSYM
			|| sym == IDSYM || sym == PRINTFSYM || sym == SCANFSYM || sym == RETURNSYM || sym == SEMICOLON || sym == SWITCHSYM) {
			statement();
		}
		if (sym != RBRACE) {
			error(MISSING_RBRACE);
		}
		getsym();
		break;
	case INTSYM:	//func with value
	case CHARSYM:
		funcdef();
		break;
	case VOIDSYM:	//void func
		voidfdef();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	case IDSYM:	//assignment
		assignstate();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	case PRINTFSYM:
		printfstate();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	case SCANFSYM:
		scanfstate();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	case SEMICOLON:
		getsym();
		break;
	case SWITCHSYM:
		switchstate();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	case RETURNSYM:
		returnstate();
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
		getsym();
		break;
	default:
		break;
	}
	cout << "This is a statement statement!" << endl;
}

//�����ʽ�� ::= �ۣ������ݣ��{���ӷ�����������}
void expression() {
	if (sym == PLUSSYM || sym == MINUSSYM) {
		getsym();
	}
	term();
	while (sym == PLUSSYM || sym == MINUSSYM) {
		getsym();
		term();
	}
	cout << "This is a expression!" << endl;
}

//��� ::= �����ӣ�{���˷�������������ӣ�}
void term() {
	factor();
	while (sym == MULTISYM || sym == DEVIDESYM) {
		getsym();
		factor();
	}
	cout << "This is a term!" << endl;
}

//�����ӣ� ::= ����ʶ����������ʶ������[�������ʽ����]��|��(�������ʽ����)������������|���ַ��������з���ֵ����������䣾 
void factor() {
	switch (sym)
	{
	case IDSYM:
		getsym();
		if (sym == LBRACK) {
			getsym();
			expression();
			if (sym != RBRACK) {
				error(MISSING_RBRACK);
			}
			getsym();
		}
		else if (sym == LPARENT) {	//���з���ֵ����������䣾 ::= ����ʶ������(����ֵ��������)��
			getsym();	//��ֵ������ ::= �����ʽ��{,�����ʽ��}�����գ�
			if (sym == IDSYM || sym == PLUSSYM || sym == MINUSSYM) {
				expression();
				getsym();
				while (sym == COMMA) {
					expression();
					getsym();
				}
			}			
		}
		break;
	case LPARENT:
		getsym();
		expression();
		if (sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		break;
	case PLUSSYM:
	case MINUSSYM:
		getsym();
		if (sym == NUMSYM) {
			//not implement yet!
		}
		else
		{
			error(WRONG_TYPE);
		}
		getsym();
		break;
		break;
	case NUMSYM:
		//not implement!
		getsym();
		break;
	case QUOTE:
		getsym();
		if (sym != CHARTY) {
			error(WRONG_TYPE);
		}
		getsym();
		if (sym != QUOTE) {
			error(CHAR_MISS_QUOTE);
		}
		getsym();
		break;
	default:
		error(0);
		break;
	}
	cout << "This is a factor!" << endl;
}

//��������䣾:: = if ��(������������)������䣾
void ifstate() {
	if (sym != IFSYM) {
		error(0);
	}
	getsym();
	if (sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	getsym();
	condition();
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	getsym();
	statement();
	cout << "This is an if statement!" << endl;
}

//��������::=  �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
void condition()
{
	expression();
	if (sym == LESS || sym == LESSEQU || sym == GREAT || sym == GREATEQU || sym == NEQUAL || sym == EQUAL) {
		getsym();
		expression();
	}
	else
	{
		error(0);
	}
	cout << "This is a condition statement!" << endl;
}

//����ֵ��䣾:: = ����ʶ�����������ʽ�� | ����ʶ������[�������ʽ����]�� = �����ʽ��
void assignstate() {
	if (sym != IDSYM) {
		error(MISSING_IDENT);
	}
	getsym();
	if (sym == LBRACK) {
		getsym();
		expression();
		getsym();
		if (sym != RBRACK) {
			error(MISSING_RBRACK);
		}
		getsym();
	}
	if (sym != ASSIGN) {
		error(0);
	}
	getsym();
	expression();
	cout << "This is an assign statement!" << endl;
}

//��ѭ����䣾:: = while ��(������������)������䣾
void whilestate() {
	if (sym != WHILESYM) {
		error(0);
	}
	getsym();
	if (sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	getsym();
	condition();
	getsym();
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	statement();
	cout << "This is a while statement!" << endl;
}

//�������䣾:: = switch ��(�������ʽ����)�� �� { �����������ȱʡ�� �� }��
void switchstate() {
	if (sym != SWITCHSYM) {
		error(0);
	}
	getsym();
	if (sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	getsym();
	expression();
	getsym();
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	getsym();
	if (sym == LBRACE) {		//�������::=  ���������䣾{���������䣾}
		getsym();
		while (sym == CASESYM) {
			casestate();
			getsym();
		}
		defaultstate();
	}
	getsym();
	if (sym != RBRACE) {
		error(MISSING_RBRACE);
	}
	cout << "This is a switch statement!" << endl;
}

//���������䣾:: = case��������������䣾
void casestate() {
	if (sym == CASESYM) {
		getsym();
		if (sym != NUMSYM && sym != QUOTE && sym != PLUSSYM && sym != MINUSSYM) {		//�������� ::= ��������|���ַ���
			error(WRONG_TYPE);
		}
		getsym();
		if (sym != COLON) {
			error(MISSING_COLON);
		}
		statement();
	}
	else
	{
		error(0);	//û��case
	}
	cout << "This is a case statement!" << endl;
}

//��ȱʡ��::=  default : ����䣾|���գ�
void defaultstate() {
	if (sym == DEFAULTSYM) {
		getsym();

	}
	cout << "This is a default statement!" << endl;
}

//������䣾::=  scanf ��(������ʶ����{,����ʶ����}��)��
void scanfstate() {
	if (sym == SCANFSYM) {
		getsym();
		if (sym == LPARENT) {
			getsym();
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}
			getsym();
			while (sym == COMMA) {
				getsym();
				if (sym != IDSYM) {
					error(MISSING_IDENT);
				}
				getsym();
			}
			if (sym != RPARENT) {
				error(MISSING_RPARENT);
			}
		}
		else
		{
			error(MISSING_LPARENT);
		}
	}
	else
	{
		error(0);
	}
	cout << "This is a scanf statement!" << endl;
}

//��д��䣾::= printf ��(�� ���ַ�����,�����ʽ�� ��)��| printf ��(�����ַ����� ��)��
//				| printf ��(�������ʽ����)��
void printfstate() {
	if (sym != PRINTFSYM) {
		error(0);
	}
	getsym();
	if (sym != LPARENT) {
		error(MISSING_LPARENT);
	}
	getsym();
	if (sym == STRING) {
		getsym();
		if (sym == COMMA) {
			getsym();
			expression();
		}
	}
	else if (sym == PLUSSYM || sym == MINUSSYM || sym == IDSYM) {
		expression();
	}
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	getsym();
	cout << "This is a printf statement!" << endl;
}

//��������䣾::=  return[��(�������ʽ����)��]     
void returnstate() {
	if (sym != RETURNSYM) {
		error(0);
	}
	getsym();
	if (sym == LPARENT) {
		getsym();
		expression();
		if (sym != RPARENT) {
			error(MISSING_RPARENT);
		}
		getsym();
	}
	cout << "This is a return statement!" << endl;
}