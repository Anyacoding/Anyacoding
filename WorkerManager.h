#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<fstream>
//�������ݵ��ļ�
#define FILENAME "��������˾.txt"

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//�˵�չʾ����
	void showMenu();

	//0.�˳�ϵͳ
	void exitSystem();

	//1.���ְ��
	void addEmp();

	//2.��ʾְ��
	void showEmp();

	//3.ɾ��ְ��
	void deleteEmp();

	//�ж�ְ������Ƿ���ڣ�-1�������ڣ������򷵻���m_EmpArray�е�����
	int empIsExist(int id);
	//����һ�����������أ���Ҫ�������ж��Ƿ���һ�������ϸ�������Ա��
	int empIsExist(string name);
    //�Ѹ�������Ա��ȫ����ӡ����
	void empIsExist(string name, int select);

	//4.�޸�ְ��
	void modifyEmp();

	//5.����ְ��
	void findEmp();

	//6.���ձ����������&����
	void sortEmp();

	//7.���ְ��
	void clearEmp();
	//��������
	void save();

	//��ȡ�ļ��е����ݸ���
	int getFileEmpNum();

	//���ļ���Ϊ��ʱ�ĳ�ʼ������
	void initEmp();

	//��������
	~WorkerManager();

public:
	int m_Empnum; //ְ����
	Worker** m_EmpArray; //ְ������

public:
	bool m_FileIsEmpty; //�ж��ļ��Ƿ�Ϊ��
};

#endif
