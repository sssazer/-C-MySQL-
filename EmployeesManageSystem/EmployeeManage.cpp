#include "EmployeeManage.h"

void EmployeeManage::printTableHead() {

	for (int i = 0; i < empFields.size(); i++) {
		cout << setw(20) << left << empFields[i];
	}
	cout << endl;
}

/// <summary>
/// ��ӡ�����ܽ���
/// </summary>
/// <param name="isRoot"></param>
void EmployeeManage::printMain(bool isRoot) {
	if (isRoot) {
		cout << "**************************" << endl;
		cout << "***��ӭʹ��ְ������ϵͳ***" << endl;
		cout << "******0-�˳�����ϵͳ******" << endl;
		cout << "******1-��ʾְ����Ϣ******" << endl;
		cout << "******2-����ְ����Ϣ******" << endl;
		cout << "******3-���ձ������******" << endl;
		cout << "******4-����ְ����Ϣ******" << endl;
		cout << "******5-ɾ����ְְ��******" << endl;
		cout << "******6-�޸�ְ����Ϣ******" << endl;
		cout << "******7-�����������******" << endl;
		cout << "**************************" << endl;
		cout << "**************************" << endl;
	}
	else {
		cout << "**************************" << endl;
		cout << "***��ӭʹ��ְ������ϵͳ***" << endl;
		cout << "******0-�˳�����ϵͳ******" << endl;
		cout << "******1-��ʾְ����Ϣ******" << endl;
		cout << "******2-����ְ����Ϣ******" << endl;
		cout << "******3-���ձ������******" << endl;
		cout << "**************************" << endl;
		cout << "**************************" << endl;
	}
}

#pragma region ְ������ϵͳ����
/// <summary>
/// ���Ա����Ϣ
/// </summary>
void EmployeeManage::addEmpInfo() {

	char* infoChars = new char[100];
	cin.get();
	while (true) { // ������Ϣ����ʱѭ������

#pragma region ��ӡ����Ͷ�������
		system("cls");
		cout << "�밴���¸�ʽ����Ա����Ϣ���м��ÿո�ָ�����ʱû�е���Ϣ��null������q�˳�" << endl;
		cout << "Ա������ �绰���� ְλ ���� ������ID" << endl;

		// ���������ݶ���		
		cin.getline(infoChars, 100);
		string infoStr = infoChars;
		infoChars += '\0';
		if (infoStr == "q") {
			break;
		}
#pragma endregion	

#pragma region �����������ݲ��γ�SQL���
		string querySQL = "insert into emp_info (name, phone_number, job_id, salary, manager_id) values (";
		int i = 0;
		int j;
		// �Կո�Ϊ�ָ����ָ�����ĸ�����Ϣ����������SQL�����
		while ((j = infoStr.find(" ", i)) != -1) {
			string subInfo = infoStr.substr(i, j - i);
			i = j + 1;
			if (subInfo == "null" || subInfo == "NULL") {
				querySQL = querySQL + subInfo + ",";
			}
			else {
				querySQL = querySQL + "\"" + subInfo + "\",";
			}
		}
		if (i < infoStr.size()) {
			string subInfo = infoStr.substr(i, infoStr.size() - i);
			if (subInfo == "null" || subInfo == "NULL") {
				querySQL = querySQL + subInfo + ",";
			}
			else {
				querySQL = querySQL + "\"" + subInfo + "\",";
			}
		}
		querySQL.replace(querySQL.size() - 1, 1, ")");
#pragma endregion

#pragma region ִ��SQL��䣬����Ա����Ϣ
		// ִ��SQL���
		if (mysql_query(&mysql, querySQL.c_str())) {
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			cout << "������Ϣ��������������" << endl;
			system("pause");
			continue;
		}
		cout << "��ӳɹ�" << endl;
		system("pause");
		break;
	} // while_true
#pragma endregion

	delete[] infoChars;
}

/// <summary>
/// ��ʾ����Ա����Ϣ
/// </summary>
void EmployeeManage::showEmpInfo() {

#pragma region ��ѯ�������ݲ���������
	string querySql = "select * from emp_info";
	mysql_query(&mysql, querySql.c_str());
	res = mysql_store_result(&mysql);
#pragma endregion

#pragma region ��ӡ��ͷ
	printTableHead();
#pragma endregion

#pragma region ��ӡ������Ϣ
	while (row = mysql_fetch_row(res)) {
		for (int i = 0; i < empFields.size(); i++) {
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
void EmployeeManage::deleteEmpInfo() {
	while (true) {
#pragma region ��ӡ��ʾ��Ϣ����ȡ����
		system("cls");

		cout << "������Ҫɾ����Ա��ID������(����q�˳�):";
		string strInfo;
		cin >> strInfo;
		if (strInfo == "q") {
			break;
		}
#pragma endregion

#pragma region ����ID
		if (strInfo[0] >= '0' && strInfo[0] <= '9') {
			string querySQL = "delete from emp_info where emp_id = \"" + strInfo + "\"";
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
				cout << "ɾ��ʧ�ܣ�δ�ҵ�IDΪ" << strInfo << "��Ա��" << endl;
				system("pause");
			}
		}
#pragma endregion

#pragma region ��������
		else {
			string querySQL = "delete from emp_info where name = \"" + strInfo + "\"";
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
				cout << "ɾ��ʧ�ܣ�δ�ҵ�����Ϊ" << strInfo << "��Ա��" << endl;
				system("pause");
			}
		}
#pragma endregion
	} // while-true
}


void EmployeeManage::alterEmpInfo() {
	while (true) {
#pragma region ����Ҫ�޸ĵ�Ա����Ϣ
		system("cls");
		cout << "������Ҫ�޸ĵ�Ա��ID����q�˳�����";
		string targetId;
		cin >> targetId;
		if (targetId == "q") {
			break;
		}
#pragma endregion

#pragma region �ж�Ա���Ƿ����
		string querySQL = "select * from emp_info where emp_id = \"" + targetId + "\"";
		if (mysql_query(&mysql, querySQL.c_str())) {
			cout << "�����ʽ��������������" << endl;
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			continue;
		}
		res = mysql_store_result(&mysql);
		if (row = mysql_fetch_row(res)) { // Ա�����ڵĻ��ʹ�ӡԱ����Ϣ
			printTableHead();
			for (int i = 0; i < empFields.size(); i++) {
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
			cout << "Ҫ�޸ĵ�Ա�������ڣ�����������" << endl;
			system("pause");
			continue;
		}
		mysql_free_result(res);
#pragma endregion

#pragma region ѡ��Ҫ�޸ĵ���Ϣ��
		vector<string> hintFields = { "����","�绰","��λ","н��","������ID" };
		vector<string> tableFields = { "name", "phone_number", "job_id", "salary", "manager_id" };
		int targetField; // �����û�ѡ����
		string strInfo; // �����û�Ҫ�޸ĵ���Ϣ
		cout << "1.����  2.�绰  3.��λ  4.н��  5.������ID" << endl;
		while (true) { // ��ȡ������û�ѡ��
			cout << "������Ҫ�޸ĵ���Ϣ���ţ�";
			if (cin >> targetField) {
				break;
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "����ѡ����������������" << endl;
			system("pause");
			continue;
		}
#pragma endregion

#pragma region �����޸ĺ����Ϣ�������޸�
		cout << "�������µ�" << hintFields[targetField - 1] << ":";
		cin >> strInfo;
		string alterSQL = "update emp_info set " + tableFields[targetField - 1] + "=\"" + strInfo + "\" where emp_id = \"" + targetId + "\"";
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
void EmployeeManage::findEmpInfo() {
	while (true) {
#pragma region ��ӡ���沢��ȡ����
		system("cls");
		string input;
		cout << "������id�����ֲ�ѯԱ��������q�˳�����";
		cin >> input;
		if (input == "q") {
			break;
		}
#pragma endregion
		// �ж��������id��������
#pragma region ����ID
		if (input[0] >= '0' && input[1] <= '9') {
			string querySql = "select * from emp_info where emp_id = \"" + input + "\"";
			if (mysql_query(&mysql, querySql.c_str())) {
				cout << "error_msg:" << mysql_error(&mysql) << endl;
				system("pause");
			}
			res = mysql_store_result(&mysql);
			if (mysql_num_rows(res) == 0) {
				cout << "idΪ" << input << "��Ա��������" << endl;
				system("pause");
			}
			else {
				// ��ӡ��ѯ������Ϣ
				printTableHead(); // ��ӡ��ͷ
				while (row = mysql_fetch_row(res)) {
					for (int i = 0; i < empFields.size(); i++) {
						if (row[i]) {
							cout << setw(20) << left << row[i];
						}
						else {
							cout << setw(20) << left << "���գ�";
						}
					}
				}
				system("pause");
			} // if-else
		}
#pragma endregion

#pragma region ��������
		else {
			string querySql = "select * from emp_info where name = \"" + input + "\"";
			if (mysql_query(&mysql, querySql.c_str())) {
				cout << "error_msg:" << mysql_error(&mysql) << endl;
				system("pause");
			}
			res = mysql_store_result(&mysql);
			if (mysql_num_rows(res) == 0) {
				cout << "nameΪ" << input << "��Ա��������" << endl;
				system("pause");
			}
			else {
				// ��ӡ��ѯ������Ϣ
				printTableHead();
				while (row = mysql_fetch_row(res)) {
					for (int i = 0; i < empFields.size(); i++) {
						if (row[i]) {
							cout << setw(20) << left << row[i];
						}
						else {
							cout << setw(20) << left << "���գ�";
						}
					}
				}
				system("pause");
			} // if-else
		}
#pragma endregion
	}

	mysql_free_result(res); // �ͷŽ����
}

/// <summary>
/// ����ΪԱ���������
/// </summary>
void EmployeeManage::sortById() {
	// ֱ���Ƚ�id��ɾ���ٴ������Ϳ�����������
	mysql_query(&mysql, "ALTER TABLE emp_info DROP emp_id");
	mysql_query(&mysql, "ALTER TABLE emp_info ADD emp_id INT PRIMARY KEY AUTO_INCREMENT first");
	cout << "��������ɹ�" << endl;
	system("pause");
}

/// <summary>
/// ���Ա����
/// </summary>
void EmployeeManage::clearAll() {
	char confirm = 'n';
	cout << "�Ƿ�ȷ��������ݿ⣨y/n����";
	cin >> confirm;
	if (confirm == 'y' || confirm == 'Y') {
		if (mysql_query(&mysql, "delete from emp_info")) {
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

#pragma endregion

void EmployeeManage::mainEmpRoot() {
		while (true) {
#pragma region ��ӡ���棬��ȡҪִ�еĲ�����
			system("cls");
			printMain(1);
			cout << "��������Ҫʹ�õĹ��ܱ�ţ�";
			if (!(cin >> optIndex)) { // ���벢����������
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "������������������" << endl;
				system("pause");
				continue;
			}
#pragma endregion
#pragma region ���ݲ�����ִ�ж�Ӧ����
			switch (optIndex) {
			case Optcode::QUIT: // �˳�
				cout << "�˳��ɹ�" << endl;
				system("pause");
				return;
				break;
			case Optcode::ADD: // ���Ա��
				addEmpInfo();
				break;
			case Optcode::SHOW: // ��ʾ����Ա����Ϣ
				showEmpInfo();
				system("pause");
				break;
			case Optcode::DEL: // ɾ����ְԱ��
				deleteEmpInfo();
				break;
			case Optcode::FIND: // ����Ա��
				findEmpInfo();
				break;
			case Optcode::SORT: // ��������
				sortById();
				break;
			case Optcode::CLEAR: // ���������Ϣ
				clearAll();
				break;
			case Optcode::ALTER: // �޸�Ա����Ϣ
				alterEmpInfo();
				break;
			default:
				cout << "ѡ������������ѡ��" << endl;
				system("pause");
				break;
			} // switch-case
#pragma endregion
		}
}

void EmployeeManage::mainEmpOrdinary() {
	while (true) {
#pragma region ��ӡ���棬��ȡ������
		system("cls");
		printMain(0);
		cout << "��������Ҫʹ�õĹ��ܱ�ţ�";
		if (!(cin >> optIndex)) { // ���벢����������
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "������������������" << endl;
			system("pause");
			continue;
		}
#pragma endregion
#pragma region ���ݲ�����ִ�ж�Ӧ����
		switch (optIndex) {
		case Optcode::QUIT: // �˳�
			cout << "�˳��ɹ�" << endl;
			system("pause");
			return;
			break;
		case Optcode::SHOW: // ��ʾ����Ա����Ϣ
			showEmpInfo();
			system("pause");
			break;
		case Optcode::FIND: // ����Ա����Ϣ
			findEmpInfo();
			break;
		case Optcode::SORT: // ����
			sortById();
			break;
		default:
			cout << "ѡ������������ѡ��" << endl;
			system("pause");
			break;
		} // switch-case
#pragma endregion
	}
}

EmployeeManage::EmployeeManage() {
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

#pragma region ��ʼ��emp_info�ı�ͷ��Ϣ
	if (mysql_query(&mysql, "select * from emp_info where emp_id = 0")) {
		cout << "error_msg:" << mysql_error(&mysql) << endl;
	}
	res = mysql_store_result(&mysql);
	fieldNums = mysql_num_fields(res);
	empFields.reserve(fieldNums);
	fields = mysql_fetch_fields(res);
	for (int i = 0; i < fieldNums; i++) {
		empFields.push_back(fields[i].name);
	}
	mysql_free_result(res);
#pragma endregion
}

EmployeeManage::~EmployeeManage() {
	mysql_close(&mysql);
}