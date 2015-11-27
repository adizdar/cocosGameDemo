//
//  Piece.hpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//

#ifndef Piece_hpp
#define Piece_hpp

#include "Piece.hpp"
#include "cocos2d.h"
#include "Constants.hpp"

#include <stdio.h>

class Piece : public cocos2d::Node
{
private:
    cocos2d::Sprite* roll;
    
public:
    CREATE_FUNC(Piece);
    
    float getSpriteHeight();
    
    void setObstacleSide(Side obstacleSide);
    Side getObstacleSide();
    cocos2d::Sprite* getSpriteRoll();
    void setSpriteRoll(cocos2d::Sprite* roll);
    
protected:
    Side obstacleSide;
    
};
#endif /* Piece_hpp */
