#include "Controller_Move.h"

//����ȫ�ֱ����ֱ����ˮƽ�ʹ�ֱ����
//x��-1��������1��������
//y��-1�������£�1��������
//0������
int direction_x = 0, direction_y = 0;

bool Controller_Move::init()
{
	this->m_iXSpeed = 0;
	this->m_iYSpeed = 0;
	direction_x = direction_y = 0;
	//��ʼ��ʱ����ɫ���ܶ������ٶ�����Ϊ��

	//ע������¼�
	registeKeyBoardEvent();


	//����update�����ĵ���
	this->scheduleUpdate();

	return true;
}

void Controller_Move::update(float dt)
{
	if (m_controllerListener == NULL) {
		return;
	}
	//���ƶ�������x��y��������������,��͵�ͬ���ƶ���
	Point curPos = m_controllerListener->getTagPosition();

	curPos.x += m_iXSpeed;
	curPos.y += m_iYSpeed;
	//curPos = pCollision(curPos.x, curPos.y);

	//log("cur_position:%f ,%f", curPos.x, curPos.y);
	m_controllerListener->setTagPosition(curPos.x + m_iXSpeed, curPos.y + m_iYSpeed);
	
	//********ΪʲôҪ�����Σ�����
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
