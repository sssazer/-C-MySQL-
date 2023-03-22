#include "UserManage.h"

void UserManage::printMain() {
	cout << "**************************" << endl;
	cout << "***��ӭʹ���û�����ϵͳ***" << endl;
	cout << "******0-�˳�����ϵͳ******" << endl;
	cout << "******1-��ʾ�û��˺�******" << endl;
	cout << "******2-�����û��˺�******" << endl;
	cout << "******3-�� �� �� ��*******" << endl;
	cout << "******4-�����û��˺�******" << endl;
	cout << "******5-ɾ���û��˺�******" << endl;
	cout << "******6-�޸��û��˺�******" << endl;
	cout << "******7-��������˺�******" << endl;
	cout << "**************************" << endl;
	cout << "**************************" << endl;
}

void UserManage::printTableHead() {
	for (int i = 0; i < usrFields.size(); i++) {
		cout << setw(20) << left << usrFields[i];
	}
	cout << endl;
}

/// <summary>
/// ���Ա����Ϣ
/// </summary>
void UserManage::addUsrInfo() {

	while (true) { // ������Ϣ����ʱѭ������

#pragma region ��ӡ���棬���벢��������
		system("cls");
		cout << "�����˺�" << endl;
		cout << "�������û�����20���ַ����ڣ���";
		string new_name;
		cin >> new_name;
		cout << "���������루20���ַ����ڣ���";
		string new_pwd;
		cin >> new_pwd;
		cout << "�Ƿ���rootȨ�ޣ�0/1����";
		char new_root;
		cin >> new_root;
#pragma endregion	

#pragma region ���ݶ��������γ�SQL��� ��ִ��
		string querySQL = "insert into usr_info (user_name, user_pwd, authority) values (\""
			+ new_name + "\",\"" + new_pwd + "\",\"" + new_root + "\")";

		if (mysql_query(&mysql, querySQL.c_str())) {
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			cout << "�����ʽ��������������" << endl;
			system("pause");
			continue;
		}

		cout << "��ӳɹ�" << endl;
		system("pause");
		break;

	} // while_true
#pragma endregion
}

/// <summary>
/// ��ʾ����Ա����Ϣ
/// </summary>
void UserManage::showUsrInfo() {

#pragma region ��ѯ�������ݲ���������
	string querySql = "select * from usr_info";
	mysql_query(&mysql, querySql.c_str());
	res = mysql_store_result(&mysql);
#pragma endregion

#pragma region ��ӡ��ͷ
	printTableHead();
#pragma endregion

#pragma region ��ӡ������Ϣ
	while (row = mysql_fetch_row(res)) {
		for (int i = 0; i < usrFields.size(); i++) {
			if (row[i]) {
				cout << setw(20) << left << row[i];
			}
			else {
				cout << setw(20) << left << "���ޣ�";
			}
		}
		cout << endl;
	}
#pragma endregion

	// �ͷŽ����
	mysql_free_result(res);
}

/// <summary>
/// ͨ��ID������ɾ��Ա����Ϣ
/// </summary>
void UserManage::deleteUsrInfo() {
	while (true) {
#pragma region ��ӡ��ʾ��Ϣ����ȡ����
		system("cls");

		cout << "������Ҫɾ�����˺ŵ��û���������q�˳�����";
		string strInfo;
		cin >> strInfo;
		if (strInfo == "q") {
			break;
		}
#pragma endregion

#pragma region ɾ��ָ���û���
		else {
			string querySQL = "delete from usr_info where user_name = \"" + strInfo + "\"";
			if (mysql_query(&mysql, querySQL.c_str())) {
				cout << "�����ʽ����������������" << endl;
				cout << "error_msg:" << mysql_error(&mysql) << endl;
				system("pause");
			}
			else if (mysql_affected_rows(&mysql)) {
				cout << "ɾ���ɹ�" << endl;
				system("pause");
				break;
			}
			else {
				cout << "ɾ��ʧ�ܣ�δ�ҵ��û���Ϊ" << strInfo << "���˺���Ϣ" << endl;
				system("pause");
			}
		}
#pragma endregion
	} // while-true
}


void UserManage::alterUsrInfo() {
	while (true) {
#pragma region ����Ҫ�޸ĵ�Ա����Ϣ
		system("cls");
		cout << "������Ҫ�޸��˺ŵ��û�������q�˳�����";
		string targetName;
		cin >> targetName;
		if (targetName == "q") {
			break;
		}
#pragma endregion

#pragma region �ж��û����Ƿ����
		string querySQL = "select * from usr_info where user_name = \"" + targetName + "\"";
		if (mysql_query(&mysql, querySQL.c_str())) {
			cout << "�����ʽ��������������" << endl;
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			continue;
		}
		res = mysql_store_result(&mysql);
		if (row = mysql_fetch_row(res)) { // �û������ڵĻ��ʹ�ӡ�˺���Ϣ
			printTableHead();
			for (int i = 0; i < usrFields.size(); i++) {
				if (row[i]) {
					cout << setw(20) << left << row[i];
				}
				else {
					cout << setw(20) << left << "���գ�";
				}
			}
			cout << endl;
		}
		else {
			cout << "Ҫ�޸ĵ��˻������ڣ�����������" << endl;
			system("pause");
			continue;
		}
		mysql_free_result(res);
#pragma endregion

#pragma region ѡ��Ҫ�޸ĵ���Ϣ��
		vector<string> hintFields = { "����", "�û�Ȩ��"};
		vector<string> tableFields = { "user_pwd", "authority"};
		int targetField; // �����û�ѡ����
		string strInfo; // �����û�Ҫ�޸ĵ���Ϣ
		cout << "1.����\t2.�û�Ȩ�� " << endl;
		while (true) { // ��ȡ������û�ѡ��
			cout << "������Ҫ�޸ĵ���Ϣ���ţ�";
			cin.sync();
			char temp;
			cin >> temp;
			if (temp == '1' || temp == '2') {
				targetField = temp - '0';
				break;
			}
			else {
				cout << "����ѡ������������ѡ��" << endl;
				system("pause");
				continue;
			}
		}
#pragma endregion

#pragma region �����޸ĺ����Ϣ�������޸�
		cout << "�������µ�" << hintFields[targetField - 1] << ":";
		cin >> strInfo;
		string alterSQL = "update usr_info set " + tableFields[targetField - 1] + "=\"" + strInfo + "\" where user_name = \"" + targetName + "\"";
		if (mysql_query(&mysql, alterSQL.c_str())) {
			cout << "�޸�ʧ��" << endl;
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			system("pause");
			continue;
		}
		// �����޸Ľ��
		if (mysql_affected_rows(&mysql)) {
			cout << "�޸ĳɹ�" << endl;
			system("pause");
			continue;
		}
		else {
			cout << "�޸�ʧ��" << endl;
			system("pause");
			continue;
		}
#pragma endregion
	}
}

/// <summary>
/// ͨ��������id����Ա��
/// </summary>
void UserManage::findUsrInfo() {
	while (true) {
#pragma region ��ӡ���沢��ȡ����
		system("cls");
		string input;
		cout << "�������û��������˺ţ�����q�˳�����";
		cin >> input;
		if (input == "q") {
			break;
		}
#pragma endregion

#pragma region ����������û�������
		string querySql = "select * from usr_info where user_name = \"" + input + "\"";
		if (mysql_query(&mysql, querySql.c_str())) {
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			system("pause");
		}
		res = mysql_store_result(&mysql);
		if (mysql_num_rows(res) == 0) {
			cout << "�û���Ϊ" << input << "���˺Ų�����" << endl;
			system("pause");
		}
		else {
			// ��ӡ��ѯ������Ϣ
			printTableHead();
			while (row = mysql_fetch_row(res)) {
				for (int i = 0; i < usrFields.size(); i++) {
					if (row[i]) {
						cout << setw(20) << left << row[i];
					}
					else {
						cout << setw(20) << left << "���գ�";
					}
				}
				cout << endl;
			}
			system("pause");
		} // if-else
#pragma endregion
	}

	mysql_free_result(res); // �ͷŽ����
}

/// <summary>
/// ����ΪԱ���������
/// </summary>
void UserManage::sortUsr() {
	// ֱ���Ƚ�id��ɾ���ٴ������Ϳ�����������
	mysql_query(&mysql, "ALTER TABLE usr_info DROP id");
	mysql_query(&mysql, "ALTER TABLE usr_info ADD id INT PRIMARY KEY AUTO_INCREMENT first");
	cout << "��������ɹ�" << endl;
	system("pause");
}

/// <summary>
/// ����û��˺ű�
/// </summary>
void UserManage::clearUsr() {
	char confirm = 'n';
	cout << "�Ƿ�ȷ��������ݿ⣨y/n����";
	cin >> confirm;
	if (confirm == 'y' || confirm == 'Y') {
		if (mysql_query(&mysql, "delete from usr_info")) {
			cout << "���ʧ��" << endl;
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			system("pause");
		}
		else {
			cout << "��ճɹ�" << endl;
			system("pause");
		}
	}
}

void UserManage::mainUser() {
	while (true) {
#pragma region ��ӡ���棬��ȡҪִ�еĲ�����
		system("cls");
		printMain();
		cout << "��������Ҫʹ�õĹ��ܱ�ţ�";
		int input;
		if(!(cin >> input)){ // ���벢�������
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "������������������" << endl;
			cin.get();
			continue;
		}
#pragma endregion
#pragma region ���ݲ�����ִ�ж�Ӧ����
		switch (input) {
		case Optcode::QUIT: // �˳�
			cout << "�˳��ɹ�" << endl;
			system("pause");
			return;
			break;
		case Optcode::ADD: // ���Ա��
			addUsrInfo();
			break;
		case Optcode::SHOW: // ��ʾ����Ա����Ϣ
			showUsrInfo();
			system("pause");
			break;
		case Optcode::DEL: // ɾ����ְԱ��
			deleteUsrInfo();
			break;
		case Optcode::FIND: // ����Ա��
			findUsrInfo();
			break;
		case Optcode::SORT: // ��������
			sortUsr();
			break;
		case Optcode::CLEAR: // ���������Ϣ
			clearUsr();
			break;
		case Optcode::ALTER: // �޸�Ա����Ϣ
			alterUsrInfo();
			break;
		default:
			cout << "ѡ������������ѡ��" << endl;
			system("pause");
			break;
		} // switch-case
#pragma endregion
	}
}

UserManage::UserManage() {
#pragma region ��¼���ݿ�
	if (!mysql_init(&mysql)) {
		cout << "���ݿ��ʼ��ʧ�ܣ�����ϵ����Ա��" << endl;
		exit(-1);
	}
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "abc123", "manage_system_db", 3306, NULL, 0)) {
		cout << "���ݿ�����ʧ�ܣ�����ϵ����Ա��" << endl;
		cout << "error_msg:" << mysql_error(&mysql) << endl;
		exit(-1);
	}
#pragma endregion

#pragma region ��ʼ��usr_info�ı�ͷ��Ϣ
	if (mysql_query(&mysql, "select * from usr_info where id = 0")) {
		cout << "error_msg:" << mysql_error(&mysql) << endl;
	}
	res = mysql_store_result(&mysql);
	fieldNums = mysql_num_fields(res);
	usrFields.reserve(fieldNums);
	fields = mysql_fetch_fields(res);
	for (int i = 0; i < fieldNums; i++) {
		usrFields.push_back(fields[i].name);
	}
	mysql_free_result(res);
#pragma endregion
}

UserManage::~UserManage() {
	mysql_close(&mysql);
}