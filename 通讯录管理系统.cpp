#include <iostream>
#include <string>

#define MAX 1000
using namespace std;

struct Person
{
	string name;
	int sex;//男是1，女是0
	int age;
	string phone;
	string adr;
};
struct addressbooks
{
	struct Person personArray[MAX];
	int size;
};

void shouMenu()
{   
	cout << "**************************" << endl;
	cout << "***** 1、添加联系人  *****" << endl;
	cout << "***** 2、显示联系人  *****" << endl;
	cout << "***** 3、删除联系人  *****" << endl;
	cout << "***** 4、查找联系人  *****" << endl;
	cout << "***** 5、修改联系人  *****" << endl;
	cout << "***** 6、清空联系人  *****" << endl;
	cout << "***** 0、退出通讯录  *****" << endl; 
	cout << "**************************" << endl;
}

void addperson(struct addressbooks* abs)
{
	if (abs->size == MAX)
	{
		cout << "通讯录已满,无法添加！" << endl;

		return;
	}
	else
	{
		abs->size++;
		cout << "请输入姓名:" << endl;
		cin >> abs->personArray[(abs->size)].name;
		cout << "请输入性别：" << endl << "1 -- 男" << endl << "0 -- 女" << endl;
		int sex = -1;
		while (1)
		{
			cin >> sex;
			if (sex == 1 || sex == 0)
			{
				abs->personArray[(abs->size)].sex = sex;
				break;
			}
			else
				cout << "输入有误，请重新输入" << endl;
		}
		cout << "请输入年龄：" << endl;
		cin >> abs->personArray[(abs->size)].age;
		cout << "请输入联系电话：" << endl;
		cin >> abs->personArray[(abs->size)].phone;
		cout << "请输入家庭住址：" << endl;
		cin >> abs->personArray[(abs->size)].adr;
		cout << "添加成功！奥里给！" << endl;

	}
}

void showperson(struct addressbooks* abs)
{
	int i;
	if (abs->size == 0)
		cout << "当前记录为空" << endl;
	else
	for (i = 1; i <= abs->size; i++)
	{
		
		
			cout << "姓名：" << abs->personArray[i].name << "         " << "性别:";
			if (abs->personArray[i].sex == 1)
				cout << "男" << "         ";
			else
				cout << "女" << "         ";
			cout << "年龄：" << abs->personArray[i].age << "         ";
			cout << "电话：" << abs->personArray[i].phone << "         ";
			cout << "住址：" << abs->personArray[i].adr << "         " << endl;
	
	}

}

void deletperson(struct addressbooks* abs)
{
	int i, flag=1;
	string name;
	cout << "请输入您要删除的联系人:" << endl;
	cin >> name;
	for (i = 1; i <= abs->size; i++)
	{
		if (name==abs->personArray[i].name)
		{
			flag = 0;
			cout << "删除成功" << endl;
			for (; i < abs->size; i++)
			{
				abs->personArray[i] = abs->personArray[i + 1];
			}
			abs->size--;
			break;
		}
	}
	if (flag)
		cout << "抱歉，此人不存在哦" << endl;
}

void findperson(struct addressbooks* abs)
{
	int i, flag = 1;
	string name;
	cout << "请输入您要查找的联系人:" << endl;
	cin >> name;
	for (i = 1; i <= abs->size; i++)
	{
		if (name == abs->personArray[i].name)
		{
			flag = 0;
			cout << "姓名：" << abs->personArray[i].name << "         " << "性别:";
			if (abs->personArray[i].sex == 1)
				cout << "男" << "         ";
			else
				cout << "女" << "         ";
			cout << "年龄：" << abs->personArray[i].age << "         ";
			cout << "电话：" << abs->personArray[i].phone << "         ";
			cout << "住址：" << abs->personArray[i].adr << "         " << endl;
			break;
		}
	}
	if (flag)
		cout << "抱歉，此人不存在哦" << endl;
}



void changeperson(struct addressbooks* abs)
{
	int i, flag=1;
	string name;
	cout << "请输入您要修改的联系人：" << endl;
		cin >> name;
		for (i = 1; i <= abs->size; i++)
		{
			if (name == abs->personArray[i].name)
			{
				flag = 0;
				cout << "请输入姓名:" << endl;
				cin >> abs->personArray[i].name;
				cout << "请输入性别：" << endl << "1 -- 男" << endl << "0 -- 女" << endl;
				int sex = -1;
				while (1)
				{
					cin >> sex;
					if (sex == 1 || sex == 0)
					{
						abs->personArray[i].sex = sex;
						break;
					}
					else
						cout << "输入有误，请重新输入" << endl;
				}
				cout << "请输入年龄：" << endl;
				cin >> abs->personArray[i].age;
				cout << "请输入联系电话：" << endl;
				cin >> abs->personArray[i].phone;
				cout << "请输入家庭住址：" << endl;
				cin >> abs->personArray[i].adr;
				cout << "修改成功！奥里给！" << endl;
				break;
			}
		}
		if (flag)
			cout << "抱歉，此人不存在哦" << endl;
}

void clearperson(struct addressbooks* abs)
{
	abs->size = 0;
	cout << "通讯录已清空" << endl;
}



	int main()
	{
		int select=0 ;
		addressbooks abs;
		abs.size = 0;
		while (1)
		{
			shouMenu();
			cin >> select;
			switch (select)
			{
			case 1: //添加联系人
				addperson(&abs);
				break;
			case 2: //显示联系人
				showperson(&abs);
				break;
			case 3: //删除联系人
				deletperson(&abs);
				break;
			case 4: //查找联系人
				findperson(&abs);
				break;
			case 5: //修改联系人
				changeperson(&abs);
				break;
			case 6: //清空联系人
				clearperson(&abs);
				break;
			case 0:
				cout << "欢迎下次使用" << endl;
				system("pause");
				return 0;
			}
			system("pause");
			system("cls");
		}
		

		return 0;
	}