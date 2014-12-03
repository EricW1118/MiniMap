

//
//  HelloWorldScene.h
//  aireTest
//
//  Created by lemon.Wang on 14-8-3.
//
//


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HubLayer.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    
    HelloWorld();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    Vec2 boundeEdge(const Vec2& pos) const;
    
    void step(float dt);
    
protected:
    
    Layer* m_gameLy;
    HubLayer* m_hubLy;
    
    cocos2d::Vec2 m_lastMove;
    
    float m_timeTick;
    
};

#endif // __HELLOWORLD_SCENE_H__
