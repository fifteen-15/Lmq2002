#pragma once
#ifndef _controllerListener_H_
#define _controlelrListener_H_
#include"cocos2d.h"

//******************��ν������������������ȡ���������λ����Ϣ��
using namespace cocos2d;

class controllerListener {
public:
	//����Ŀ������
	virtual void setTagPosition(int x, int y) = 0;

	//��ȡĿ������
	virtual Point getTagPosition() = 0;

};

#endif