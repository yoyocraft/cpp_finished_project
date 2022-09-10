#include "SpeechManager.h"

int main()
{
	//实例化管理类对象
	SpeechManager sm;
	srand((unsigned int)time(NULL));//随机数种子

	/*sm.Create_Speaker();
	sm.Speech_Draw();*/
	while (true)
	{
		sm.Show_Menu();

		cout << "请输入要实现的功能（0~3）：" << endl;
		int choice;//用于保存用户的选择
		cin >> choice;

		switch (choice)
		{
		case 0:	//0、退出比赛程序
			sm.Exit_System();
			break;
		case 1:	//1、开始演讲比赛
			sm.Start_Contest();
			break;
		case 2:	//2、查看往届记录
			sm.Show_Record();
			break;
		case 3:	//3、清空比赛记录
			sm.Clear_Record();
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}

	}


	system("pause");
	return 0;
}