#include <iostream>
#include <string>
using namespace std;

class Speaker
{
public:
	//提供获取选手属性的函数
	string& GetName() { return this->m_Name; }
	double* GetScore() { return this->m_Score; }

private:
	string m_Name;	//姓名
	double m_Score[2];//比赛分数（两轮）
};