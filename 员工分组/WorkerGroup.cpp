#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

#define Worker_Num 10
enum {
	CEHUA,
	MEISHU,
	YANFA
};
class Worker {
public:
	string m_Name;//姓名
	int m_Salary;//工资
};
void CreateWorker(vector<Worker>& v) {
	string nameSeed = "ABCDEFGHIJ";
	for (int i = 0; i < Worker_Num; i++) {
		Worker worker;
		worker.m_Name = "员工";
		worker.m_Name += nameSeed.at(i);
		worker.m_Salary = rand() % 10000 + 10000;
		//将员工放入vector容器
		v.push_back(worker);
	}
}
void setGroup(vector<Worker>& v, multimap<int, Worker>& m) {
	//遍历员工随机分组
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		int depId = rand() % 3;
		m.insert(make_pair(depId, *it));
	}
}
void showWokerBydepId(int elem, multimap<int, Worker>& m) {
	multimap<int, Worker>::iterator pos = m.find(elem);
	int count = m.count(elem);
	int index = 0;
	for (; pos != m.end() && index < count; pos++, index++) {
		cout << "姓名： " << pos->second.m_Name << " 工资：" << pos->second.m_Salary << endl;
	}
}
void showWorkerByGroup(multimap<int, Worker>& m) {
	cout << "策划部门：" << endl;
	showWokerBydepId(CEHUA, m);
	cout << "------------------------------" << endl;
	cout << "美术部门：" << endl;
	showWokerBydepId(MEISHU, m);
	cout << "------------------------------" << endl;
	cout << "研发部门：" << endl;
	showWokerBydepId(YANFA, m);
}

int main() 
{
	srand((unsigned int)time(NULL));
	//创建员工
	vector<Worker>vWorker;
	CreateWorker(vWorker);
	//员工分组
	multimap<int, Worker> mWorker;
	setGroup(vWorker, mWorker);
	//分组显示
	showWorkerByGroup(mWorker);
	
	system("pause");
	return 0;
}