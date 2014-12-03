
//  HubLayer.cpp
//  aireTest
//
//  Created by lemon.Wang on 14-8-3.
//
//

#include "HubLayer.h"

HubLayer::HubLayer():
m_gameLayer(nullptr)
{
    
}

bool HubLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}

void HubLayer::onEnter()
{
    Layer::onEnter();
    auto l = LayerColor::create(Color4B(100, 100, 100, 50), getContentSize().width, getContentSize().height);
    addChild(l);
}

void HubLayer::draw(Renderer *renderer, const Mat4& transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(HubLayer::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void HubLayer::onDraw(const Mat4 &transform, bool transformUpdated)
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    DrawPrimitives::setPointSize(1.0f);
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    DrawPrimitives::drawRect(Vec2::ZERO,Vec2(getContentSize().width, getContentSize().height));

    if(m_gameLayer)
    {
        DrawPrimitives::setDrawColor4B(0,255,255,255);
        auto gPos = m_gameLayer->getPosition();
        float inX = gPos.x;
        float iny = (-gPos.y / m_gameLayer->getContentSize().height) * getContentSize().height;
        
        
        DrawPrimitives::drawRect(Vec2(inX,iny),
                                 Vec2(inX + 640.0 / m_gameLayer->getContentSize().width * getContentSize().width,
                                      iny + 960.0 / m_gameLayer->getContentSize().height * getContentSize().height));
        
        
        DrawPrimitives::setPointSize(5);
        DrawPrimitives::setDrawColor4B(0,0,255,255);
        
        for (int i = 0; i < m_gameLayer->getChildren().size(); ++i)
        {
            auto c = m_gameLayer->getChildren().at(i);
            if (c->getTag() != 10 && c->getTag() != 11)
            {
                float x = (c->getPosition().x / m_gameLayer->getContentSize().width) * getContentSize().width;
                float y = (c->getPosition().y / m_gameLayer->getContentSize().height) * getContentSize().height;
                DrawPrimitives::drawPoint(Vec2(x, y));
            }
        }
    }

    //end draw
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
