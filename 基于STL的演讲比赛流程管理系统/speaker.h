#ifndef _SPEACER_H_
#define _SPEACER_H_
#include <iostream>
#include <string>
using namespace std;

//选手类
class Speaker
{
public:
	//提供接口获取属性
	string& GetName()
	{
		return this->m_Name;
	}

	double* GetScore()
	{
		return this->m_Score;
	}

private:
	string m_Name;//姓名
	double m_Score[2];//分数	最多有两轮得分
};
#endif