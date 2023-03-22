#pragma once
#include<iostream>
#include<vector>
#include<mysql.h>
#include<string>
#include<iomanip>

using namespace std;

class UserManage {
private:
	MYSQL mysql;
	MYSQL_RES* res; // �洢��ѯ����� res��Ϊ����������߿纯��ʱ�ͻ��Ϊnull��
	MYSQL_ROW row; // ��ȡ�����
	int fieldNums; // ��ǰ��ѯ��������ֶ���
	MYSQL_FIELD* fields; // ��ǰ��ѯ������ı�ͷ��Ϣ
	vector<string> usrFields; // ����usr_info��ı�ͷ��Ϣ

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

	void printMain();
	void printTableHead(); // ��ӡ��ͷ��Ϣ
	void showUsrInfo(); // ��ʾ�����û��˺�
	void deleteUsrInfo(); // ɾ���û��˺�
	void alterUsrInfo(); // �޸��û��˺�
	void findUsrInfo(); // �޸��û��˺�
	void sortUsr(); // ���û��˺����±��
	void clearUsr(); // ��������û��˺�����
	void addUsrInfo(); // �����û��˺�

public:
	void mainUser();
	UserManage();
	~UserManage();

};
