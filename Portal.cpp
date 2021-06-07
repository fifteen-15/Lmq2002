#include "Portal.h"

bool Portal::init()
{
	return true;
}

void Portal::act()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("portal.plist", "portal.png");  //创建帧动画

	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;

	//创建精灵 ,对象，添加到列表里
	frameList.pushBack(cache->getSpriteFrameByName("portal_1.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_2.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_3.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_4.png"));
	//集合记录后用来创建动画
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	//播放动画，此处为永远播放
	animation->setDelayPerUnit(0.2f);  //设置播放速度


	//创建动画动作
	Animate* animate = Animate::create(animation);

	//精灵执行动作
	m_sprite->runAction(animate);
	//addChild()
}

//void Portal::setTiledMap(TMXTiledMap* map)
//{
//	this->m_map = map;
//}
