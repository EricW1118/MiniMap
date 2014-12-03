//
//  HubLayer.h
//  aireTest
//
//  Created by lemon.Wang on 14-8-3.
//
//

#ifndef __aireTest__HubLayer__
#define __aireTest__HubLayer__

#include "cocos2d.h"

using namespace cocos2d;

class HubLayer: public Layer
{
public:
    HubLayer();
    virtual bool init();
    CREATE_FUNC(HubLayer);
    CC_SYNTHESIZE(Layer*, m_gameLayer, gLayer);
    void onDraw(const Mat4 &transform, bool transformUpdated);
    virtual void draw(Renderer *renderer, const Mat4& transform, bool transformUpdated);
    virtual void onEnter();
    
protected:
     CustomCommand _customCommand;
};

#endif /* defined(__aireTest__HubLayer__) */
