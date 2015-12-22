#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
        glview = GLViewImpl::createWithRect("CocosProject1", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(640, 960, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
    
    std::vector<std::string> searchResolutionsOrder(1);
    
    cocos2d::Size targetSize = glview->getFrameSize();
    CCLOG("%f", targetSize.height);
    
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (targetSize.height > mediumResource.size.height)
    {
        searchResolutionsOrder[0] = "resources-3x";
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (targetSize.height > smallResource.size.height)
    {
        searchResolutionsOrder[0] = "resources-2x";
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        searchResolutionsOrder[0] = "resources-1x";
        
    }
    
//    if (targetSize.height < 481.0f)
//    {
//        searchResolutionsOrder[0] = "Assets/Images/resources-1xa";
//    }
//    else if (targetSize.height < 1137.0f)
//    {
//        searchResolutionsOrder[0] = "Assets/Images/resources-2xa";
//    }
//    else if (targetSize.height < 2047.0f)
//    {
//        searchResolutionsOrder[0] = "Assets/Images/resources-3xa";
//    }
//    else
//    {
//        searchResolutionsOrder[0] = "Assets/Images/resources-4xa";
//    }
    
    FileUtils::getInstance()->setSearchResolutionsOrder(searchResolutionsOrder);

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
