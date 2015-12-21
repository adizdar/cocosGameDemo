#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Piece.hpp"
#include "ui/CocosGUI.h"

// C++ forward declaration, better to forward declare
// the classes you need access to
// instead of including a source file into a header
// Doing that tells the compiler that there's a class called Character,
// so that you can use that type name in your method and instance variable declarations.
// It doesn't need to worry about what Character
// actually is until the implementation of MainScene.
class Character;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    void onPlayBtnTap();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

protected:
    Character* character;
    Side lastObstacleSide;
    Side getSideForObstacle(Side lastSide);
    
    void onEnter() override; // event for the scene after it has been created
    void update(float dt) override; // Update loops are a very common feature in games -
                                    // they allow you to execute certain sections of code right before each frame is rendered
    void setupTouchHandling();
    void stepTower();
    void resetGameState();
    void triggerPlaying();
    void triggerTitle();
    void triggerReady();
    void triggerGameOver();
    void toggleReadyAnimationEffect(bool hide);
    void setTimeLeft(float timeLeft);
    void triggerActionTimeline(std::string animationName, bool loop);
    void animateHitPiece(Side obstacleSide);

private:
    Node* pieceNode;
    cocos2d::Vector<Piece*> pieces;
    int pieceIndex; // -> tracks which piece in the pieces vector is at the bottom of the tower
    GameState gameState;
    cocos2d::ui::Text* scoreLabel;
    int score;
    
    void initNodeReader();
    void initGame(Node* rootNode);
    bool isGameOver();
    void setScore(int score);
    float timeLeft;
    cocos2d::Sprite* timeBar;
    cocos2d::Vec2 flyingPiecePosition;
    
};

#endif // __HELLOWORLD_SCENE_H__
