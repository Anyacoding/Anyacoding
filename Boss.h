#pragma once
#include"Worker.h"
//������
class Boss :public Worker
{
public:
	//���캯��
	Boss(int id, string name, int did);
	//��ȡԱ���ĸ�λ
	string getDid();
	//��ʾԱ������Ϣ
	void showInfo();

};