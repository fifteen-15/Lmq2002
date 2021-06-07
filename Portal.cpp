#include "Portal.h"

bool Portal::init()
{
	return true;
}

void Portal::act()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("portal.plist", "portal.png");  //����֡����

	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;

	//�������� ,������ӵ��б���
	frameList.pushBack(cache->getSpriteFrameByName("portal_1.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_2.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_3.png"));
	frameList.pushBack(cache->getSpriteFrameByName("portal_4.png"));
	//���ϼ�¼��������������
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	//���Ŷ������˴�Ϊ��Զ����
	animation->setDelayPerUnit(0.2f);  //���ò����ٶ�


	//������������
	Animate* animate = Animate::create(animation);

	//����ִ�ж���
	m_sprite->runAction(animate);
	//addChild()
}

//void Portal::setTiledMap(TMXTiledMap* map)
//{
//	this->m_map = map;
//}
