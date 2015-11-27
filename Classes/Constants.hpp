//
//  Constants.hpp
//  CocosProject1
//
//  Created by Ahmed Dizdar on 20/11/15.
//
//

#ifndef Constants_hpp
#define Constants_hpp

#include <stdio.h>

// the screen side of the caracter
enum class Side
{
    Left,
    Right,
    None
};

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver
};

#define ERROR_HANDLING(name) \
if(!name) {log("MainScene.cpp. Msg: Pointer is not defined, the pointer is nil"); \
return;}

#endif /* Constants_hpp */
