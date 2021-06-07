#pragma once
#ifndef _Controller_Move_H_
#define _Controller_Move_H_
#include "Controller.h"
#include "cocos2d.h"

#include "Player.h"
using namespace cocos2d;




class Controller_Move : public mController {
public:
	CREATE_FUNC(Controller_Move);
	virtual bool init();

	virtual void update(float dt);

	//设置x方向的移动速度
	void setiXSpeed(int iSpeed);

	//设置y方向的移动速度
	void setiYSpeed(int iSpeed);

	//****************************存放按键的状态是不是按压中
	//std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//Point pCollision(float x, float y);
	int miXSpeed() { return m_iXSpeed; }
	int miYSpeed() { return m_iYSpeed; }
	//friend class Player;

	//void bindPlayer(Player* player);

private:
	int m_iXSpeed;
	int m_iYSpeed;

	//Player* m_player;

	//注册键盘事件
	void registeKeyBoardEvent();

};

#endif