#pragma once
#include<iostream>
#include<vector>
#include<mysql.h>
#include<string>
#include<iomanip>

using namespace std;

class EmployeeManage {
private:
	MYSQL mysql;
	MYSQL_RES* res; // �洢��ѯ����� res��Ϊ����������߿纯��ʱ�ͻ��Ϊnull��
	MYSQL_ROW row; // ��ȡ�����
	int fieldNums; // ��ǰ��ѯ��������ֶ���
	MYSQL_FIELD* fields; // ��ǰ��ѯ������ı�ͷ��Ϣ
	vector<string> empFields; // ����emp_info��ı�ͷ��Ϣ

	enum Optcode { // ������
		QUIT = 0,
		SHOW = 1,
		FIND = 2,
		SORT = 3,
		ADD = 4,
		DEL = 5,
		ALTER = 6,
		CLEAR = 7
	};

	int optIndex;

	void printMain(bool isRoot); // ��ӡ��ҳ��
	void showEmpInfo(); // ��ʾ����ְ����Ϣ
	void printTableHead(); // ��ӡ��ͷ��Ϣ
	void deleteEmpInfo(); // ɾ����ְԱ����Ϣ
	void alterEmpInfo(); // �޸�Ա����Ϣ
	void findEmpInfo(); // �޸�Ա����Ϣ	
	void sortById(); // ��Ա�����±��
	void clearAll(); // �����������
	void addEmpInfo(); // ����ְ����Ϣ

public:
	void mainEmpRoot();
	void mainEmpOrdinary();
	EmployeeManage();
	~EmployeeManage();
};
