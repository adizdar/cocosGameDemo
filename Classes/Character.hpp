//
//  Character.hpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//


#ifndef __SushiNeko__Character__
#define __SushiNeko__Character__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Constants.hpp"

#include <stdio.h>

class Character : public cocos2d::Node
{
private:

public:
    CREATE_FUNC(Character);
    
    bool init() override;
    void onExit() override;
    void setSide(Side side);
    Side getSide();
    void runChopAnimation();
    
protected:
    Side side;
    cocostudio::timeline::ActionTimeline* timeline;
};

#endif /* defined(__SushiNeko__Character__) */