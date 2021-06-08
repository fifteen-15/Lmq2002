#include "Controller_Move.h"

//两个全局变量分别代表水平和垂直方向
//x：-1代表向左，1代表向右
//y：-1代表向下，1代表向上
//0代表不动
int direction_x = 0, direction_y = 0;

bool Controller_Move::init()
{
	this->m_iXSpeed = 0;
	this->m_iYSpeed = 0;
	direction_x = direction_y = 0;
	//初始化时，角色不能动，将速度设置为零

	//注册键盘事件
	registeKeyBoardEvent();


	//开启update函数的调用
	this->scheduleUpdate();

	return true;
}

void Controller_Move::update(float dt)
{
	if (m_controllerListener == NULL) {
		return;
	}
	//让移动对象在x和y方向上增加坐标,这就等同于移动了
	Point curPos = m_controllerListener->getTagPosition();

	curPos.x += m_iXSpeed;
	curPos.y += m_iYSpeed;
	//curPos = pCollision(curPos.x, curPos.y);

	//log("cur_position:%f ,%f", curPos.x, curPos.y);
	m_controllerListener->setTagPosition(curPos.x + m_iXSpeed, curPos.y + m_iYSpeed);
	
	//********为什么要加两次？？？
}

void Controller_Move::setiXSpeed(int iSpeed)
{
	this->m_iXSpeed = iSpeed;
}

void Controller_Move::setiYSpeed(int iSpeed)
{
	this->m_iYSpeed = iSpeed;
}


//void Controller_Move::bindPlayer(Player* player)
//{
//	m_player = player;
//}

void Controller_Move::registeKeyBoardEvent()
{
	auto listener = EventListenerKeyboard::create();

	int iSpeed = 0;
	

	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			setiXSpeed(2);
			direction_x = 1;
			//log("%d", direction_x);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			setiXSpeed(-2);
			direction_x = -1;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			setiYSpeed(2);
			direction_y = 1;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			setiYSpeed(-2);
			direction_y = 1;
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			setiXSpeed(0);
			direction_x = 10;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			setiXSpeed(0);
			direction_x = -10;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			setiYSpeed(0);
			direction_y = 0;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			setiYSpeed(0);
			direction_y = 0;
		}
		//direction_x = 0;
		//direction_y = 0;
		//setiYSpeed(0);
		//setiXSpeed(0);
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
