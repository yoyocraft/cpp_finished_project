#include "WorkerManager.h"

//构造函数
WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileisExist = false;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileisEmpty = true;
		ifs.close();
		return;
	}
	//文件存在记录数据
	int num = this->get_EmpNum();
	cout << "当前职工人数为：" << num << endl;
	this->m_EmpNum = num;
	//开辟空间，将文件的数据存到数组中
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();//初始化职工
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "-----------------------------------------" << endl;
	cout << "------------【职工管理系统】-------------" << endl;
	cout << "-------------0.退出管理系统--------------" << endl;
	cout << "-------------1.增加职工信息--------------" << endl;
	cout << "-------------2.显示职工信息--------------" << endl;
	cout << "-------------3.删除职工信息--------------" << endl;
	cout << "-------------4.修改职工信息--------------" << endl;
	cout << "-------------5.查找职工信息--------------" << endl;
	cout << "-------------6.按照编号排序--------------" << endl;
	cout << "-------------7.清空所有文档--------------" << endl;
	cout << "-----------------------------------------" << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算添加新空间人数
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;
			//判断职工编号是否存在
			int ret = this->isExist(id);
			if (ret == -1)	//职工编号合法
			{
				cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
				cin >> name;
				cout << "请选择该职工岗位：" << endl;
				cout << "1、普通员工" << endl
					<< "2、经理" << endl
					<< "3、老板" << endl;
				cin >> dSelect;

				Worker* worker = NULL;
				switch (dSelect)
				{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}
				//将创建的职工指针保存到数组中
				newSpace[this->m_EmpNum + i] = worker;
			}
			else
			{
				cout << "当前输入的编号存在，请重新输入！" << endl;
				i--;
				continue;
			}
		}

		delete[]this->m_EmpArray;		//释放原有的空间
		this->m_EmpArray = newSpace;	//更改新空间的指向
		this->m_EmpNum = newSize;		//更新新的职工人数
		this->m_FileisEmpty = false;	//更新职工不为空标志

		this->save();//同步保存到文件中
		this->m_FileisExist = true;//更新文件是否存在标志
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id, num = 0;
	string name;
	int dId;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

//初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)		//Employee
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//Manager
		{
			worker = new Manager(id, name, dId);
		}
		else   //Boss
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index++] = worker;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileisEmpty)
	{
		cout << "记录为空" << endl;
	}
	else if (!this->m_FileisExist)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();//利用多态调用接口
		}
	}
	system("pause");
	system("cls");
}

//判断员工是否存在，如果存在返回职工所在数组的位置，不存在返回-1
int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileisEmpty)
	{
		cout << "记录为空" << endl;
	}
	else if(!this->m_FileisExist)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);
		if (index != -1)//职工存在
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];	//数据前移
			}
			this->m_EmpNum--;//更新人员个数
			this->save();//同步到文件中
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileisEmpty)
	{
		cout << "记录为空" << endl;
	}
	else if (!this->m_FileisExist)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int ret = this->isExist(id);
		if (ret != -1)
		{
			//查找员工
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到" << id << "号职工,请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请输入新岗位：" << endl;
			cout << "1、普通员工" << endl
				<< "2、经理" << endl
				<< "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId,newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			//更新数据到数组
			this->m_EmpArray[ret] = worker;
			this->save();
			cout << "修改成功！" << endl;		
		}
		else
		{
			cout << "修改失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileisEmpty)
	{
		cout << "记录为空" << endl;
	}
	else if (!this->m_FileisExist)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入查找方式(1 or 2):" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找职工编号：" << endl;
			cin >> id;

			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败！查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找职工姓名：" << endl;
			cin >> name;
			bool flag = false;//查找标志，默认未找到

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功！该职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败！查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//职工排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileisEmpty)
	{
		cout << "记录为空" << endl;
		system("pause");
		system("cls");
	}
	else if (!this->m_FileisExist)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入排序方式(1 or 2):" << endl;
		cout << "1、按照职工号升序" << endl;
		cout << "2、按照职工号降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
			}
			if (MinOrMax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
				this->m_EmpArray[MinOrMax] = temp;
			}
		}
	}
	cout << "排序成功，排序后结果" << endl;
	this->save();
	this->Show_Emp();
}

//清空数据
void WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	
	int select = 0; 
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后再重新创建
		ofs.close();
		
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];//释放堆区的每一个职工
					this->m_EmpArray[i] = NULL;
				}
			}
			//删除堆区的数组指针
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileisEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];//释放堆区的每一个职工对象
				this->m_EmpArray[i] = NULL;
			}
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}