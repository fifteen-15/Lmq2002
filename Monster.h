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
	virtual void update(float dt); //��дupdate����

	void show();  //��ʾ����
	
	void setTiledMapPosition(Point position); //���ù�������
	bool isAlive();//�ж��Ƿ�״̬

	//�Ƿ�����ս������Χ
	//�����ײ����
	bool isCollideWithPlayer(Player* player);

	//����Ҷ���
	void bindPlayer(Player* player);

	void hide();

private:
	bool m_isAlive;
	Player* m_player;

};

#endif