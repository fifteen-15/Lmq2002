#pragma once
#ifndef _Portal_H_
#define _Portal_H_
#include "Characters.h"

//using namespace cocos2d;


class Portal : public Characters {
public:
	CREATE_FUNC(Portal);
	virtual bool init();
	void act();
	//void setTiledMap(TMXTiledMap* map);

private:
	//TMXTiledMap* m_map;

};


#endif