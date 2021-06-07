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

	/*����Tiled��ͼ����ӵ�������*/
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
	�˴���ʾ��ͼ��С����
	����ɺ���һϵ�д�λԭ��ĸ���
	����!!!!!!!!!!
	��ν����������
	********************************************/


	this->addChild(map);

	addPlayer(map);  //������ʿ
	addPortal(map);  //���ش�����

	
	addMonster(map);

	//�������������
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

	//��������
	Sprite* playerSprite = Sprite::create("boy_run1.png");

	//������󶨵���Ҷ�����
	m_player = Player::create();
	m_player->bindSprite(playerSprite);
	m_player->setContentSize(Size(40, 40));
	//m_player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);


    //����addPlayer����ֻ�����һ�Σ����Ǿ���update���ϸ��£�����ת���Ŀ��
	//mPlayer->run();
	m_player->scheduleUpdate();
	
	//mPlayer->run();
	//log("dir %d", direction_x);
	//if (direction_x == 1)
	//{
	//	mPlayer->run();   //�ý�ɫ��
	//}
	//if (direction_x == -1)
	//{
	//	mPlayer->run_left();
	//}
	m_player->setTiledMap(map);

	//�����������
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//��������������
	ValueMap playerPointMap = objGroup->getObject("player_position");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	//log("player_position:%lf, %lf", playerPointMap.at("x"), playerPointMap.at("y"));
	/*********************************************
	* 
	�˴�λ����Ϣ��ȡ���󣡣���������
	player_position:346.874969, 918.749939

	************************************************/


	//mPlayer->setPosition(Point(100, visibleSize.height ));
	m_player->setPosition(Point(playerX, playerY));
	//mPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//��������ƶ�������
	Controller_Move* controller_move = Controller_Move::create();
	controller_move->setiXSpeed(0);
	controller_move->setiYSpeed(0);

	//��ӵ�������
	this->addChild(controller_move);

	//���ÿ���������������
	m_player->setController(controller_move);

	//�������ӵ���ͼ,1�������
	map->addChild(m_player, 0);


	////��ӵ�������
	//this->addChild(controller_move);
}

void Scene_battleMap::addPortal(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��������
	Sprite* portalSprite = Sprite::create("portal_1.png");

	//������󶨵���Ҷ�����
	Portal* mPortal = Portal::create();
	mPortal->bindSprite(portalSprite);
	mPortal->act();
	//mPortal->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mPortal->setScale(1.5f);

	//���ô���������
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//���ش������������
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
	//***************************************Ѫ��
	m_hpBar = LoadingBar::create();
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //������ʾλ��,��Ļ������
	this->addChild(m_hpBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_hpBar->setPercent(100);

	//���ý���������
	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_hpBar->setScale(0.5f);

	//*******************************************************������
	m_mpBar = LoadingBar::create();
	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //������ʾλ��,��Ļ������
	this->addChild(m_mpBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_mpBar->setPercent(100);

	//���ý���������
	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_mpBar->setScale(0.5f);

	//***********************************************************����
	m_defendBar = LoadingBar::create();
	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //������ʾλ��,��Ļ������
	this->addChild(m_defendBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_defendBar->setPercent(100);

	//���ý���������
	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_defendBar->setScale(0.5f);
}

//void Scene_battleMap::special_ground()
//{
//
//}
