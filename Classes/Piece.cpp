//
//  Piece.cpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//

#include "Piece.hpp"
using namespace cocos2d;

/** 
  * To know the height of the sushi roll so that we can stack them on top of each other
  * getContentSize() returns the content size of the Node (0,0),
  * So we will grab the refereance of the child roll and with the height property get the size of the sushi roll
*/
float Piece::getSpriteHeight()
{
    // return the roll sprite's height
    return this->getSpriteRoll()->getContentSize().height;
    
}

void Piece::setObstacleSide(Side obstacleSide)
{
    Sprite* leftChopstick = this->getSpriteRoll()->getChildByName<Sprite*>("leftChopstick");
    Sprite* rightChopstick = this->getSpriteRoll()->getChildByName<Sprite*>("rightChopstick");

    this->obstacleSide = obstacleSide;
    
    switch (this->obstacleSide) {
        case Side::None:
            leftChopstick->setVisible(false);
            rightChopstick->setVisible(false);
            break;
            
        case Side::Left:
            leftChopstick->setVisible(true);
            rightChopstick->setVisible(false);
            break;
            
        case Side::Right:
            leftChopstick->setVisible(false);
            rightChopstick->setVisible(true);
            break;
            
        default:
            leftChopstick->setVisible(false);
            rightChopstick->setVisible(false);
            break;
    }
    
    
}

Side Piece::getObstacleSide()
{
    return this->obstacleSide;
}

void Piece::setSpriteRoll(cocos2d::Sprite *roll)
{
    this->roll = roll;
}

Sprite* Piece::getSpriteRoll()
{
    if (!this->roll) {
        // grab a reference to the roll sprite
        this->roll = this->getChildByName<Sprite*>("roll");
    }
    
    return this->roll;
}