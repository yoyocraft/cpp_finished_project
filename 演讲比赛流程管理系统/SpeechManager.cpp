#include "SpeechManager.h"


//构造函数
SpeechManager::SpeechManager()
{
	//初始化记录人数
	this->m_Record.clear();

	//重置比赛
	this->Reset_Contest();

	//初始化比赛轮数
	this->m_Index = 1;
}


//展示菜单
void SpeechManager::Show_Menu()
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
void SpeechManager::Exit_System()
{
	cout << "欢迎下次使用本系统" << endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void SpeechManager::Init_Speech()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//比赛轮数重置
	this->m_Index = 1;
}

//创建选手
void SpeechManager::Create_Speaker()
{
	//string NameSeed = "ABCDEFGHIJKL";//创建姓名种子
	string NameSeed;
	char ch = 'A';
	for (int i = 0; i < SPEAKER_NUM; i++,ch++)
	{
		NameSeed += ch;
	}
	for (int i = 0; i < NameSeed.size(); i++)
	{
		//实例化选手
		Speaker sp;
		sp.GetName() = "选手";
		sp.GetName() += NameSeed.at(i);

		for (int j = 0; j < CONTSET_NUM; j++)
		{
			sp.GetScore()[j] = 0;
		}

		//将选手编号存入第一轮比赛容器中
		this->v1.push_back(i + START_NUM);

		//将选手存入选手容器中
		this->m_Speaker.insert(make_pair(i + START_NUM, sp));
	}
}

//比赛函数
void SpeechManager::Start_Contest()
{
	for (; this->m_Index <= CONTSET_NUM; this->m_Index++)
	{
		//抽签
		this->Speech_Draw();
		//开始比赛
		this->Speech_Contest();
		//显示比赛结果
		this->Show_Score();
	}

	//保存记录
	this->Save_Record();

	//重置比赛
	this->Reset_Contest();

	cout << "---------------本届比赛完毕！---------------" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::Speech_Draw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		this->Print_SpeechDraw(v1);
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		this->Print_SpeechDraw(v2);
	}
	cout << "------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//打印抽签顺序
void SpeechManager::Print_SpeechDraw(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//比赛
void SpeechManager::Speech_Contest()
{
	cout << "----------------第 <<" << this->m_Index << " >> 轮比赛正式开始----------------" << endl;
	multimap<int, double, greater<double>>GroupScore;//临时容器，存放选手得分，key是选手编号，value是选手得分
	int num = 0;	//用于分组，6人一组

	vector<int>v_Src;//临时选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历选手开始比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < JUGLE_NUM; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//转换成浮点型分数
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//对分数降序排序

		d.pop_front();//去除最高分
		d.pop_back();//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//获取总分
		double avg = sum / d.size();//获取均分
		
		//将均分存入选手容器
		this->m_Speaker[*it].GetScore()[this->m_Index - 1] = avg;

		//将打分数据存入临时选手容器中
		GroupScore.insert(make_pair(*it, avg));

		//每6人取出前三名
		if (!(num % FIRST_PROMOTED_NUM))
		{
			cout << "第" << num / FIRST_PROMOTED_NUM << "小组比赛名次：" << endl;
			for (multimap<int, double>::iterator it = GroupScore.begin();
				it != GroupScore.end(); it++)
			{
				cout << "选手编号：" << it->first << "  姓名：" << this->m_Speaker[it->first].GetName()
					<< "  得分：" << this->m_Speaker[it->first].GetScore()[this->m_Index - 1] << endl;
			}
			int count = 0;
			for (multimap<int, double>::iterator it = GroupScore.begin();
				it != GroupScore.end() && count < FINAL_PROMOTED_NUM; it++, count++)
			{
				//存到下一环节的选手容器中
				if (this->m_Index == 1)
				{
					v2.push_back(it->first);
				}
				else
				{
					vVictory.push_back(it->first);
				}
			}
			GroupScore.clear();//清空临时容器，防止下一轮造成数据重复
			cout << endl;
		}
	}
	cout << "----------------第 << " << this->m_Index << " >> 轮比赛完毕----------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::Show_Score()
{
	cout << "----------------第 << " << this->m_Index << " >> 轮晋级选手信息如下：----------------" << endl;
	vector<int>v;//临时存储晋级选手

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
		cout << "选手编号：" << *it << "  姓名：" << this->m_Speaker[*it].GetName()
			<< "  得分：" << this->m_Speaker[*it].GetScore()[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");

	this->Show_Menu();
}

//保存记录
void SpeechManager::Save_Record()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);//追加的方式打开文件
	//将记录写入文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].GetScore()[CONTSET_NUM - 1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录已成功保存至当前目录下的文件\"" << FILENAME << "\"中" << endl;
	//更新标志
	this->FileIsEmpty = false;
	this->FileIsExist = true;
}

//读取记录
void SpeechManager::Load_Record()
{
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		this->FileIsExist = false;//文件不存在
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if(ifs.eof())
	{
		this->FileIsEmpty = true;//文件为空
		ifs.close();
		return;
	}

	this->FileIsEmpty = false;//文件不为空
	ifs.putback(ch);//将读到的字符放回文件

	string data;
	int index = 0;

	while (ifs >> data)
	{
		vector<string>v;//用于存放截取的字符串
		//对读到的字符串进行截取
		int pos = 1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);//从0开始查找逗号","
			if (pos == -1)//未找到
			{
				break;
			}
			string temp = data.substr(start, pos - start);//获取截取的字符
			v.push_back(temp);//存入容器
			start = pos + 1;//更新查找的位置
		}
		this->m_Record.insert(make_pair(index, v));//key表示第几届，value表示前三名记录
		index++;
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::Show_Record()
{
	if (this->FileIsEmpty)
	{
		cout << "文件为空！" << endl;
	}
	else if (!this->FileIsExist)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		for (int i = 0; i < m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< "  冠军编号：" << this->m_Record[i][0] << "  得分：" << this->m_Record[i][1]
				<< "  亚军编号：" << this->m_Record[i][2] << "  得分：" << this->m_Record[i][3]
				<< "  季军编号：" << this->m_Record[i][4] << "  得分：" << this->m_Record[i][5]
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::Clear_Record()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//以ios::trunc打开文件，若存在，则删除新建文件
		ofs.close();
		//重置比赛
		this->Reset_Contest();

		//更新标志
		this->FileIsEmpty = true;

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

//重置比赛
void SpeechManager::Reset_Contest()
{
	//初始化比赛
	this->Init_Speech();
	//创建选手
	this->Create_Speaker();
	//加载往届记录
	this->Load_Record();
}

//析构函数
SpeechManager::~SpeechManager()
{

}