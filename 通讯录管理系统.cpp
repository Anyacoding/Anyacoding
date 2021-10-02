#include <iostream>
#include <string>

#define MAX 1000
using namespace std;

struct Person
{
	string name;
	int sex;//����1��Ů��0
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
	cout << "***** 1�������ϵ��  *****" << endl;
	cout << "***** 2����ʾ��ϵ��  *****" << endl;
	cout << "***** 3��ɾ����ϵ��  *****" << endl;
	cout << "***** 4��������ϵ��  *****" << endl;
	cout << "***** 5���޸���ϵ��  *****" << endl;
	cout << "***** 6�������ϵ��  *****" << endl;
	cout << "***** 0���˳�ͨѶ¼  *****" << endl; 
	cout << "**************************" << endl;
}

void addperson(struct addressbooks* abs)
{
	if (abs->size == MAX)
	{
		cout << "ͨѶ¼����,�޷���ӣ�" << endl;

		return;
	}
	else
	{
		abs->size++;
		cout << "����������:" << endl;
		cin >> abs->personArray[(abs->size)].name;
		cout << "�������Ա�" << endl << "1 -- ��" << endl << "0 -- Ů" << endl;
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
				cout << "������������������" << endl;
		}
		cout << "���������䣺" << endl;
		cin >> abs->personArray[(abs->size)].age;
		cout << "��������ϵ�绰��" << endl;
		cin >> abs->personArray[(abs->size)].phone;
		cout << "�������ͥסַ��" << endl;
		cin >> abs->personArray[(abs->size)].adr;
		cout << "��ӳɹ����������" << endl;

	}
}

void showperson(struct addressbooks* abs)
{
	int i;
	if (abs->size == 0)
		cout << "��ǰ��¼Ϊ��" << endl;
	else
	for (i = 1; i <= abs->size; i++)
	{
		
		
			cout << "������" << abs->personArray[i].name << "         " << "�Ա�:";
			if (abs->personArray[i].sex == 1)
				cout << "��" << "         ";
			else
				cout << "Ů" << "         ";
			cout << "���䣺" << abs->personArray[i].age << "         ";
			cout << "�绰��" << abs->personArray[i].phone << "         ";
			cout << "סַ��" << abs->personArray[i].adr << "         " << endl;
	
	}

}

void deletperson(struct addressbooks* abs)
{
	int i, flag=1;
	string name;
	cout << "��������Ҫɾ������ϵ��:" << endl;
	cin >> name;
	for (i = 1; i <= abs->size; i++)
	{
		if (name==abs->personArray[i].name)
		{
			flag = 0;
			cout << "ɾ���ɹ�" << endl;
			for (; i < abs->size; i++)
			{
				abs->personArray[i] = abs->personArray[i + 1];
			}
			abs->size--;
			break;
		}
	}
	if (flag)
		cout << "��Ǹ�����˲�����Ŷ" << endl;
}

void findperson(struct addressbooks* abs)
{
	int i, flag = 1;
	string name;
	cout << "��������Ҫ���ҵ���ϵ��:" << endl;
	cin >> name;
	for (i = 1; i <= abs->size; i++)
	{
		if (name == abs->personArray[i].name)
		{
			flag = 0;
			cout << "������" << abs->personArray[i].name << "         " << "�Ա�:";
			if (abs->personArray[i].sex == 1)
				cout << "��" << "         ";
			else
				cout << "Ů" << "         ";
			cout << "���䣺" << abs->personArray[i].age << "         ";
			cout << "�绰��" << abs->personArray[i].phone << "         ";
			cout << "סַ��" << abs->personArray[i].adr << "         " << endl;
			break;
		}
	}
	if (flag)
		cout << "��Ǹ�����˲�����Ŷ" << endl;
}



void changeperson(struct addressbooks* abs)
{
	int i, flag=1;
	string name;
	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
		cin >> name;
		for (i = 1; i <= abs->size; i++)
		{
			if (name == abs->personArray[i].name)
			{
				flag = 0;
				cout << "����������:" << endl;
				cin >> abs->personArray[i].name;
				cout << "�������Ա�" << endl << "1 -- ��" << endl << "0 -- Ů" << endl;
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
						cout << "������������������" << endl;
				}
				cout << "���������䣺" << endl;
				cin >> abs->personArray[i].age;
				cout << "��������ϵ�绰��" << endl;
				cin >> abs->personArray[i].phone;
				cout << "�������ͥסַ��" << endl;
				cin >> abs->personArray[i].adr;
				cout << "�޸ĳɹ����������" << endl;
				break;
			}
		}
		if (flag)
			cout << "��Ǹ�����˲�����Ŷ" << endl;
}

void clearperson(struct addressbooks* abs)
{
	abs->size = 0;
	cout << "ͨѶ¼�����" << endl;
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
			case 1: //�����ϵ��
				addperson(&abs);
				break;
			case 2: //��ʾ��ϵ��
				showperson(&abs);
				break;
			case 3: //ɾ����ϵ��
				deletperson(&abs);
				break;
			case 4: //������ϵ��
				findperson(&abs);
				break;
			case 5: //�޸���ϵ��
				changeperson(&abs);
				break;
			case 6: //�����ϵ��
				clearperson(&abs);
				break;
			case 0:
				cout << "��ӭ�´�ʹ��" << endl;
				system("pause");
				return 0;
			}
			system("pause");
			system("cls");
		}
		

		return 0;
	}