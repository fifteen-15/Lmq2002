#include "Monster.h"

Monster::Monster()
{
	m_isAlive = true;
}

Monster::~Monster()
{
}

bool Monster::init()
{
	show();
	this->scheduleUpdate();
	return true;
}

void Monster::update(float dt)
{
	if (isAlive()) {
		if (isCollideWithPlayer(m_player)) {
			m_player->hitted(3);
			m_isAlive = false;
		}
	}
	if (!isAlive()) {
		hide();
	}
}

void Monster::show()
{
	if (getSprite() != NULL) {
		setVisible(true);   //���ÿɼ�
		m_isAlive = true;   //��ǹ���Ϊ�״̬
	}
}



void Monster::setTiledMapPosition(Point position)
{
	if (getSprite() != NULL) {
		/*��ʼ����������*/
		setPosition(position);
	}
}

bool Monster::isAlive()
{
	return m_isAlive;
}

bool Monster::isCollideWithPlayer(Player* player)
{
	//��ȡ��ײ������ľ�������
	Rect entityRect = player->getBoundingBox();

	Point monsterPos = getPosition();

	//�ж����ĵ��Ƿ��н���
	return entityRect.containsPoint(monsterPos);
}

void Monster::bindPlayer(Player* player)
{
	m_player = player;
}

void Monster::hide()
{
	if (getSprite() != NULL) {
		setVisible(false);   //���ÿɼ�
		m_isAlive = false;   //��ǹ���Ϊ�״̬
	}
}

