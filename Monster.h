#pragma once
#ifndef _Monster_H_
#define _Monster_H_
#include "Characters.h"
#include "Player.h"

class Monster :public Characters {
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();
	virtual void update(float dt); //重写update函数

	void show();  //显示怪物
	
	void setTiledMapPosition(Point position); //重置怪物数据
	bool isAlive();//判断是否活动状态

	//是否进入近战攻击范围
	//检测碰撞即可
	bool isCollideWithPlayer(Player* player);

	//绑定玩家对象
	void bindPlayer(Player* player);

	void hide();

private:
	bool m_isAlive;
	Player* m_player;

};

#endif