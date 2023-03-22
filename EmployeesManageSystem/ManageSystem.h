#pragma once
#include<iostream>
#include<vector>
#include<mysql.h>
#include<string>
#include<iomanip>
#include "EmployeeManage.h"
#include "UserManage.h"

using namespace std;

class ManageSystem {
private:
	MYSQL mysql;
	MYSQL_RES* res; // �洢��ѯ����� res��Ϊ����������߿纯��ʱ�ͻ��Ϊnull��
	MYSQL_ROW row; // ��ȡ�����
	int fieldNums; // ��ǰ��ѯ��������ֶ���

	EmployeeManage em;
	UserManage um;

	string user_name;
	string user_pwd;
	bool isRoot; // ��¼��ǰ��¼�û��Ƿ���root�û�

	void loginPage(); // ʵ�ֵ�¼����
	void printLogin(); // ��ӡ��¼����

public:
	void mainPage(); // ���ڲ�������ϵͳ
	ManageSystem(); // �޲ι���
	~ManageSystem();
};