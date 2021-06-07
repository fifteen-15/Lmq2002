#pragma once
#ifndef _Characters_H_
#define _Characters_H_

#include "cocos2d.h"
#include "Controller.h"
#include "controllerListener.h"
using namespace cocos2d;

class Characters :public Node, public controllerListener
{
public:
	//绑定精灵对象
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	//设置控制器
	void setController(mController* controller);

	//实现simplemovelistener接口的方法
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	mController* m_controller;
};





#endif