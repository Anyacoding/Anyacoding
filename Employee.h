#pragma once
#include"Worker.h"
using namespace std;

//��ͨԱ����
class Employee :public Worker
{
public:
	//���캯��
	Employee(int id, string name, int did);
	//��ȡԱ���ĸ�λ����д���ി�麯��
	string getDid();
	//��ʾԱ����Ϣ����д���ി�麯��
	void showInfo();

};
