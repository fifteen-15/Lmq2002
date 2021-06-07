#include "Knight.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
USING_NS_CC;


Paladin::Paladin():
myPaladin(NULL),
normalLeft(NULL),
normalRight(NULL),
runLeft(NULL),
runRight(NULL),
dieLeft(NULL),
dieRight(NULL)
{
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Paladin.plist", "Paladin.png");
	myPaladin = Sprite::createWithSpriteFrameName("normalRight.png");
	dieLeft = Sprite::createWithSpriteFrameName("dieLeft.png");
	dieRight = Sprite::createWithSpriteFrameName("dieRight.png");

	auto texture = Director::getInstance()->getTextureCache()->addImage("normalLeft.png");
	normalLeft = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(
		Rect( texture->getPixelsWide() / 8, 0, texture->getPixelsWide() / 8, texture->getPixelsHigh())));
	normalLeft->retain();

	texture= Director::getInstance()->getTextureCache()->addImage("runLeft.png");
	runLeft= SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(
		Rect(texture->getPixelsWide() / 8, 0, texture->getPixelsWide() / 8, texture->getPixelsHigh())));
	runLeft->retain();

	texture = Director::getInstance()->getTextureCache()->addImage("normalRight.png");
	normalRight = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(
		Rect(texture->getPixelsWide() / 8, 0, texture->getPixelsWide() / 8, texture->getPixelsHigh())));
	normalRight->retain();

	texture = Director::getInstance()->getTextureCache()->addImage("runRight.png");
	runRight = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(
		Rect(texture->getPixelsWide() / 8, 0, texture->getPixelsWide() / 8, texture->getPixelsHigh())));
	runRight->retain();

	isLive = true;
	MP = MPMAX;
	AC = ACMAX;
	HP = HPMAX;
	speed = SPEED;
	score = 0;
	direction = Right;
	//position还没设值
	size = myPaladin->getContentSize();
}
//没考虑内存泄漏，与retain有关？
Paladin::~Paladin(){}

bool Paladin::getIsLive()
{
	return this->isLive;
}
void Paladin::setDead()
{
	isLive = false;
	return;
}

void Paladin::onEnter()
{
	Node::onEnter();
}
void Paladin::onExit()
{
	Node::onExit();
}

Paladin* Paladin::getPaladinInstance()
{
	return paladinInstance;
}
Paladin* Paladin::create()
{
	Paladin* pPaladin = new Paladin();
	if (pPaladin && pPaladin->init())
	{
		pPaladin->autorelease();
		return pPaladin;
	}
	CC_SAFE_DELETE(pPaladin);
	return NULL;
}

void Paladin::dieAnimation()
{
	if (getIsLive())
		return;
	removeChild(myPaladin);
	switch (direction)
	{
		case Left:
			addChild(dieLeft);
			break;
		case Right:
			addChild(dieRight);
			break;
	}
}

//待补充，待改善（loop设置）
void Paladin::runAnimation()
{
	Vector<SpriteFrame*>leftAnimation;
	leftAnimation.pushBack(normalLeft);
	leftAnimation.pushBack(runLeft);

	Vector<SpriteFrame*>rightAnimation;
	rightAnimation.pushBack(normalRight);
	rightAnimation.pushBack(runRight);

	//动画循环播放但是不知道怎么停止
	switch (direction)
	{
		case Left:
			Animation* animation = Animation::createWithSpriteFrames(leftAnimation);
			Animate* animate = Animate::create(animation);
			runAction(animate);
			break;
		case Right:
			Animation* animation = Animation::createWithSpriteFrames(rightAnimation);
			Animate* animate = Animate::create(animation);
			runAction(animate);
			break;
	}
}

//需要添加音效，所以不递归了
void Paladin::hit(int attack)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beAttack.wav");
	HP = HP - attack / ACMAX;
	AC = AC - attack % ACMAX;
	if (HP <= 0)
	{
		isLive = false;
	}
}

//根据碰撞检测判断，还没写，或许不用写……，而是在怪物那里写？
bool Paladin::isHit()
{

	return false;
}
//用到了isHit()
bool Paladin::isListenerAllowed()
{
	if(isHit())
		return false;
	return true;
}

void Paladin::bindEnermy(Sprite* attacker)
{
	enermy = attacker;
}

//实际上是一个闪烁的动画
void Paladin::born()
{
	myPaladin->runAction(Blink::create(2.0f, 10));
}

//待补充
void Paladin::reset()
{
	removeAllChildren();
	addChild(myPaladin);

	MP = MPMAX;
	AC = ACMAX;
	HP = HPMAX;
	speed = SPEED;
	score = 0;
	direction = Right;
}

//可能初始化函数是显形？不懂与constructor的区别
bool Paladin::init()
{
	addChild(myPaladin);


}