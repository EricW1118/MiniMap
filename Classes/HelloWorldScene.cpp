//
//  HelloWorldScene.cpp
//  aireTest
//
//  Created by lemon.Wang on 14-8-3.
//
//

#include "HelloWorldScene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld():
m_timeTick(0)
{
    
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("HelloWorld.png");
    bg->setScale(this->getContentSize().width / bg->getContentSize().width,
                 this->getContentSize().height / bg->getContentSize().height);
    bg->setColor(Color3B::ORANGE);
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(bg);
    
    
    m_gameLy = Layer::create();
    m_gameLy->setContentSize(Size(visibleSize.width, visibleSize.height * 4));
    addChild(m_gameLy, 1);
    
    
    m_hubLy = HubLayer::create();
    m_hubLy->setContentSize(Size(visibleSize.width * 0.25, visibleSize.height * 4 * 0.15));
    m_hubLy->setPosition(Vec2(1, (this->getContentSize().height - m_hubLy->getContentSize().height) / 2));
    addChild(m_hubLy, 1);
    
    m_hubLy->setgLayer(m_gameLy);
    
    
    auto lD = LayerColor::create(Color4B(255.0, 0, 0, 255.0),
                       visibleSize.width, 30);
    lD->setTag(10);
    
    lD->setPosition(Vec2(0, m_gameLy->getContentSize().height - lD->getContentSize().height));
    m_gameLy->addChild(lD);
    
    auto lP = LayerColor::create(Color4B(0, 255.0, 0, 255.0),
                                visibleSize.width, 30);
    m_gameLy->addChild(lP);
    lP->setTag(11);
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this](Touch *touch, Event *event)->bool
    {
        m_lastMove = this->convertTouchToNodeSpace(touch);
        return true;
    };
    

    touchListener->onTouchMoved = [this](Touch *touch, Event *event)
    {
        auto location = this->convertTouchToNodeSpace(touch);
       
        Vec2 v = Vec2(location.x - m_lastMove.x, location.y - m_lastMove.y);
        Vec2 des = m_gameLy->getPosition();
        des.add(v);
        m_gameLy->setPosition(boundeEdge(des));
        m_lastMove = location;
        
    };
    touchListener->onTouchEnded = [this](Touch *touch, Event *event){};
    
    touchListener->onTouchCancelled = [this](Touch *touch, Event *event){};
    
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    schedule(schedule_selector(HelloWorld::step));
    
    return true;
}


Vec2 HelloWorld::boundeEdge(const Vec2& pos) const
{
    Vec2 rpos = pos;
    rpos.x = MAX(rpos.x, getContentSize().width - m_gameLy->getContentSize().width);
    rpos.x = MIN(rpos.x, 0);
    
    rpos.y = MAX(rpos.y, getContentSize().height - m_gameLy->getContentSize().height );
    rpos.y = MIN(rpos.y, 0);
    return rpos;
}

void HelloWorld::step(float dt)
{
    m_timeTick += dt;
    
    if (m_timeTick > 2.0)
    {
        m_timeTick  = 0;
        
        int r = arc4random() % 2 ;
        auto s = LayerColor::create(Color4B(255 * r,
                                            255 * (r % 1),
                                            0,
                                            255.0), 30, 30);
        
        s->ignoreAnchorPointForPosition(false);
        s->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        m_gameLy->addChild(s);
        
        if (r)
        {
            s->setPosition(Vec2(CCRANDOM_0_1() * m_gameLy->getContentSize().width,
                                30 -  s->getContentSize().height / 2));
            
            auto ss = Sequence::create(MoveBy::create(15 + arc4random() % 5, Vec2(0, m_gameLy->getContentSize().height)),
                                      CallFuncN::create([this](Node* sender)
                                                        {
                                                            sender->removeFromParent();
                                                        }), NULL);
            s->runAction(ss);

        }
        else
        {
            s->setPosition(Vec2(CCRANDOM_0_1() * m_gameLy->getContentSize().width,
                                m_gameLy->getContentSize().height + s->getContentSize().height / 2));
            
            auto ss = Sequence::create(MoveBy::create(15 + arc4random() % 5, Vec2(0, -m_gameLy->getContentSize().height)),
                                       CallFuncN::create([this](Node* sender)
                                                         {
                                                             sender->removeFromParent();
                                                         }), NULL);
            s->runAction(ss);
        }
        
    }
}











