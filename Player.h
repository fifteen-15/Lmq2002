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


	//void special_ground(int tiledGid);  //����ذ��ϵ��������
	Point pCollision(int x, int y);  //�����ƶ������ȡ��ײ��
	//friend class Controller_Move;

	void hitted(int attack);   //������
	int getiHP();   //Ѫ��
	int getDefence();
	int getSpeed();

	void resetData();

private:
	TMXTiledMap* m_map;
	//Player* m_player;

	//��������Ƿ��������ϰ���
	bool isJumping;

	//�����ײ�ĵ�ͼ��
	TMXLayer* meta;

	//����������ת��Ϊ��ͼ��������
	Point tileCoordForPosition(Point pos);

	int m_iHP;  //����Ѫ��
	int m_defence;  //����ֵ
	int m_speed;

};


#endif