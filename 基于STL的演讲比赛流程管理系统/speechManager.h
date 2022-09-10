#ifndef _SPEECHMANAGRE_H_
#define _SPEECHMANAGER_H_
#include <iostream>
//容器类头文件
#include <map>
#include <vector>
#include <string>
#include <deque>
//算法类头文件
#include <algorithm>
#include <functional>
#include <numeric>
//文件操作头文件
#include <fstream>

#include <ctime>
#include "speaker.h"

#define FILENAME "speech.csv"
#define JUGLENUM 10
#define SPEAKERNUM 12
#define CONTESTNUM 2
using namespace std;

//创建演讲比赛管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//展示菜单
	void ShowMenu();

	//退出系统
	void ExitSystem();

	//初始化容器和属性
	void initSpeech();

	//创建选手
	void createSpeaker();

	//开始比赛----比赛流程控制
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存分数
	void saveRecord();

	//读取记录
	void loadRecord();

	//重置比赛
	void resetContest();

	//文件为空的标志
	bool FileIsEmpty;

	//文件是否存在标志
	bool FileIsExist;

	//往届记录
	map<int, vector<string>>m_Record;//key代表第几届，value代表文件中截取的记录内容

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();

	//成员属性
	//第一轮比赛选手 容器 12人
	vector<int>v1;
	//第一轮晋级选手编号容器
	vector<int>v2;
	//前三名
	vector<int>vVictory;
	//存放编号以及对应选手的容器
	map<int, Speaker>m_Speaker;

	//比赛轮数
	int m_Index;

	//析构函数
	~SpeechManager();
};
#endif