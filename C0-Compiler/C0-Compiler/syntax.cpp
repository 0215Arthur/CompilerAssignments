#include "stdafx.h"
#include "global.h"

void enter();		//�����Ŵ�����ű�
void inttype();	//���������ĵݹ��ӳ���
void consttype();	//�����������͵ĵݹ��ӳ���
void program();	//�������ĵݹ��ӳ���
void conststate();		//������˵���ĵݹ��ӳ���
void constdef();	//����������ĵݹ��ӳ���
void varstate();		//������������ĵݹ��ӳ���
void vardef();		//�����������ĵݹ��ӳ���
void paralist();		//����������ʱ������ĵݹ��ӳ���
void compound();	//����������ĵݹ��ӳ���
void funcdef();	//�����з���ֵ���������ĵݹ��ӳ���
void voidfdef();	//�����޷���ֵ�ĺ��������ĵݹ��ӳ���
void statement();		//�������ĵݹ��ӳ���
void expression();	//������ʽ�ĵݹ��ӳ���
void term();	//������ĵݹ��ӳ���
void factor();	//�������ӵĵݹ��ӳ���
void assignstate();	//����ֵ���ĵݹ��ӳ���
void ifstate();	//����if���ĵݹ��ӳ���
void condition();	//�����������ĵݹ��ӳ���
void whilestate();	//����whileѭ�����ĵݹ��ӳ���
void switchstate();	//����switch�ĵݹ��ӳ���
void casestate();	//����case�ĵݹ��ӳ���
void defaultstate();	//����default�ĵݹ��ӳ���
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
		}
		else {
			backup();
			getsym();
			if (sym != IDSYM) {
				error(MISSING_IDENT);
			}

		}
		/*backup();
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

		}*/

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

//�������� ::=  �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}| ���գ�
void paralist() {
	if (sym == INTSYM || sym == CHARSYM) {
		getsym();
		if (sym == IDSYM) {
			getsym();
			while (sym == COMMA) {
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
	while (sym==IFSYM || sym == WHILESYM	) {			//not finished!!!!!!!!//////////////////
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
		compound();
		getsym();
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

//����䣾:: = ��������䣾����ѭ����䣾 | ��{ ��������У��� }�������з���ֵ����������䣾;
//| ���޷���ֵ����������䣾; ������ֵ��䣾; ��������䣾; ����д��䣾; �����գ�; | �������䣾����������䣾;
void statement() {
	cout << "This is a statement statement!" << endl;
}

//�����ʽ�� ::= �ۣ������ݣ��{���ӷ�����������}
void expression() {
	if (sym == PLUSSYM) {
		getsym();
	}
	term();
	while (sym == PLUSSYM) {
		getsym();
		term();
	}
	cout << "This is a expression!" << endl;
}

//��� ::= �����ӣ�{���˷�������������ӣ�}
void term() {
	cout << "This is a term!" << endl;
}

//�����ӣ� ::= ����ʶ����������ʶ������[�������ʽ����]��|��(�������ʽ����)������������|���ַ��������з���ֵ����������䣾 
void factor() {
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
	getsym();
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
	statement();
	cout << "This is an if statement!" << endl;
}

//��������::=  �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
void condition()
{
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
	}
	getsym();
	if (sym != EQUAL) {
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
		if (sym != NUMSYM || sym != CHARTY) {	//����������//////////////////////////////////
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
	else if (sym == PLUSSYM || sym == IDSYM) {
		expression();
	}
	if (sym != RPARENT) {
		error(MISSING_RPARENT);
	}
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
		getsym();
		if (sym != RPARENT) {
			error(MISSING_RPARENT);
		}
	}
	cout << "This is a return statement!" << endl;
}