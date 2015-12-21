#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CharacterReader.hpp"
#include "PieceReader.hpp"
#include "Character.hpp"
#include "Constants.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initNodeReader();

    auto rootNode = CSLoader::createNode("MainScene.csb");
    auto gameOverSprite = rootNode->getChildByName("mat");
    Button* playButton = static_cast<Button*>(gameOverSprite->getChildByName("play"));

    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    this->initGame(rootNode);
    
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::onPlayBtnTap, this));
    
    addChild(rootNode);
    
    return true;
}

// In order to start detect the touch events we need to wait for the scenen to be initialize
// with onEnter event we can achive this
void MainScene::onEnter()
{
    Layer::onEnter(); // call super class implementation so it can init it self first
    
    this->flyingPiecePosition = this->pieceNode->getPosition();
    
    this->setupTouchHandling();
    this->triggerTitle();
    this->scheduleUpdate(); // trigger update loop
}

void MainScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        // get the location of the touch in the MainScene's coordinate system
        Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
        
        if (this->gameState == GameState::GameOver) return true;
        
        switch (this->gameState) {
                
            case GameState::Title:
                this->triggerReady();
                break;
                
            case GameState::Ready:
                this->triggerPlaying();
                
            case GameState::Playing:
                this->character->runChopAnimation();
                break;
                
            case GameState::GameOver:
                this->resetGameState();
                this->triggerReady();
                break;
                
        }
        
        // check if the touch was on the left or right side of the screen
        // move the character to the appropriate side
        if (touchLocation.x < this->getContentSize().width / 2.0f)
        {
            this->character->setSide(Side::Left);
        }
        else
        {
            this->character->setSide(Side::Right);
        }
        
        if (this->isGameOver())
        {
            this->triggerGameOver();
            return true;
        }
        
        this->setScore(++this->score);
        this->setTimeLeft(this->timeLeft+0.25);
        this->character->runChopAnimation();
        this->stepTower();
    
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Side MainScene::getSideForObstacle(Side lastSide)
{
    float randomInterval = 0.0f;
    
    if(lastSide != Side::None) {
        return Side::None;
    } else {
        randomInterval = CCRANDOM_0_1();
        
        return (randomInterval < 0.45f) ? Side::Right :
               (randomInterval < 0.9f) ? Side::Left :
                Side::None;
    }
}

void MainScene::initNodeReader()
{
    CSLoader* instance = CSLoader::getInstance(); // -> Cocos Studio instance loader

    // Register the readers for our custom classes, type casting to ObjectFactory, WITHOUT IT WILL BREAK ROOT NODE
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("PieceReader", (ObjectFactory::Instance) PieceReader::getInstance);
}

void MainScene::initGame(Node* rootNode)
{
    Piece *piece = nullptr; // -> piece instance for the sushi tower
    float rollHeight;
    
    auto lifeBG = rootNode->getChildByName("lifeBG");
    ERROR_HANDLING(lifeBG);
    
    this->timeBar = lifeBG->getChildByName<Sprite*>("lifeBar");
    ERROR_HANDLING(this->timeBar);

    this->pieceIndex = 0;
    this->gameState = GameState::Title;
    this->scoreLabel = rootNode->getChildByName<ui::Text*>("scoreLabel");
    
    // grabs a reference to the Node labeled character in Cocos Studio
    this->character = rootNode->getChildByName<Character*>("caracter");
    
    ERROR_HANDLING(this->character);
    
    // initializing lastObstacleSide to the value Left
    this->lastObstacleSide = Side::Left;
    
    //  grabs a reference to the Node labeled pieceNode in Cocos Studio and saves it in the variable pieceNode
    this->pieceNode = rootNode->getChildByName("pieceNode");
    
    // create the sushi tower
    for (int i = 0; i < 10; i++) {
        
        // because CSLoader::createNode returns a Node object
        // we need to downcast it to Piece
        piece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));
        
        if(!piece) {
            log("MainScene.cpp -> piece. Msg: Piece is not defined, the pointer is nil");
            break;
        }
        
        rollHeight = piece->getSpriteHeight();
        
        // divide by 2.0f because we don't want the rolls to be evenly spaced
        // without overlapping - we want them to be stacked on top of each other
        piece->setPosition(0.0f, rollHeight/2.0f * i);
        
        // set the chopstick side
        this->lastObstacleSide = this->getSideForObstacle(this->lastObstacleSide);
        piece->setObstacleSide(this->lastObstacleSide);
        
        // add the piece to both the pieceNode and the piece Vector
        this->pieceNode->addChild(piece);
        this->pieces.pushBack(piece);
        
    }
    
    this->resetGameState();

}

void MainScene::stepTower()
{
    Piece* currentPiece = this->pieces.at(this->pieceIndex);
    float pieceHeight = currentPiece->getSpriteHeight()/2.0f;
    MoveBy* moveAction;

    this->animateHitPiece(currentPiece->getObstacleSide());
    
    // move the lowest piece to the top of the tower
    // this can also be written as ( currentPiece->getPosition() + Vec2(0.0f, ...),
    // because getPosition returns a vector and we sum another vector to it)
    // also the positionX is not 0 becuase the original position of the piece
    // is set on the map in the middle so its 320px, and because we dont want to specify
    // this size we let it to be automaticly set by the position so if we change the
    //position it will update it self
    currentPiece->setPosition(currentPiece->getPositionX(), pieceHeight * (float)this->pieces.size() + currentPiece->getPositionY());
    
    // set the zOrder of the piece so that it appears on top of the others
    currentPiece->setLocalZOrder(currentPiece->getLocalZOrder() + 1);
    
    // set the side of the obstacle, based on the side of the obstacle of the piece right before this one
    //because it is on the top it will generate new random ones
    currentPiece->setObstacleSide(this->getSideForObstacle(this->lastObstacleSide));
    this->lastObstacleSide = currentPiece->getObstacleSide();
    
    // move pieceNode down so that the whole tower moves down
    // this is same as the position code this->pieceNode->getPosition() + Vec2(0.0f, -pieceHeight)
    // but the get position is automaticly added to the new Vec2 so we can ignore it
    moveAction = MoveBy::create(0.15f, Vec2(0.0f, -pieceHeight));
    
//    this->pieceNode->setPosition(this->pieceNode->getPositionX(), this->pieceNode->getPositionY()- pieceHeight);
    
//    this->pieceNode->setPosition(this->pieceNode->getPosition() + Vec2(0.0f, -pieceHeight));
    
    this->pieceNode->runAction(moveAction);
    
    // change the index referencing the lowest piece
    this->pieceIndex = (this->pieceIndex + 1) % 10;
    
    if (this->isGameOver())
    {
        this->triggerGameOver();
    }
}

bool MainScene::isGameOver()
{
    return this->character->getSide() == this->pieces.at(pieceIndex)->getObstacleSide();
}

void MainScene::triggerPlaying()
{
    this->gameState = GameState::Playing;
    this->toggleReadyAnimationEffect(true);
}

void MainScene::triggerReady()
{
    this->gameState = GameState::Ready;
    this->triggerActionTimeline("ready", true);
    this->toggleReadyAnimationEffect(false);
}

void MainScene::triggerGameOver()
{
    this->gameState = GameState::GameOver;
    this->setTimeLeft(0);
    
    // get a reference to the top-most node
    auto scene = this->getChildByName("Scene");
    Sprite* gameOverScreen = dynamic_cast<Sprite*>(scene->getChildByName("mat"));
    
    // get a reference to the game over score label
    Text* gameOverScoreLabel = gameOverScreen->getChildByName<Text*>("gameOverScoreLabel");
    
    // set the score label to the user's score
    gameOverScoreLabel->setString(std::to_string(this->score));
    
    // load and run the game over animations
   // this->stopAllActions();
    triggerActionTimeline("gameOver", false);
}

void MainScene::triggerTitle()
{
    this->gameState = GameState::Title;
    this->triggerActionTimeline("title", false);
}

// makes sure that the lowest piece doesn't have an obstacle on it,
// so that if the game ended with the character colliding with an
// obstacle then the next game won't start in a bad state.
void MainScene::resetGameState()
{
    this->pieces.at(this->pieceIndex)->setObstacleSide(Side::None);
    this->score = 0;
    this->setTimeLeft(5);
}

void MainScene::setScore(int score)
{
    this->score = score;
    this->scoreLabel->setString(to_string(score));
}

void MainScene::setTimeLeft(float timeLeft)
{
    // clamp the time left timer to between 0 and 10 seconds
    this->timeLeft = clampf(timeLeft, 0.0f, 10.0f);
    
    // update the UI to reflect the correct time left
    // if there's 5 seconds left, that's divided by 10,
    // resulting in the timeBar being scaled to half of its original width.
    this->timeBar->setScaleX(timeLeft / 10.0f);
}

void MainScene::update(float dt)
{
    // dt is deltaTime, amount of time, in seconds, that has
    // elapsed since the last time update() was called
    Layer::update(dt);
    
    if (this->gameState == GameState::GameOver) return;
    
    this->setTimeLeft(this->timeLeft-dt);
    
    if (!this->timeLeft) this->triggerGameOver();
    
}

void MainScene::triggerActionTimeline(string animationName, bool loop)
{
    // we pass "MainScene.csb" to the constructor
    // so this ActionTimeline will be able to play any of the animations
    // that we've created in MainScene.csd
    ActionTimeline* timeline = CSLoader::createTimeline("MainScene.csb");
    ERROR_HANDLING(timeline);
    
    //this->stopAllActions(); // cancel any currently running actions on MainScene
    this->runAction(timeline); // we tell MainScene to run the timeline
    timeline->play(animationName, loop);
    
}

void MainScene::toggleReadyAnimationEffect(bool hide)
{
    auto rootScene = this->getChildByName("Scene"); // get a reference to the top-most node
    
    ERROR_HANDLING(rootScene);
    
    // get references to the left and right tap sprite
    Sprite* tapLeft = rootScene->getChildByName<Sprite*>("tapLeft");
    Sprite* tapRight = rootScene->getChildByName<Sprite*>("tapRight");
    
    ERROR_HANDLING(tapLeft);
    ERROR_HANDLING(tapRight);
    
    // create two fade actions
    // we can't create one and reuse it because a action can't be reused on two elements
    if (hide) {
        FadeOut* fadeLeft = FadeOut::create(0.35f);
        FadeOut* fadeRight = FadeOut::create(0.35f);
        
        // run the fade actions
        tapLeft->runAction(fadeLeft);
        tapRight->runAction(fadeRight);
    } else {
        tapLeft->setOpacity(255);
        tapRight->setOpacity(255);
    }
}

void MainScene::animateHitPiece(Side obstacleSide)
{
    Piece* flyingPiece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));
    ActionTimeline* pieceTimeline = CSLoader::createTimeline("Piece.csb");
    
    flyingPiece->setObstacleSide(obstacleSide);
    flyingPiece->setPosition(this->flyingPiecePosition);
    
    this->addChild(flyingPiece);
    this->runAction(pieceTimeline);
    
    switch (this->character->getSide()) {
        case Side::Left:
            pieceTimeline->play("moveRight", false);
            break;
        case Side::Right:
            pieceTimeline->play("moveLeft", false);
            break;
        default:
            break;
    }
    
    // on the last frame of the animation, remove the piece from the scene
    pieceTimeline->setLastFrameCallFunc([this, &flyingPiece]() {
        this->removeChild(flyingPiece);
    });
    
}

void MainScene::onPlayBtnTap(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    this->resetGameState();
    this->triggerReady();
}
















