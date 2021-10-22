#include"WorkerManager.h"
#include<iostream>
using namespace std;

//构造函数
WorkerManager::WorkerManager()
{
	//1.判断文件是否存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在捏" << endl;
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.判断文件是否为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空捏" << endl;
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3.文件存在且不为空，即有数据
	int num = this->getFileEmpNum();
	cout << "职工人数为:" << num << endl;
	this->m_Empnum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_Empnum];
   //进行数据初始化（数据迁移）
	this->initEmp();
}

//菜单展示函数
void WorkerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}

//0.退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎您下次使用捏~" << endl;
	system("pause");
	exit(0);
}

//1.添加职工
void WorkerManager::addEmp()
{
	cout << "请输入需要添加的社畜数量捏：" << endl;
	int addEmpNum = 0;
	cin >> addEmpNum;
	if (addEmpNum > 0)
	{
		//新空间大小
		int newsize = this->m_Empnum + addEmpNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newsize];
		//拷贝已有职工
		if (this->m_Empnum != 0)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新职工
		for (int i = 0; i < addEmpNum; i++)
		{
			int id;
			string name;
			int did;

			cout << "请输入第 " << i + 1 << " 个职工的编号：" << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个职工的姓名：" << endl;
			cin >> name;
			cout << "第 " << i + 1 << " 个职工的职务是：" << endl
				 << "1.普通职工" << endl
				 << "2.经理" << endl
				 << "3.老板" << endl;
			
			while (true)
			{
				cin >> did;
				if (did == 1 || did == 2 || did == 3)
				{
					switch (did)
					{
					case 1:
						newSpace[this->m_Empnum + i] = new Employee(id, name, did);
						break;
					case 2:
						newSpace[this->m_Empnum + i] = new Manager(id, name, did);
						break;
					case 3:
						newSpace[this->m_Empnum + i] = new Boss(id, name, did);
						break;
					default:
						break;
					}
					break; //打破while循环
				}
				cout << "输入有误，请重新选择职工部门编号~" << endl;
			}

		}
		//释放原有空间数组
		delete[] this->m_EmpArray;
		//更改指针指向
		this->m_EmpArray = newSpace;
		//更改职工人数
		this->m_Empnum = newsize;
		//更新状态
		this->m_FileIsEmpty = false;
		//输出成功添加
		cout << "成功添加 " << addEmpNum << " 个新社畜捏！" << endl;
		
		this->save(); //保存到文件中
	}
	else
	{
		cout << "输入有误，请重新输入！" << endl;
	}
}

//保存数据
void WorkerManager::save()
{
	//创建文件输出流
	ofstream ofs;
	//以输出的方式打开文件——写文件
	ofs.open(FILENAME, ios::out);
	//写文件
	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_Did << endl;
	}
	//关闭文件
	ofs.close();
}


//获取文件中的数据个数
int WorkerManager::getFileEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios:: in);
	int num = 0;
	int id;
	string name;
	int did;
	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	ifs.close();
	return num;
}

//当文件不为空时的初始化函数
void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	Worker* Worker = NULL;
	while (ifs >> id && ifs >> name && ifs >> did) {
		if (did == 1) {
			Worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			Worker = new Manager(id, name, did);
		}
		else {
			Worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index++] = Worker;
	}
	ifs.close();
}

//显示职工
void WorkerManager::showEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else  {
		for (int i = 0; i < this->m_Empnum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
}

//删除职工
void WorkerManager::deleteEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入您想删除的社畜编号:" << endl;
		int id;
		cin >> id;
		if (this->empIsExist(id) != -1) {
			int index = this->empIsExist(id);
			for (int i = index + 1; i < this->m_Empnum; i++) {
				this->m_EmpArray[i - 1] = this->m_EmpArray[i];
			}
			this->m_Empnum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "您想要删除的社畜不存在捏" << endl;
		}
	}
}

//判断职工编号是否存在，-1：不存在；存在则返回在m_EmpArray中的索引
int WorkerManager::empIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_Empnum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

//实现按姓名查找的功能函数重载，只要进行判断有无一个或以上该姓名的职工
int WorkerManager::empIsExist(string name)
{
	int index = -1;
	for (int i = 0; i < this->m_Empnum; i++) {
		if (this->m_EmpArray[i]->m_Name == name) {
			index = i;
			break;
		}
	}
	return index;
}

//为了解决同名的情况而附加的重载，int select形参无实际意义，仅为了进行函数重载的区分
void WorkerManager::empIsExist(string name, int select)
{
	for (int i = 0; i < this->m_Empnum; i++) {
		if (this->m_EmpArray[i]->m_Name == name) {

			this->m_EmpArray[i]->showInfo();
		}
	}
}

//4.修改职工
void WorkerManager::modifyEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入您想修改的社畜编号:" << endl;
		int id;
		cin >> id;
		if (this->empIsExist(id) != -1) {
			int index = this->empIsExist(id);//index为数组中目标员工下标
			delete this->m_EmpArray[index];
			cout << "查到" << id << "号社畜,请输入新的职工编号:" << endl;
			int id;
			cin >> id;
			cout << "请输入新姓名:" << endl;
			string name;
			cin >> name;
			cout << "请输入岗位:" << endl
				<< "1.普通职工" << endl
				<< "2.经理" << endl
				<< "3.老板" << endl;
			int choice;
			Worker* Worker = NULL;
			while (1) {

				cin >> choice;

				if (choice == 1 || choice == 2 || choice == 3) {
					switch (choice)
					{
					case 1:
						Worker = new Employee(id, name, 1);
						break;
					case 2:
						Worker = new Manager(id, name, 2);
						break;
					case 3:
						Worker = new Boss(id, name, 3);
						break;
					default:
						break;
					}
					break;
				}
				else {
					cout << "输入有误，请重新选择职工部门编号~" << endl;
				}
			}
			this->m_EmpArray[index] = Worker;
			this->save();
			cout << "修改成功!" << endl;
		}
		else {
			cout << "您想要修改的社畜不存在捏" << endl;
		}
	}
}

//5.查找职工
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入您喜欢的查找方式捏:" << endl
			 << "1.按Id号查找" << endl
		     << "2.按姓名查找" << endl;
		int select;
		
		while (1) {
			cin >> select;
			if (select == 1) {
				cout << "请输入您想查找的社畜编号:" << endl;
				int id;
				cin >> id;
				if (this->empIsExist(id) != -1) {
					cout << "查找成功,该社畜信息如下:" << endl;
					this->m_EmpArray[this->empIsExist(id)]->showInfo();
				}
				else {
					cout << "抱歉,查无此人" << endl;
				}
				break;
			}
			else if (select == 2) {
				cout << "请输入您想查找的社畜姓名:" << endl;
				string name;
				cin >> name;
				if (this->empIsExist(name) != -1) {
					cout << "查找成功,该社畜信息如下:" << endl;
					this->empIsExist(name, select);
					//this->m_EmpArray[this->empIsExist(name)]->showInfo();
				}
				else {
					cout << "抱歉,查无此人" << endl;
				}
				break;
			}
			else {
				cout << "您的输入有误，请不要调皮捏~" << endl;
			}
		}

	}
}

//6.按照编号排序（升序&降序）
void WorkerManager::sortEmp()
{
	cout << "请选择您喜欢的排序方式:" << endl
		 << "1.按职工编号升序排列" << endl
	     << "2.按职工编号降序排列" << endl;
	int choice;
	while (1) {
		cin >> choice;
		if (choice == 1 || choice == 2) {
			for (int i = 0; i < this->m_Empnum; i++) {
				int minOrmax = i;
				for (int j = i + 1; j < this->m_Empnum; j++) {
					//升序
					if (choice == 1) {
						if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id) {
							minOrmax = j;
						}
					}
					//降序
					else {
						if (this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id) {
							minOrmax = j;
						}
					}
				}
				if (minOrmax != i) {
					Worker* temp;
					temp = this->m_EmpArray[minOrmax];
					this->m_EmpArray[minOrmax] = this->m_EmpArray[i];
					this->m_EmpArray[i] = temp;
				}	
			}
			this->save();
			this->showEmp();
			break;
		} 
		cout << "请输入合法的选项,不要调皮~" << endl;
	}

}

//7.清空职工
void WorkerManager::clearEmp()
{
	cout << "确认清空?" << endl
		<< "1.确认" << endl
		<< "2.返回" << endl;
	int select; 
	while (1) {
		cin >> select;
		if (select == 1 || select == 2) {
			if (select == 1) {
				ofstream ofs;
				ofs.open(FILENAME, ios::trunc);
				ofs.close();
				if (this->m_EmpArray != NULL) {
					for (int i = 0; i < this->m_Empnum; i++) {
						delete this->m_EmpArray[i];
					}
					delete[] this->m_EmpArray;
					this->m_EmpArray = NULL;
				}
				this->m_Empnum = 0;
				this->m_FileIsEmpty = true;
				cout << "清空成功!" << endl;
				break;
			}
			else {
				return;
			}
		}
		else {
			cout << "没有该选项,请重新选择~" << endl;
		}
	}
}


//析构函数
WorkerManager::~WorkerManager()
{
	//一般来说对象的生命周期结束时成员都会被销毁，但是指针类成员若指向的区域内容没有被手动释放，
	//在指针地址丢失后则会留下垃圾,所以重写虚构函数一般是在对象成员有指针的情况下才有必要
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_Empnum; i++) {
			delete this->m_EmpArray[i];
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}