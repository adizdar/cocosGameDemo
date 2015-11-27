//
//  CharacterReader.hpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//

#ifndef CharacterReader_hpp
#define CharacterReader_hpp

#include <stdio.h>
#include "CharacterReader.hpp"
#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class  CharacterReader : public cocostudio::NodeReader
{
public:
    
    static CharacterReader* getInstance();
    static void purge();
    
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* CharacterReader_hpp */
