#include "MultiMenu.h"
USING_NS_CC;

Scene* MultiMenu::createScene()
{
	return MultiMenu::create();
}

void MultiMenu::menuCloseCallBack(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

bool MultiMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	/*start to creat some option button in the menu layer*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("menuBackground.jpg");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(origin.x, origin.y));
	addChild(background,0);

	auto startLabel = Label::createWithTTF("start", "fonts/agencyb.ttf",40);
	auto close = MenuItemImage::create("end1.png",
									   "end2.png",
									   CC_CALLBACK_1(MultiMenu::menuCloseCallBack, this));
	auto start = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MultiMenu::menuCloseCallBack, this));
	start->setColor(Color3B::RED);
	start->setAnchorPoint(Vec2(0.5, 0.5));
	start->setPosition(Vec2(150+origin.x+start->getContentSize().width/2 , 300+origin.y+start->getContentSize().height/2 ));
	close->setAnchorPoint(Vec2(-1, -1));
	auto menuEnd = Menu::create(close,start, NULL);
	menuEnd->setScale(0.5f);
	menuEnd->setAnchorPoint(Vec2(-1, -1));
	close->setPosition(Vec2(origin.x - close->getContentSize().width / 2,
							origin.y- close->getContentSize().height));
	addChild(menuEnd,1);



	return true;
}

MultiMenu::MultiMenu()
{
}
MultiMenu::~MultiMenu()
{
}