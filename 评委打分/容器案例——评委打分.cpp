#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<deque>
#include<ctime>
#include <algorithm>
class Person {
public:
	Person(string name) {
		this->m_Name = name;
	}
	string m_Name;
	int m_Score;
};
void CreatPerson(vector<Person>& v) {
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++) {
		Person p("选手");
		p.m_Name += nameSeed.at(i);
		p.m_Score = 0;//初始化为0
		v.push_back(p);
	}
}
void setScore(vector<Person>& v) {
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		deque<int>d;
		for (int i = 0; i < 10; i++) {
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end());
		//去除最高分和最低分
		d.pop_back();
		d.pop_front();

		//均分
		int sum = 0;
		for (deque<int>::iterator it = d.begin(); it != d.end();it++) {
			sum += (*it);
		}
		int avg = sum / d.size();
		it->m_Score = avg;
	}
}
void showScore(vector<Person>& v) {
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "name:" << it->m_Name << " score:" << it->m_Score << endl;
	}
}
int main()
{
	srand((unsigned)time(NULL));
	//创建五名选手，放到vector容器中
	vector<Person>v;
	CreatPerson(v);
	//给五名选手打分
	setScore(v);
	//展示分数
	showScore(v);

	system("pause");
	return 0;
}