#include"WorkerManager.h"
#include<iostream>
using namespace std;

//���캯��
WorkerManager::WorkerManager()
{
	//1.�ж��ļ��Ƿ����
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���������" << endl;
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ж��ļ��Ƿ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ����" << endl;
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3.�ļ������Ҳ�Ϊ�գ���������
	int num = this->getFileEmpNum();
	cout << "ְ������Ϊ:" << num << endl;
	this->m_Empnum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_Empnum];
   //�������ݳ�ʼ��������Ǩ�ƣ�
	this->initEmp();
}

//�˵�չʾ����
void WorkerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}

//0.�˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ���´�ʹ����~" << endl;
	system("pause");
	exit(0);
}

//1.���ְ��
void WorkerManager::addEmp()
{
	cout << "��������Ҫ��ӵ�����������" << endl;
	int addEmpNum = 0;
	cin >> addEmpNum;
	if (addEmpNum > 0)
	{
		//�¿ռ��С
		int newsize = this->m_Empnum + addEmpNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newsize];
		//��������ְ��
		if (this->m_Empnum != 0)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�����ְ��
		for (int i = 0; i < addEmpNum; i++)
		{
			int id;
			string name;
			int did;

			cout << "������� " << i + 1 << " ��ְ���ı�ţ�" << endl;
			cin >> id;
			cout << "������� " << i + 1 << " ��ְ����������" << endl;
			cin >> name;
			cout << "�� " << i + 1 << " ��ְ����ְ���ǣ�" << endl
				 << "1.��ְͨ��" << endl
				 << "2.����" << endl
				 << "3.�ϰ�" << endl;
			
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
					break; //����whileѭ��
				}
				cout << "��������������ѡ��ְ�����ű��~" << endl;
			}

		}
		//�ͷ�ԭ�пռ�����
		delete[] this->m_EmpArray;
		//����ָ��ָ��
		this->m_EmpArray = newSpace;
		//����ְ������
		this->m_Empnum = newsize;
		//����״̬
		this->m_FileIsEmpty = false;
		//����ɹ����
		cout << "�ɹ���� " << addEmpNum << " ����������" << endl;
		
		this->save(); //���浽�ļ���
	}
	else
	{
		cout << "�����������������룡" << endl;
	}
}

//��������
void WorkerManager::save()
{
	//�����ļ������
	ofstream ofs;
	//������ķ�ʽ���ļ�����д�ļ�
	ofs.open(FILENAME, ios::out);
	//д�ļ�
	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_Did << endl;
	}
	//�ر��ļ�
	ofs.close();
}


//��ȡ�ļ��е����ݸ���
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

//���ļ���Ϊ��ʱ�ĳ�ʼ������
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

//��ʾְ��
void WorkerManager::showEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else  {
		for (int i = 0; i < this->m_Empnum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
}

//ɾ��ְ��
void WorkerManager::deleteEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "����������ɾ����������:" << endl;
		int id;
		cin >> id;
		if (this->empIsExist(id) != -1) {
			int index = this->empIsExist(id);
			for (int i = index + 1; i < this->m_Empnum; i++) {
				this->m_EmpArray[i - 1] = this->m_EmpArray[i];
			}
			this->m_Empnum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "����Ҫɾ�������󲻴�����" << endl;
		}
	}
}

//�ж�ְ������Ƿ���ڣ�-1�������ڣ������򷵻���m_EmpArray�е�����
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

//ʵ�ְ��������ҵĹ��ܺ������أ�ֻҪ�����ж�����һ�������ϸ�������ְ��
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

//Ϊ�˽��ͬ������������ӵ����أ�int select�β���ʵ�����壬��Ϊ�˽��к������ص�����
void WorkerManager::empIsExist(string name, int select)
{
	for (int i = 0; i < this->m_Empnum; i++) {
		if (this->m_EmpArray[i]->m_Name == name) {

			this->m_EmpArray[i]->showInfo();
		}
	}
}

//4.�޸�ְ��
void WorkerManager::modifyEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "�����������޸ĵ�������:" << endl;
		int id;
		cin >> id;
		if (this->empIsExist(id) != -1) {
			int index = this->empIsExist(id);//indexΪ������Ŀ��Ա���±�
			delete this->m_EmpArray[index];
			cout << "�鵽" << id << "������,�������µ�ְ�����:" << endl;
			int id;
			cin >> id;
			cout << "������������:" << endl;
			string name;
			cin >> name;
			cout << "�������λ:" << endl
				<< "1.��ְͨ��" << endl
				<< "2.����" << endl
				<< "3.�ϰ�" << endl;
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
					cout << "��������������ѡ��ְ�����ű��~" << endl;
				}
			}
			this->m_EmpArray[index] = Worker;
			this->save();
			cout << "�޸ĳɹ�!" << endl;
		}
		else {
			cout << "����Ҫ�޸ĵ����󲻴�����" << endl;
		}
	}
}

//5.����ְ��
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "��������ϲ���Ĳ��ҷ�ʽ��:" << endl
			 << "1.��Id�Ų���" << endl
		     << "2.����������" << endl;
		int select;
		
		while (1) {
			cin >> select;
			if (select == 1) {
				cout << "������������ҵ�������:" << endl;
				int id;
				cin >> id;
				if (this->empIsExist(id) != -1) {
					cout << "���ҳɹ�,��������Ϣ����:" << endl;
					this->m_EmpArray[this->empIsExist(id)]->showInfo();
				}
				else {
					cout << "��Ǹ,���޴���" << endl;
				}
				break;
			}
			else if (select == 2) {
				cout << "������������ҵ���������:" << endl;
				string name;
				cin >> name;
				if (this->empIsExist(name) != -1) {
					cout << "���ҳɹ�,��������Ϣ����:" << endl;
					this->empIsExist(name, select);
					//this->m_EmpArray[this->empIsExist(name)]->showInfo();
				}
				else {
					cout << "��Ǹ,���޴���" << endl;
				}
				break;
			}
			else {
				cout << "�������������벻Ҫ��Ƥ��~" << endl;
			}
		}

	}
}

//6.���ձ����������&����
void WorkerManager::sortEmp()
{
	cout << "��ѡ����ϲ��������ʽ:" << endl
		 << "1.��ְ�������������" << endl
	     << "2.��ְ����Ž�������" << endl;
	int choice;
	while (1) {
		cin >> choice;
		if (choice == 1 || choice == 2) {
			for (int i = 0; i < this->m_Empnum; i++) {
				int minOrmax = i;
				for (int j = i + 1; j < this->m_Empnum; j++) {
					//����
					if (choice == 1) {
						if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id) {
							minOrmax = j;
						}
					}
					//����
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
		cout << "������Ϸ���ѡ��,��Ҫ��Ƥ~" << endl;
	}

}

//7.���ְ��
void WorkerManager::clearEmp()
{
	cout << "ȷ�����?" << endl
		<< "1.ȷ��" << endl
		<< "2.����" << endl;
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
				cout << "��ճɹ�!" << endl;
				break;
			}
			else {
				return;
			}
		}
		else {
			cout << "û�и�ѡ��,������ѡ��~" << endl;
		}
	}
}


//��������
WorkerManager::~WorkerManager()
{
	//һ����˵������������ڽ���ʱ��Ա���ᱻ���٣�����ָ�����Ա��ָ�����������û�б��ֶ��ͷţ�
	//��ָ���ַ��ʧ�������������,������д�鹹����һ�����ڶ����Ա��ָ�������²��б�Ҫ
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_Empnum; i++) {
			delete this->m_EmpArray[i];
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}