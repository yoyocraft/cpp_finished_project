#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

int main()
{
	WorkerManager wm;//实例化管理者对象
	int choice = 0;//用户选择
	while (true)
	{
		wm.Show_Menu();

		cout << "请输入功能编号（0~7）：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:	//退出管理系统
			wm.ExitSystem();
			break;
		case 1:	//增加职工信息
			wm.Add_Emp();
			break;
		case 2:	//显示职工信息
			wm.Show_Emp();
			break;
		case 3:	//删除职工信息
			wm.Del_Emp();
			break;
		case 4:	//修改职工信息
			wm.Mod_Emp();
			break;
		case 5:	//查找职工信息
			wm.Find_Emp();
			break;
		case 6:	//按照编号排序
			wm.Sort_Emp();
			break;
		case 7:	//清空所有文档
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}