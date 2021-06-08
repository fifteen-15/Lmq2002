#include "Player.h"


extern int direction_x, direction_y;

Player::Player()
{
	//��ʼ��Ѫ��
	m_iHP = 10;
	m_defence = 10;
	m_speed = 2;
}

bool Player::init()
{
	return true;
}

void Player::run()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile("boys.plist", "boys.png");  //����֡����

	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;

	//�������� ,������ӵ��б���
	frameList.pushBack(cache->getSpriteFrameByName("boy_run1.png"));
	frameList.pushBack(cache->getSpriteFrameByName("boy_run2.png"));
	

	//���ϼ�¼��������������
	Animation* animation = Animation::createWithSpriteFrames(frameList);



	animation->setLoops(-1);
	//���Ŷ������˴�Ϊ��Զ����

	animation->setDelayPerUnit(0.1f);  //���ò����ٶ�


	//������������
	Animate* animate = Animate::create(animation);

	//����ִ�ж���
	m_sprite->runAction(animate);
	//addChild()


}



void Player::update(float dt)
{	
	float speed = 0.01f;
	auto action_right = Sequence::create(
		//ScaleTo::create(speed, -1.f, 1.f),  //ˮƽ��ת
		ScaleTo::create(speed, 1.f, 1.f),   //ˮƽ��ԭ
		nullptr);

	auto action_left = Sequence::create(
		ScaleTo::create(speed, -1.f, 1.f),  //ˮƽ��ת
		//ScaleTo::create(speed, 1.f, 1.f),   //ˮƽ��ԭ
		nullptr);

	extern int direction_x, direction_y;
	//log("%d", direction_x);
	if (direction_x == 1|| direction_x == 10)
	{
		m_sprite->runAction(action_right);

		if (direction_y == 0 || direction_y == 1)
			run();   //�ý�ɫ��
		if (direction_x == 1)
			direction_x = 2;
		if (direction_y == 1)
			direction_y = 2;
		
	}
	if (direction_x == -1|| direction_x == -10)
	{
		m_sprite->runAction(action_left);

		if (direction_y == 0 || direction_y == 1)
			run();
		if (direction_x == -1)
			direction_x = -2;
		if (direction_y == 1)
			direction_y = 2;

		
	}
	
}



void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();


	//��ͼ��������
	Size mapTiledNum = m_map->getMapSize();
	//log("get the mapTiledNum");

	//��ͼ�������Ӵ�С
	Size tiledSize = m_map->getTileSize();
	//log("get the tiledSize");

	//��ͼ��С
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	//��Ļ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������
	Point spritePos = getPosition();

	//�����������С����Ļ��һ�룬��ȡ��Ļ�е�����
	//����ȡ��������
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//float x = spritePos.x;
	//float y = spritePos.y;

	//���x,y����������Ͻǵļ���ֵ����ȡ����ֵ����
	//����ֵָ���ǲ��õ�ͼ������Ļ��ɳ��ֺڱߵļ�������
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//Ŀ���
	Point destPos = Point(x, y);

	//��Ļ�е�
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	//Point centerPos = Vec2(Director::getInstance()->getVisibleSize() / 2);
	//������Ļ�е�����ƶ���Ŀ�ĵ�֮��ľ���
	Point viewPos = centerPos - destPos;
	//log("viewPos");

	parent->setPosition(viewPos);

}

void Player::setTagPosition(int x, int y)
{
	/****************�ж�ǰ���Ƿ񲻿�ͨ��*****************/
	//ȡ����ǰ��������
	
	//Rect barrierRect = meta->getBoundingBox();

	//��ȡ�������ӵĴ�С
	auto m_segment_width = m_map->getTileSize().width;
	auto m_segment_height = m_map->getTileSize().height;
	//log("%f  ,%f", m_segment_width, m_segment_height);
	//Point dstPos = Point(x, y);
	Size spriteSize = m_sprite->getContentSize();
	//log("x,y��%d,%d", x, y);

	//Point dstPos = pCollision(x, y);
	Point dstPos = Point(x + spriteSize.width / 2, y);
	//log("pos:%f, %f", spriteSize.width, spriteSize.height);
	//��õ�ǰ����ǰ�������ڵ�ͼ�еĸ���λ��
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	//log("character position: %f,%f", tiledPos.x, tiledPos.y);

	//��ȡ��ͼ���ӵ�Ψһ��ʶ
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//int tiledGid = meta->getTileGIDAt(playerRect);
	//log("%d", tiledGid);

	//��Ϊ0����������������
	if (tiledGid != 0) {
		/*
		��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
		����������meta��ģ���ͬʱҲ������������ͼ�ģ����Ի�ȡ���ӵ���������
		ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ�л��
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();
		//ȡ�ø��ӵ�colliable����ֵ
		//Value prop = properties.asValueMap().at("Collidable");

		////�ж�Collidable�����Ƿ�Ϊtrue������ǣ���������ƶ�
		//if (prop.asString().compare("true") == 0) {
		//	return;
		//}

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			//ȡ�ø��ӵ�Collidable����ֵ
			Value prop = propertiesMap.at("Collidable");
			//�ж�Collidableֵ�Ƿ�Ϊtrue,����ǣ������ƶ�
			if (prop.asString().compare("true") == 0) {
				return;
			}

		}
		if (propertiesMap.find("win") != propertiesMap.end()) {
			//ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ����л�����
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {

				auto listener = EventListenerKeyboard::create();

				listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
					if (keyCode == EventKeyboard::KeyCode::KEY_J) {
						//setiXSpeed(2);
						Director::getInstance()->replaceScene(HelloWorld::createScene());
					}


				};
				listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
					if (keyCode == EventKeyboard::KeyCode::KEY_J) {
						//setiXSpeed(0);
						Director::getInstance()->replaceScene(HelloWorld::createScene());
					}
				};
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			}
		}
	}


	Characters::setTagPosition(x, y);

	//������Ϊ�����ƶ���ͼ
	setViewPointByPlayer();

}

void Player::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;

	//����metaͼ�������
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);    //��Ҫ��ʾ
}

Point Player::pCollision(int x,int y)
{
	

	//��ȡ�������ӵĴ�С
	auto m_segment_width = m_map->getTileSize().width;
	auto m_segment_height = m_map->getTileSize().height;


	Size spriteSize = m_sprite->getContentSize();

	float X = x + spriteSize.width / 2, Y = y;

	//if (direction_x == 1 || direction_x == 2)
	//{
	//	X = x + spriteSize.width / 2 + m_segment_width / 4;
	//	//Y = y;
	//}
	//else if (direction_x == -1 || direction_x == -2)
	//{
	//	X = x + spriteSize.width / 4;
	//	//Y = y;
	//}
	//else
	//{
	//	X = x;
	//}
	//if (direction_y == -1)
	//{
	//	//X = x + spriteSize.width / 2 + m_segment_width / 4;
	//	Y = y - m_segment_height / 2 + spriteSize.height / 4;
	//}
	//else 
	//{
	//	//X = x + spriteSize.width / 4;
	//	Y = y;
	//}
	
	return Point(X, Y);
}

void Player::hitted(int attack)
{
	if (getSprite() == NULL)
	{
		return;
	}
	/*��ѪƮ����Ч*/
	//FlowWord* flowWord = FlowWord::create();
	//this->addChild(flowWord);
	//flowWord->showWord("-%d", attack, getSprite()->getPosition());
	if (m_defence > 0) {
		m_defence -= attack;
		if (m_defence < 0) {
			m_defence = 0;
		}
	}
	else {
		m_iHP -= attack;
	}

	if (m_iHP < 0) {
		m_iHP = 0;
	}

	//�������ֶ���
	auto backMove = MoveBy::create(0.1f, Point(-20, 0));
	auto forwardMove = MoveBy::create(0.1f, Point(20, 0));
	auto backRotate = RotateBy::create(0.1f, -5, 0);
	auto forwardRotate = RotateBy::create(0.1f, 5, 0);

	//��ϳ����ֶ���
	auto backActions = Spawn::create(backMove, backRotate, NULL);
	auto forwardActions = Spawn::create(forwardMove, forwardRotate, NULL);

	auto actions = Sequence::create(backActions, forwardActions, NULL);

	stopAllActions();  //��ֹ֮ͣǰ����
	//resetData();       //��������
	runAction(actions);//ִ�ж���
}

int Player::getiHP()
{
	return this->m_iHP;
}

int Player::getDefence()
{
	return this->m_defence;
}

int Player::getSpeed()
{
	return this->m_speed;
}



void Player::resetData()
{
	setScale(1.0f);
	setRotation(0);
}

//void Player::special_ground()
//{
//
//}

Point Player::tileCoordForPosition(Point pos)
{
	//Size mapTiledNum = m_map->getMapSize();  //��ȡ��ͼ��С
	//Size tiledSize = m_map->getTileSize();   //��ȡ���Ӵ�С


	//int x = pos.x / tiledSize.width;
	//log("%d", tiledSize.width);
	int x = pos.x / m_map->getContentSize().width * m_map->getMapSize().width;
	int y = m_map->getMapSize().height - pos.y /m_map->getContentSize().height * m_map->getMapSize().height;
	
	//cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ���������
	//int y =  ((mapTiledNum.height * tiledSize.height) - pos.y) / tiledSize.height;
	//int y =(1040- pos.y)/ tiledSize.height;
	//log("getMapSize:%f, %f", mapTiledNum.width, mapTiledNum.height);
	//log("getTileSize:%f, %f", tiledSize.width, tiledSize.height);
	//����������㿪ʼ����
	if (x > 0) {
		x -= 1;
	}
	if (y > 0) {
		y -= 0;
	}

	//log("%d,%d", x, y);
	return Point(x, y);
}
