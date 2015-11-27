//
//  Character.cpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//
#include "Character.hpp"

using namespace cocos2d;

bool Character::init()
{
    if(!Node::init()) return false;

    this->side = Side::Left;
    this->timeline = CSLoader::createTimeline("Caracter.csb");
    
    // retain the character animation timeline so it doesn't get deallocated
    // memory management - for the most part Cocos2d-x does a good job of handling it for us.
    // But in this case, the retain() call is necessary to
    // ensure that timeline doesn't get deallocated.
    this->timeline->retain();
    
    return true;
}

void Character::onExit()
{
    // release the retain we called in init
    this->timeline->release();
    
    Node::onExit();
}

void Character::setSide(Side side)
{
    this->side = side;
    
    if(this->side == Side::Right)
        this->setScaleX(-1.0f);
    else
        this->setScaleX(1.0f);
}

Side Character::getSide()
{
    return this->side;
}

void Character::runChopAnimation()
{
    this->stopAllActions();
    this->runAction(this->timeline);
    
    this->timeline->play("chop", false);
}


