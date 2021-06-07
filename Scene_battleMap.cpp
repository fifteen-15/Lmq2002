#include "Scene_battleMap.h"
#include "Controller_Move.h"
#include "Characters.h"
#include "Portal.h"
#include "Monster.h"


extern int direction_x, direction_y;

Scene* Scene_battleMap::createScene()
{
	//Size winSize = Director::getInstance()->getWinSize();
	auto scene = Scene::create();
	auto layer = Scene_battleMap::create();


	scene->addChild(layer);

	return scene;
}

bool Scene_battleMap::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!Layer::init())return false;

	Sprite* bg_UI = Sprite::create("menu_UI/background_UI.png");
	bg_UI->setPosition(Point(0, visibleSize.height));
	bg_UI->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg_UI->setScale(0.5f);
	this->addChild(bg_UI, 2);

	loadUI();

	this->scheduleUpdate();

	/*加载Tiled地图，添加到场景中*/
	TMXTiledMap* map = TMXTiledMap::create("battleMap_ice.tmx");
	//map->setScale(15/32);
	//map->getLayer("background");
	
	//Sprite* map = Sprite::create("battleMap_ice.png");
	//map->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//map->setContentSize(Size(4800, 6000));
	//map->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	//log("mapSize:%f,%f", map->getContentSize().width,map->getContentSize().height);
	//log("mapNum:%f,%f", map->getMapSize().width, map->getMapSize().height);
	//log("TiledSize:%f, %f", map->getTileSize().width, map->getTileSize().height);
	/******************************************
	此处显示地图大小错误
	是造成后面一系列错位原因的根本
	所在!!!!!!!!!!
	如何解决？？？？
	********************************************/


	this->addChild(map);

	addPlayer(map);  //加载骑士
	addPortal(map);  //加载传送门

	
	addMonster(map);

	//创建怪物管理器
	//MonsterManager* monsterMgr = MonsterManager::create();
	//this->addChild(monsterMgr, 4);

	return true;
}

void Scene_battleMap::update(float dt)
{
	m_defendBar->setPercent(m_player->getDefence() / 10.0f * 100);
	m_hpBar->setPercent(m_player->getiHP() / 10.0f * 100);
	log("Hp: %d", m_player->getiHP());
}



void Scene_battleMap::addPlayer(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建精灵
	Sprite* playerSprite = Sprite::create("boy_run1.png");

	//将精灵绑定到玩家对象上
	m_player = Player::create();
	m_player->bindSprite(playerSprite);
	m_player->setContentSize(Size(40, 40));
	//m_player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);


    //由于addPlayer函数只会调用一次，我们就用update不断更新，带到转向的目的
	//mPlayer->run();
	m_player->scheduleUpdate();
	
	//mPlayer->run();
	//log("dir %d", direction_x);
	//if (direction_x == 1)
	//{
	//	mPlayer->run();   //让角色跑
	//}
	//if (direction_x == -1)
	//{
	//	mPlayer->run_left();
	//}
	m_player->setTiledMap(map);

	//设置玩家坐标
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//加载玩家坐标对象
	ValueMap playerPointMap = objGroup->getObject("player_position");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	//log("player_position:%lf, %lf", playerPointMap.at("x"), playerPointMap.at("y"));
	/*********************************************
	* 
	此处位置信息获取错误！！！！！！
	player_position:346.874969, 918.749939

	************************************************/


	//mPlayer->setPosition(Point(100, visibleSize.height ));
	m_player->setPosition(Point(playerX, playerY));
	//mPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//创建玩家移动控制器
	Controller_Move* controller_move = Controller_Move::create();
	controller_move->setiXSpeed(0);
	controller_move->setiYSpeed(0);

	//添加到场景中
	this->addChild(controller_move);

	//设置控制器到主角身上
	m_player->setController(controller_move);

	//将玩家添加到地图,1代表层数
	map->addChild(m_player, 0);


	////添加到场景中
	//this->addChild(controller_move);
}

void Scene_battleMap::addPortal(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建精灵
	Sprite* portalSprite = Sprite::create("portal_1.png");

	//将精灵绑定到玩家对象上
	Portal* mPortal = Portal::create();
	mPortal->bindSprite(portalSprite);
	mPortal->act();
	//mPortal->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mPortal->setScale(1.5f);

	//设置传送门坐标
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//加载传送门坐标对象
	ValueMap portalMap = objGroup->getObject("portal");
	float portalX = portalMap.at("x").asFloat();
	float portalY = portalMap.at("y").asFloat();

	//mPortal->setTiledMap(map);

	mPortal->setPosition(Point(portalX, portalY));

	map->addChild(mPortal, 0);

}

void Scene_battleMap::addMonster(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	TMXObjectGroup* mstGroup = map->getObjectGroup("Monsters");

	ValueVector tempArray = mstGroup->getObjects();

	//float x, y, w, h;

	for each (Value mstPointMap in tempArray)
	{


		ValueMap mstPoint = mstPointMap.asValueMap();
		float posX = mstPoint.at("x").asFloat();
		float posY = mstPoint.at("y").asFloat();

		
		Point monsterPoint = Point(posX, posY);
	/*	posY -= this->getTileSize().height;
		Point tileXY = this->positionToTileCoord(ccp(posX, posY));
		std::string name = objPoint.at("name").asString();
		std::string type = objPoint.at("type").asString();*/

		std::string name = mstPoint.at("name").asString();
		std::string type = mstPoint.at("type").asString();

		if (name == "monster")
		{
			Monster* mMonster = NULL;
			if (type == "striker")
			{
				mMonster = Monster::create();
				//mMonster->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

				mMonster->bindPlayer(m_player);
				mMonster->bindSprite(Sprite::create("mst_scorer2.png"));

	
				//Point mstPoint;
				mMonster->setPosition(monsterPoint);
				map->addChild(mMonster, 1);

			}

		}
	}

}

void Scene_battleMap::loadUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//***************************************血条
	m_hpBar = LoadingBar::create();
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //设置显示位置,屏幕正中央
	this->addChild(m_hpBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //进度条

	//设置初始百分比
	m_hpBar->setPercent(100);

	//设置进度条朝向
	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_hpBar->setScale(0.5f);

	//*******************************************************护盾条
	m_mpBar = LoadingBar::create();
	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //设置显示位置,屏幕正中央
	this->addChild(m_mpBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //进度条

	//设置初始百分比
	m_mpBar->setPercent(100);

	//设置进度条朝向
	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_mpBar->setScale(0.5f);

	//***********************************************************蓝条
	m_defendBar = LoadingBar::create();
	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //设置显示位置,屏幕正中央
	this->addChild(m_defendBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //进度条

	//设置初始百分比
	m_defendBar->setPercent(100);

	//设置进度条朝向
	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_defendBar->setScale(0.5f);
}

//void Scene_battleMap::special_ground()
//{
//
//}
