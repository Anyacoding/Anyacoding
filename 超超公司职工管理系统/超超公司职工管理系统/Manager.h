#pragma once
#include"Worker.h"
//������
class Manager :public Worker
{
public:
	//���캯��
	Manager(int id, string name, int did);
	//��ȡԱ���ĸ�λ
	string getDid();
	//��ʾԱ������Ϣ
	void showInfo();

};
