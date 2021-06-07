#pragma once
#ifndef _Scene_battleMap_H_
#define _Scene_battleMap_H_
#include "Player.h"
#include "cocos2d.h"
//#include "Controller_Move.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
using namespace ui;
USING_NS_CC;
using namespace cocostudio;

/*游戏战斗界面*/
class Scene_battleMap :public Layer
{
public:
	static Scene* createScene();   //创建场景


	CREATE_FUNC(Scene_battleMap);

	virtual bool init();

	virtual void update(float dt);

	void addPlayer(TMXTiledMap* map);//将骑士加入地图

	void addPortal(TMXTiledMap* map);//将传送门加入地图

	void addMonster(TMXTiledMap* map);//添加怪物

	//void special_ground();   //特殊地板上的特殊行为
	void loadUI();

private:
	Player* m_player;

	int num_money;
	LoadingBar* m_hpBar;
	LoadingBar* m_mpBar;
	LoadingBar* m_defendBar;
};

#endif
