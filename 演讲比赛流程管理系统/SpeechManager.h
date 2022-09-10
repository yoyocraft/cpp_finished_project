#pragma once 
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ctime>
#include <fstream>
#include "speaker.h"

#define FILENAME "speech.csv"
#define JUGLE_NUM 10
#define SPEAKER_NUM 12
#define CONTSET_NUM 2
#define FIRST_PROMOTED_NUM 6
#define FINAL_PROMOTED_NUM 3
#define START_NUM 10001
using namespace std;


//创建比赛管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//展示菜单
	void Show_Menu();

	//退出系统
	void Exit_System();

	//初始化容器和属性
	void Init_Speech();

	//创建选手
	void Create_Speaker();

	//比赛函数
	void Start_Contest();

	//抽签
	void Speech_Draw();

	//打印抽签顺序
	void Print_SpeechDraw(vector<int>& v);

	//比赛
	void Speech_Contest();

	//显示比赛结果
	void Show_Score();

	//保存记录
	void Save_Record();

	//读取记录
	void Load_Record();

	//往届记录容器
	map<int, vector<string>>m_Record;

	//显示往届记录
	void Show_Record();

	//重置比赛
	void Reset_Contest();

	//清空记录
	void Clear_Record();

	//文件为空标志
	bool FileIsEmpty;

	//文件存在标志
	bool FileIsExist;

	//成员属性
	//第一轮选手编号容器
	vector<int>v1;
	//第二轮选手编号容器
	vector<int>v2;
	//前三名选手容器
	vector<int>vVictory;
	//存放编号和选手的容器
	map<int, Speaker>m_Speaker;
	//比赛轮数
	int m_Index;

	//析构函数
	~SpeechManager();
};