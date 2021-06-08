#pragma once
#ifndef _Controller_H_
#define _Controller_H_
#include "cocos2d.h"
#include "controllerListener.h"

using namespace cocos2d;

class mController : public Node {
public:
	/*ÉèÖÃ¼àÌı¶ÔÏó*/
	void setControllerListener(controllerListener* controllerListener);

protected:
	controllerListener* m_controllerListener;
};

#endif