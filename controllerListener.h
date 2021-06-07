#pragma once
#ifndef _controllerListener_H_
#define _controlelrListener_H_
#include"cocos2d.h"

//******************所谓监听器，就是用来获取监听对象的位置信息的
using namespace cocos2d;

class controllerListener {
public:
	//设置目标坐标
	virtual void setTagPosition(int x, int y) = 0;

	//获取目标坐标
	virtual Point getTagPosition() = 0;

};

#endif