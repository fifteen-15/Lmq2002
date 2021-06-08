#include "Characters.h"

void Characters::bindSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);
}

Sprite* Characters::getSprite()
{
	return this->m_sprite;
}

void Characters::setController(mController* controller)
{
	this->m_controller = controller;

	m_controller->setControllerListener(this);
}

void Characters::setTagPosition(int x, int y)
{
	setPosition(Point(x, y));
}

Point Characters::getTagPosition()
{
	return getPosition();
}
