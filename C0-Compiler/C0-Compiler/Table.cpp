#include "StdAfx.h"
#include "Table.h"


Table::Table(string name)
{
	offset = 0;
	curlevel = 0;
	topfunction = name;
	curfunction = topfunction;
	func_insert(curfunction, VOIDSYM, 0);
}


Table::~Table()
{
}

bool Table::in_table(string iname)
{
	for (int i = 0; i < items.size(); i++) {
		if (items[i].name == iname) {
			return true;
		}
	}
	return false;
}

TableItem Table::find(string name)
{
	TableItem item;
	int length = items.size();
	for (int i = curlevel+1; i < length; i++) {	//���ҵ�ǰ��
		item = items[i];
		if (item.name == name) {
			return item;
		}
		if (item.kind == FUNC) {
			break;
		}
	}
	for (int i = 1; i < length; i++) {	//����ȫ�ֱ���
		if (items[i].name == name) {
			return items[i];
		}
		if (items[i].kind == FUNC) {
			break;
		}
	}
	return item;
}

bool Table::is_con(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		if (ti.kind == CON) {
			return true;
		}
	}
	return false;
}

bool Table::is_var(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		if (ti.kind == VAR) {
			return true;
		}
	}
	return false;
}

bool Table::is_arr(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		if (ti.kind == ARR) {
			return true;
		}
	}
	return false;
}

bool Table::is_para(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		if (ti.kind == PARA) {
			return true;
		}
	}
	return false;
}

bool Table::is_func(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		if (ti.kind == FUNC) {
			return true;
		}
	}
	return false;
}

int Table::getkind(string name)
{
	if (in_table(name)) {
		TableItem ti = find(name);
		return ti.kind;
	}
	return 0;
}

int Table::gettype(string name)
{
	if (in_table(name)) {
		return find(name).type;
	}
	return -1;
}

int Table::getvalue(string name)
{
	if (in_table(name)) {
		return find(name).value;
	}
	return 0;
}

int Table::setfuncnum(string name, int number)
{
	if (!in_table(name)) {
		return 1;
	}
	for (int i = curlevel; i < items.size(); i++) {
		if (items[i].name == name && items[i].kind == FUNC) {
			items[i].number = number;
			return 0;
		}
	}
	return 1;
}

int Table::setfuncsize()
{
	items[curlevel].value = offset;

	return 0;
}

//����ű��в��볣��
int Table::con_insert(string name, int type, int value)
{
	if (in_table(name)) {
		return 1;
	}
	this->items.push_back(TableItem(name, offset, CON, type, value, 0, curfunction));
	offset += 4;
	return 0;
}

//����ű��в������
int Table::var_insert(string name, int type)
{
	if (in_table(name)) {
		return 1;
	}
	this->items.push_back(TableItem(name, offset, VAR, type, 0, 0, curfunction));
	offset += 4;
	return 0;
}

int Table::arr_insert(string name, int type, int num)
{
	if (in_table(name)) {
		return 1;
	}
	this->items.push_back(TableItem(name, offset, ARR, type, 0, num, curfunction));
	offset += 4 * num;
	return 0;
}

int Table::para_insert(string name, int type)
{
	if (in_table(name)) {
		return 1;
	}
	this->items.push_back(TableItem(name, offset, PARA, type, 0, 0, curfunction));
	offset += 4;
	return 0;
}

int Table::func_insert(string name, int type, int num)
{
	if (in_table(name)) {
		return 1;
	}
	funcloc[name] = items.size();
	offset = 0;
	curlevel = funcloc[name];
	items.push_back(TableItem(name, 0, FUNC, type, 0, num, curfunction));
	offset += 4;
	return 0;
}

int Table::temp_insert(string name, int type)
{
	if (in_table(name)) {
		return 1;
	}
	this->items.push_back(TableItem(name, offset, TEMP, type, 0, 0, curfunction));
	offset += 4;
	return 0;
}

