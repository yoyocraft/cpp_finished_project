#include "speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	//初始化比赛
	this->resetContest();

	//初始化比赛轮数
	this->m_Index = 1;

	//初始化记录人数
	this->m_Record.clear();
}

//展示菜单
void SpeechManager::ShowMenu()
{
	cout << "----------------------------------------------" << endl;
	cout << "-----------【演讲比赛流程管理系统】-----------" << endl;
	cout << "--------------0、退出比赛程序-----------------" << endl;
	cout << "--------------1、开始演讲比赛-----------------" << endl;
	cout << "--------------2、查看往届记录-----------------" << endl;
	cout << "--------------3、清空比赛记录-----------------" << endl;
	cout << "----------------------------------------------" << endl;
}

//退出系统
void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
	//清空容器
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//初始化轮数
	this->m_Index = 1;
}

//创建选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed.at(i);

		//创建具体选手
		Speaker sp;
		sp.GetName() = name;
		
		for (int j = 0; j < 2; j++)
		{
			sp.GetScore()[j] = 0;
		}

		//创建选手编号并放入v1容器中
		this->v1.push_back(i + 10001);

		//选手编号和以及对应选手放入map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//开始比赛----比赛流程控制
void SpeechManager::startSpeech()
{
	for (; this->m_Index <= CONTESTNUM; this->m_Index++)
	{
		//1、抽签
		this->speechDraw();
		//2、比赛
		this->speechContest();
		//3、显示晋级结果
		this->showScore();
	}

	//4、保存分数
	this->saveRecord();

	//重置比赛，获取记录
	this->resetContest();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "--------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());	//洗牌算法 打乱选手次序
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::speechContest()
{
	cout << "----------------第 <<" << this->m_Index << " >> 轮比赛正式开始----------------" << endl;
	
	multimap<double, int, greater<double>>groupScore;	//准备临时容器 存放小组成绩
	int num = 0;//用于统计人员个数	6人一组
	
	vector<int>v_Src;//比赛选手容器

	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < JUGLENUM; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;	//分数设为浮点类型
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//降序排序

		d.pop_front();		//去除最高分
		d.pop_back();		//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);		//累加总分

		double avg = sum / (double)d.size();					//平均分
	
		this->m_Speaker[*it].GetScore()[this->m_Index - 1] = avg;		//将均分放入容器

		//将打分数据放入临时小组容器中
		groupScore.insert(make_pair(avg, *it));//key是得分，value是具体选手编号

		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); 
				it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].GetName()
					<< " 成绩：" << this->m_Speaker[it->second].GetScore()[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三名
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
				it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}
			groupScore.clear();			//容器清空，防止造成下一轮比赛重复使用数据
			cout << endl;
		}
	}
	cout << "----------------第 << " << this->m_Index << " >> 轮比赛完毕----------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore()
{
	cout << "----------------第 << " << this->m_Index << " >> 轮晋级选手信息如下：----------------" << endl;
	
	vector<int>v;//临时存储当前轮的下一轮的选手

	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << this->m_Speaker[*it].GetName()
			<< " 得分：" << this->m_Speaker[*it].GetScore()[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->ShowMenu();
}

//保存分数
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);//用输出的方式打开文件---写文件，追加写

	//将每个人的数据写入文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].GetScore()[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;
	//更新标志
	this->FileIsEmpty = false;
	this->FileIsExist = true;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs(FILENAME, ios::in);	//输入流对象，读取文件

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->FileIsEmpty = false;

	ifs.putback(ch);//读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//存放截取的6个字符串

		//对读取的数据进行截取
		int pos = 1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);//从0开始查找" , "
			if (pos == -1)
			{
				break;//找不到 break返回
			}

			string temp = data.substr(start, pos - start);//找到了，进行分割，参数1：起始位置，参数2：截取长度
			v.push_back(temp);
			start = pos + 1;	//更新下一次查找起点
		}
		this->m_Record.insert(make_pair(index, v));		//存放往届记录
		index++;
	}
	ifs.close();
}

//显示往届得分
void SpeechManager::showRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	else if (!this->FileIsExist)
	{
		cout << "文件不存在" << endl;

	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< " 冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1]
				<< " 亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3]
				<< " 季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5]
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//打开方式：ios::truck 如果存在删除文件并重新创建
		ofs.close();

		//初始化容器和属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//加载往届记录
		this->loadRecord();

		cout << "清空成功" << endl;
		this->FileIsEmpty = true;	//更新文件为空的标志
	}
	system("pause");
	system("cls");
}

//重置比赛
void SpeechManager::resetContest()
{
	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
}

//析构函数
SpeechManager::~SpeechManager()
{

}