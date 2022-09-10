#include <iostream>
#include <cstdlib>
#include <string>
#include "BookInfoManagement.h"
#include "StudentInfoManagement.h"
#include"Peroperate.h"
#include"Fileoperate.h"
using namespace std;

Interface face;
Fileoperate operate;
int adminop();
int studentop(string account);

int main()
{

	int identity;										//当前登陆人员身份
	while (true)
	{
		int op = face.MainFace();
		switch (op)
		{
		case 0:
			cout << "正常退出,欢迎下次使用！" << endl;
			return 0;
		case 1:
			cout << "输入账号:" << endl;
			string account, password;
			cin >> account;
			cout << "输入密码:" << endl;
			cin >> password;
			identity = operate.GetIdentity(account, password);

			switch (identity)
			{
			case 0:
				cout << "登陆失败！！请重试...";
				return 1;
			case 1:
				cout << "学生" << account << "登陆成功！！" << endl;
				studentop(account);
				system("cls");
				break;
			case 2:
				cout << "管理员" << account << "登陆成功！！" << endl;
				adminop();
				system("cls");
				break;
			}
			break;
		}
	}
	return 1;
}

int adminop()
{
	while (true) {
		int op = face.AdminMainFace();
		switch (op)
		{
		case 1:
			BookInfoManagement::GetBM().BookInfoManage();
			break;
		case 2:
			StudentInfoManagement::GetSM().StuInfoManage();
			break;
		case 0:
			return 0;
		}
	}
	return 1;
}

int studentop(string account)
{

	while (1)
	{
		Peroperate::GetInstance().PersonalOperate(account);
		break;
	}
	return 1;
}
