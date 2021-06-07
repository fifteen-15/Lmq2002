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
	//�󶨾������
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	//���ÿ�����
	void setController(mController* controller);

	//ʵ��simplemovelistener�ӿڵķ���
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

protected:
	Sprite* m_sprite;
	mController* m_controller;
};





#endif