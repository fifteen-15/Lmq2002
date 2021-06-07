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
		setVisible(true);   //设置可见
		m_isAlive = true;   //标记怪物为活动状态
	}
}



void Monster::setTiledMapPosition(Point position)
{
	if (getSprite() != NULL) {
		/*初始化怪物坐标*/
		setPosition(position);
	}
}

bool Monster::isAlive()
{
	return m_isAlive;
}

bool Monster::isCollideWithPlayer(Player* player)
{
	//获取碰撞检查对象的矩阵区域
	Rect entityRect = player->getBoundingBox();

	Point monsterPos = getPosition();

	//判断中心点是否有交集
	return entityRect.containsPoint(monsterPos);
}

void Monster::bindPlayer(Player* player)
{
	m_player = player;
}

void Monster::hide()
{
	if (getSprite() != NULL) {
		setVisible(false);   //设置可见
		m_isAlive = false;   //标记怪物为活动状态
	}
}

