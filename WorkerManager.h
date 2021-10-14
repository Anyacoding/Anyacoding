#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<fstream>
//保存数据的文件
#define FILENAME "超超社畜公司.txt"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//菜单展示函数
	void showMenu();

	//0.退出系统
	void exitSystem();

	//1.添加职工
	void addEmp();

	//2.显示职工
	void showEmp();

	//3.删除职工
	void deleteEmp();

	//判断职工编号是否存在，-1：不存在；存在则返回在m_EmpArray中的索引
	int empIsExist(int id);
	//进行一个函数的重载，主要功能是判断是否有一个或以上该姓名的员工
	int empIsExist(string name);
    //把该姓名的员工全部打印出来
	void empIsExist(string name, int select);

	//4.修改职工
	void modifyEmp();

	//5.查找职工
	void findEmp();

	//6.按照编号排序（升序&降序）
	void sortEmp();

	//7.清空职工
	void clearEmp();
	//保存数据
	void save();

	//获取文件中的数据个数
	int getFileEmpNum();

	//当文件不为空时的初始化函数
	void initEmp();

	//析构函数
	~WorkerManager();

public:
	int m_Empnum; //职工数
	Worker** m_EmpArray; //职工数组

public:
	bool m_FileIsEmpty; //判断文件是否为空
};

#endif
