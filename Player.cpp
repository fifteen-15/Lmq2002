#include "Player.h"


extern int direction_x, direction_y;

Player::Player()
{
	//初始化血量
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

	frameCache->addSpriteFramesWithFile("boys.plist", "boys.png");  //创建帧动画

	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;

	//创建精灵 ,对象，添加到列表里
	frameList.pushBack(cache->getSpriteFrameByName("boy_run1.png"));
	frameList.pushBack(cache->getSpriteFrameByName("boy_run2.png"));
	

	//集合记录后用来创建动画
	Animation* animation = Animation::createWithSpriteFrames(frameList);



	animation->setLoops(-1);
	//播放动画，此处为永远播放

	animation->setDelayPerUnit(0.1f);  //设置播放速度


	//创建动画动作
	Animate* animate = Animate::create(animation);

	//精灵执行动作
	m_sprite->runAction(animate);
	//addChild()


}



void Player::update(float dt)
{	
	float speed = 0.01f;
	auto action_right = Sequence::create(
		//ScaleTo::create(speed, -1.f, 1.f),  //水平翻转
		ScaleTo::create(speed, 1.f, 1.f),   //水平还原
		nullptr);

	auto action_left = Sequence::create(
		ScaleTo::create(speed, -1.f, 1.f),  //水平翻转
		//ScaleTo::create(speed, 1.f, 1.f),   //水平还原
		nullptr);

	extern int direction_x, direction_y;
	//log("%d", direction_x);
	if (direction_x == 1|| direction_x == 10)
	{
		m_sprite->runAction(action_right);

		if (direction_y == 0 || direction_y == 1)
			run();   //让角色跑
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


	//地图方块数量
	Size mapTiledNum = m_map->getMapSize();
	//log("get the mapTiledNum");

	//地图单个格子大小
	Size tiledSize = m_map->getTileSize();
	//log("get the tiledSize");

	//地图大小
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	//屏幕大小
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//主角坐标
	Point spritePos = getPosition();

	//如果主角坐标小于屏幕的一半，则取屏幕中点坐标
	//否则取主角坐标
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//float x = spritePos.x;
	//float y = spritePos.y;

	//如果x,y坐标大于右上角的极限值，则取极限值坐标
	//极限值指的是不让地图超出屏幕造成出现黑边的极限坐标
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//目标点
	Point destPos = Point(x, y);

	//屏幕中点
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	//Point centerPos = Vec2(Director::getInstance()->getVisibleSize() / 2);
	//计算屏幕中点和所移动的目的点之间的距离
	Point viewPos = centerPos - destPos;
	//log("viewPos");

	parent->setPosition(viewPos);

}

void Player::setTagPosition(int x, int y)
{
	/****************判断前面是否不可通行*****************/
	//取主角前方的坐标
	
	//Rect barrierRect = meta->getBoundingBox();

	//获取单个格子的大小
	auto m_segment_width = m_map->getTileSize().width;
	auto m_segment_height = m_map->getTileSize().height;
	//log("%f  ,%f", m_segment_width, m_segment_height);
	//Point dstPos = Point(x, y);
	Size spriteSize = m_sprite->getContentSize();
	//log("x,y：%d,%d", x, y);

	//Point dstPos = pCollision(x, y);
	Point dstPos = Point(x + spriteSize.width / 2, y);
	//log("pos:%f, %f", spriteSize.width, spriteSize.height);
	//获得当前主角前方坐标在地图中的格子位置
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	//log("character position: %f,%f", tiledPos.x, tiledPos.y);

	//获取地图格子的唯一标识
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//int tiledGid = meta->getTileGIDAt(playerRect);
	//log("%d", tiledGid);

	//不为0，代表存在这个格子
	if (tiledGid != 0) {
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性
		格子是属于meta层的，但同时也是属于整个地图的，所以获取格子的所有属性
		时，通过格子唯一标识在地图中获得
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();
		//取得格子的colliable属性值
		//Value prop = properties.asValueMap().at("Collidable");

		////判断Collidable属性是否为true，如果是，则不让玩家移动
		//if (prop.asString().compare("true") == 0) {
		//	return;
		//}

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			//取得格子的Collidable属性值
			Value prop = propertiesMap.at("Collidable");
			//判断Collidable值是否为true,如果是，则不让移动
			if (prop.asString().compare("true") == 0) {
				return;
			}

		}
		if (propertiesMap.find("win") != propertiesMap.end()) {
			//取得格子的win属性值，判断是否为true，如果是，则切换画面
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

	//以主角为中心移动地图
	setViewPointByPlayer();

}

void Player::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;

	//保存meta图层的引用
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);    //不要显示
}

Point Player::pCollision(int x,int y)
{
	

	//获取单个格子的大小
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
	/*扣血飘字特效*/
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

	//创建几种动作
	auto backMove = MoveBy::create(0.1f, Point(-20, 0));
	auto forwardMove = MoveBy::create(0.1f, Point(20, 0));
	auto backRotate = RotateBy::create(0.1f, -5, 0);
	auto forwardRotate = RotateBy::create(0.1f, 5, 0);

	//组合成两种动作
	auto backActions = Spawn::create(backMove, backRotate, NULL);
	auto forwardActions = Spawn::create(forwardMove, forwardRotate, NULL);

	auto actions = Sequence::create(backActions, forwardActions, NULL);

	stopAllActions();  //先停止之前动作
	//resetData();       //重置数据
	runAction(actions);//执行动作
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
	//Size mapTiledNum = m_map->getMapSize();  //获取地图大小
	//Size tiledSize = m_map->getTileSize();   //获取格子大小


	//int x = pos.x / tiledSize.width;
	//log("%d", tiledSize.width);
	int x = pos.x / m_map->getContentSize().width * m_map->getMapSize().width;
	int y = m_map->getMapSize().height - pos.y /m_map->getContentSize().height * m_map->getMapSize().height;
	
	//cocos2d-x的默认Y坐标是由下向上的，所以要做一个相减操作
	//int y =  ((mapTiledNum.height * tiledSize.height) - pos.y) / tiledSize.height;
	//int y =(1040- pos.y)/ tiledSize.height;
	//log("getMapSize:%f, %f", mapTiledNum.width, mapTiledNum.height);
	//log("getTileSize:%f, %f", tiledSize.width, tiledSize.height);
	//格子坐标从零开始计算
	if (x > 0) {
		x -= 1;
	}
	if (y > 0) {
		y -= 0;
	}

	//log("%d,%d", x, y);
	return Point(x, y);
}
