#pragma once
#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "cocos2d.h"
#define MPMAX 6
#define ACMAX 7
#define HPMAX 180
#define SPEED 1
using namespace cocos2d;

class Knight:
	public cocos2d::Node
{
	virtual int getMP(int MP);
	virtual int getHP(int HP);
	virtual void setMP(int MP);
	virtual void setHP(int HP);
	virtual void setSpeed(int speed);
//	virtual bool create() = 0;
//	virtual Sprite* create();


};

class Paladin :
	public Knight
{
public:
	Sprite* myPaladin;
	SpriteFrame* normalLeft;
	SpriteFrame* runLeft;
	SpriteFrame* normalRight;
	SpriteFrame* runRight;
	Sprite* dieRight;
	Sprite* dieLeft;

	enum Direction {
		Left,
		Right
	};


	//初始化图像工作
	Paladin();
	~Paladin();

	bool getIsLive();
	void setDead();

	//不清楚作用
	void onEnter();
	void onExit();

	//对象指针
	static Paladin* paladinInstance;
	//把对象指针传出去，即把对象给别人拿来用
	static Paladin* getPaladinInstance();
	//建唯一一个对象，给一个内存。
	static Paladin* create();

	//令地图滚动达到人物行走目的，这个在场景类里实现函数
	void dieAnimation();
	//到达地图边界的时候可能要用到moveby?
	void runAnimation();

	//主角受伤之后
	void hit(int attack);
	//碰撞检测来判断
	bool isHit();
	bool isListenerAllowed();

	void bindEnermy(Sprite* enermy);

	//主角出生动画
	void born();
	//游戏重新开始重置主角信息
	void reset();
	

private:
	bool init();
	bool isLive;
	int MP;
	int HP;
	int AC;
	int speed;
	int score;
	Sprite* enermy;
	Direction direction;
	//未知
	cocos2d::Point position;
	//主角宽高，用来检测碰撞
	Size size;
};

class Berserker :
	public Knight
{
	int MP;
	int HP;
	int speed;
	std::string fileName;
	virtual bool init();
//	Sprite* create();
};

#endif
