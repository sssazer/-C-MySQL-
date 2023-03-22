#include "ManageSystem.h"

/// <summary>
/// ���캯������������MySQL������
/// </summary>
ManageSystem::ManageSystem() {
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
}

ManageSystem::~ManageSystem() {
	mysql_close(&mysql);
}

/// <summary>
/// ��ӡ��½����
/// </summary>
void ManageSystem::printLogin() {
	cout << "**************************" << endl;
	cout << "*********���¼***********" << endl;
	cout << "�������û�����";
	cin >> user_name;
	cout << "����������";
	cin >> user_pwd;
}

/// <summary>
/// ʵ�ֵ�¼����
/// </summary>
/// <returns>��¼�û�Ϊ��ͨ�û�ʱ����0��Ϊroot�û�ʱ����1</returns>
void ManageSystem::loginPage() {
	while (true) {
#pragma region ��ӡ���棬��ȡ�û������벢�γ�SQL���
		system("cls");
		printLogin();
		string querySql = "select user_pwd, authority from usr_info where user_name = \"" + user_name + "\"";
#pragma endregion

#pragma region ִ��SQL����ȡ�����
		if (mysql_query(&mysql, querySql.c_str())) {
			cout << "error_msg:" << mysql_error(&mysql) << endl;
			exit(-1);
		}
		res = mysql_store_result(&mysql);
#pragma endregion

#pragma region �������ݿ��������ж��Ƿ��¼�ɹ�
		if (row = mysql_fetch_row(res)) {
			if (user_pwd == row[0]) {
				isRoot = row[1][0] - '0';
				break;
			}
			else {
				cout << "�������" << endl;
				system("pause");
				continue;
			}
		}
		else {
			cout << "�û��������ڣ�����������" << endl;
			system("pause");
		}
#pragma endregion
	} // while_true
}// login_page


void ManageSystem::mainPage() {
	loginPage(); // ִ�е�¼����

	if(isRoot){
		while (true) {
			system("cls");
			cout << "0���˳�ϵͳ" << endl;
			cout << "1���û�����ϵͳ" << endl;
			cout << "2��Ա������ϵͳ" << endl;
			cout << "��ѡ��Ҫ�����ϵͳ��0/1/2����";

			int sysChoice;
			if (! (cin >> sysChoice)) { // ��ȡ��������룬�������Ƿ���cin����Ϊfalse�����������״̬
				cin.clear(); // ��cin�Ĵ���״̬���
				cin.ignore(INT_MAX, '\n'); // ������뻺����
				cout << "������������������" << endl;
				cin.get();
				continue;
			}
			
			if (sysChoice == 0) {
				cout << "�˳��ɹ�" << endl;
				system("pause");
				exit(0);
			}
			else if(sysChoice == 1){
				um.mainUser();
			}
			else if(sysChoice == 2){
				em.mainEmpRoot();
			}
			else {
				cout << "�����������������" << endl;
				system("pause");
			}
		}
	}
	else {
		em.mainEmpOrdinary();
	}
}