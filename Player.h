#pragma once
#ifndef _Player_H_
#define _Player_H_
#include "HelloWorldScene.h"
#include "Controller_Move.h"

#include "Characters.h"
class Player :public Characters
{
public:
	CREATE_FUNC(Player);

	Player();
	virtual bool init();
	void run();
	//void run_left();

	virtual void update(float dt);
	

	void setViewPointByPlayer();

	virtual void setTagPosition(int x, int y);

	void setTiledMap(TMXTiledMap* map);


	//void special_ground(int tiledGid);  //特殊地板上的特殊操作
	Point pCollision(int x, int y);  //根据移动方向获取碰撞点
	//friend class Controller_Move;

	void hitted(int attack);   //被攻击
	int getiHP();   //血条
	int getDefence();
	int getSpeed();

	void resetData();

private:
	TMXTiledMap* m_map;
	//Player* m_player;

	//标记主角是否碰到了障碍物
	bool isJumping;

	//检测碰撞的地图层
	TMXLayer* meta;

	//将像素坐标转换为地图格子坐标
	Point tileCoordForPosition(Point pos);

	int m_iHP;  //主角血量
	int m_defence;  //护盾值
	int m_speed;

};


#endif