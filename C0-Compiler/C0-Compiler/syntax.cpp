#include "stdafx.h"
#include "global.h"

void enter();		//�����Ŵ�����ű�
void program();	//�������ĵݹ��ӳ���
void conststate();		//������˵���ĵݹ��ӳ���
void constdef();	//����������ĵݹ��ӳ���
void varstate();		//������������ĵݹ��ӳ���
void vardef();		//�����������ĵݹ��ӳ���
void headdef();	//����ͷ�����ĵݹ��ӳ���
void paralist();		//����������ʱ������ĵݹ��ӳ���
void funcdef();	//�����������ĵݹ��ӳ���
void statement();		//�������ĵݹ��ӳ���
void expression();	//������ʽ�ĵݹ��ӳ���
void term();	//������ĵݹ��ӳ���
void factor();	//�������ӵĵݹ��ӳ���
void assignstate();	//����ֵ���ĵݹ��ӳ���
void ifstate();	//����if���ĵݹ��ӳ���
void whilestate();	//����whileѭ�����ĵݹ��ӳ���
void switchstate();	//����switch�ĵݹ��ӳ���
void printfstate();		//����printf�ĵݹ��ӳ���
void scanfstate();		//����scanf�ĵݹ��ӳ���
void returnstate();	//����return�ĵݹ��ӳ���

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
			varstate();		//���б���������Ӧ�����ﴦ�����
		}
		else if (sym == LPARENT) {
			funcdef();		//ע������ֻ������һ���з���ֵ�ĺ���
		}
	}
	else {
		error(0);
	}

	//����������
	while (sym == INTSYM || sym == CHARSYM || sym == VOIDSYM) {
		backup();
		getsym();
		if (sym == MAINSYM) {
			retrieve();
			break;
		}
		else if (sym != IDSYM) {
			error(MISSING_IDENT);
		}
		getsym();
		if (sym == LPARENT) {
			funcdef();
		}
		else {

		}

	}

	//����main����




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
			getsym();
		}
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
		if (sym == PLUSSYM) {	//���ӷ�������� ::= +��-
			
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
	retrieve();
	vardef();
	if (sym != SEMICOLON) {
		error(MISSING_SEMICOLON);
	}
	getsym();
	backup();
	while (sym == INTSYM || sym == CHARSYM) {
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
			return;	
		}
		if (sym != SEMICOLON) {
			error(MISSING_SEMICOLON);
		}
	}
	cout << "This is a var state!" << endl;
}


//���������壾  ::= �����ͱ�ʶ����(����ʶ����|����ʶ������[�����޷�����������]��){,(����ʶ����|����ʶ������[�����޷�����������]�� )}
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
							getsym();
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
}

