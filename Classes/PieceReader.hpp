//
//  PieceReader.hpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//

#ifndef PieceReader_hpp
#define PieceReader_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "Piece.hpp"

class  PieceReader : public cocostudio::NodeReader
{
public:
    
    static PieceReader* getInstance();
    static void purge();
    
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* PieceReader_hpp */
