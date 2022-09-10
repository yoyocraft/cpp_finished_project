#pragma once
#include <iostream>
#include <fstream>
#include"worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//显示菜单
	void Show_Menu();

	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否存在
	bool m_FileisExist;

	//判断文件是否为空
	bool m_FileisEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化职工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//判断员工是否存在，如果存在返回职工所在数组的位置，不存在返回-1
	int isExist(int id);

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//职工排序
	void Sort_Emp();

	//清空数据
	void Clean_File();

	//析构函数
	~WorkerManager();
};