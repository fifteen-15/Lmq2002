#pragma once
#ifndef _MULTIMENU_H_
#define _MULTIMENU_H_
#include "cocos2d.h"
using namespace cocos2d;

class MultiMenu :
    public cocos2d::Scene
{
public:
    MultiMenu();
    ~MultiMenu();
    bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MultiMenu);
    //ending program
    void menuCloseCallBack(cocos2d::Ref* pSender);

};
#endif // !_MULTIMENU_H_
