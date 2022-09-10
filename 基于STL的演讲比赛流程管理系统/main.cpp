#include <iostream>
#include"speechManager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));	//随机数种子
	//实例化管理类对象
	SpeechManager sm;

	int choice;
	while (true)
	{
		sm.ShowMenu();

		cout << "请输入要实现的功能（0~3）：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:		//退出比赛程序
			sm.ExitSystem();
			break;
		case 1:		//开始演讲比赛
			sm.startSpeech();
			break;
		case 2:		//查看往届记录
			sm.showRecord();
			break;
		case 3:		//清空比赛记录
			sm.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}