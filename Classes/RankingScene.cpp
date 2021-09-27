#include "RankingScene.h"
#include "ui/UIButton.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

extern int score;
extern int width;
extern int height;
extern float heightBlock;
using namespace CocosDenshion;
//using namespace ui;
USING_NS_CC;

Scene* RankingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RankingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool RankingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg);

    
    log("score : %d", score);
    log("%d %d", width, height);
    auto Label1 = Label::createWithTTF("Your Score!", "fonts/DungGeunMo.ttf", 40);
    Label1->setTextColor(Color4B::BLUE);
    Label1->setPosition(Vec2((width/2), (height/2)+(heightBlock * 2)));
   
    char scoretemp[50] = { '\0' , };
    sprintf(scoretemp, "%d", score);
    auto Label2 = Label::createWithTTF(scoretemp, "fonts/DungGeunMo.ttf", 30);
    Label2->setTextColor(Color4B::ORANGE);
    Label2->setPosition(Vec2((width / 2), (height / 2) - (heightBlock * 1)));
    
    this->addChild(Label2);
    this->addChild(Label1);
   
    auto RetryButton = ui::Button::create("Retry.png");
    RetryButton->setPosition(Vec2((width / 2), (height / 2) - (heightBlock * 5)));
    this->addChild(RetryButton);
    RetryButton->addTouchEventListener(CC_CALLBACK_2(RankingScene::Retry, this));

    return true;
}
void RankingScene::Retry(Ref* sender, cocos2d::ui::Widget::TouchEventType Type)
{
    switch (Type)
    {
    case cocos2d::ui::Widget::TouchEventType::BEGAN:
    {
        Scene * returnS = Game::createScene();
        Director::getInstance()->replaceScene(returnS);
        break;
    }
    }
}

void RankingScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
