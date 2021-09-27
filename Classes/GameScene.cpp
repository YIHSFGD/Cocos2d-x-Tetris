/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "cocos2d.h"
#include "RankingScene.h"
#include "ui/UIButton.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
#define PREVIEW 20
USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// 전역변수
int TryCount = 1;
int width = 270;
int height = 480;
int mapX = 12, mapY = 30;
float widthBlock = 16;
float heightBlock = widthBlock;
float blankX = 0;
float blankY = ((height / 4) / 2) + widthBlock * 7;
int score = 0;
int line = 0;
int blockForm = 0;
int blockRotation = 0;
int NextblockForm = 0;
int NextblockRotation = 0;
int initX = widthBlock * 5;
int initY = height;
int x = initX, y = height;
int gameXInit = 5;
int gameYInit = 0;
int gameX = 5;
int gameY = 0;
int randomCut = 0;
int count = 0;
int TimeCount = 0;
int minus = 0;
int TimeOverBlock = 60;
float nextX = 28.5, nextY = 5;
int BlockSize = 8;
int nColor = 3;
int NextColor = 3;
int TimeC = 0;
int startC = 0;
int gameOverLoop = 0;
int GameOverTimer = 0;
int FirstHoldBlockCount = 0;
int HoldBlock = 0;
int HoldCount = 0;
int Holdon = 0;
int HoldColor = 3;
int level = 1;
int DownDropTime = 60;
int Pause = 0;
int keyout = 0;
bool BlockMoved = false;
int MovedCount = 0;
int StartCurrX = 0;
int StartCurrY = 0;
int StartPos_X;
int StartPos_Y;
int StartPos_X2;
int StartPos_Y2;
int m, m2;
int stop = 0;
int stop2 = 0;
int  StartPos_X3 = 0;
int  StartPos_Y3 = 0;

// 블럽 4차원 배열
int block[7][4][4][4] = {

        { // ㅗ모양 블럭
                {
                        {0,0,0,0},
                        {0,1,0,0},
                        {1,1,1,0}, // ㅗ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,0,0}, // ㅏ
                        {0,1,1,0},
                        {0,1,0,0}
                },
                {
                        {0,0,0,0},
                        {0,0,0,0}, // ㅜ
                        {1,1,1,0},
                        {0,1,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,0,0},
                        {1,1,0,0}, // ㅓ
                        {0,1,0,0}
                }
        },

        {    //    ㅁㅁ 모양
                {// ㅁㅁ
                        {0,0,0,0},
                        {0,1,1,0},//   ㅁㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {1,0,0,0},// ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,1,0,0} //   ㅁ
                },
                {
                        {0,0,0,0},
                        {0,1,1,0},//   ㅁㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {1,0,0,0},// ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,1,0,0}//    ㅁ
                }
        },
        {   // ㅣㅣ 블럭 반대
                {
                        {0,0,0,0},
                        {1,1,0,0},// ㅁㅁ
                        {0,1,1,0},//   ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,0,0},//   ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {1,0,0,0} // ㅁ
                },
                {
                        {0,0,0,0},
                        {1,1,0,0},// ㅁㅁ
                        {0,1,1,0},//   ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,0,0},//   ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {1,0,0,0} // ㅁ
                }
        },
        {   // 1자 블럭
                {
                        {0,0,1,0}, // ㅁ
                        {0,0,1,0}, // ㅁ
                        {0,0,1,0}, // ㅁ
                        {0,0,1,0}  // ㅁ
                },
                {
                        {0,0,0,0},
                        {0,0,0,0},
                        {1,1,1,1}, // ㅁㅁㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,1,0,0},// ㅁ
                        {0,1,0,0},// ㅁ
                        {0,1,0,0},// ㅁ
                        {0,1,0,0} // ㅁ
                },
                {
                        {0,0,0,0},
                        {1,1,1,1},
                        {0,0,0,0}, // ㅁㅁㅁㅁ
                        {0,0,0,0}
                }
        },

        {   // L자 블럭
                {
                        {0,0,0,0},
                        {1,0,0,0},// ㅁ
                        {1,1,1,0},// ㅁㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {1,1,0,0},// ㅁㅁ
                        {1,0,0,0},// ㅁ
                        {1,0,0,0}//  ㅁ
                },
                {
                        {0,0,0,0},
                        {1,1,1,0}, // ㅁㅁㅁ
                        {0,0,1,0}, //     ㅁ
                        {0,0,0,0}
                },
                {
                        {0,1,0,0},//   ㅁ
                        {0,1,0,0},//   ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,0,0,0}
                }
        },
        {   // L자 블럭 반대
                {
                        {0,0,0,0},
                        {0,0,1,0},//     ㅁ
                        {1,1,1,0},// ㅁㅁㅁ
                        {0,0,0,0}
                },
                {
                        {1,0,0,0},// ㅁ
                        {1,0,0,0},// ㅁ
                        {1,1,0,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {1,1,1,0},// ㅁㅁㅁ
                        {1,0,0,0},// ㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {1,1,0,0},// ㅁㅁ
                        {0,1,0,0},//   ㅁ
                        {0,1,0,0} //   ㅁ
                }
        },

        {   // 네모
                {
                        {0,0,0,0},
                        {0,1,1,0},// ㅁㅁ
                        {0,1,1,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,1,0},// ㅁㅁ
                        {0,1,1,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,1,0},// ㅁㅁ
                        {0,1,1,0},// ㅁㅁ
                        {0,0,0,0}
                },
                {
                        {0,0,0,0},
                        {0,1,1,0},// ㅁㅁ
                        {0,1,1,0},// ㅁㅁ
                        {0,0,0,0}
                }
        }
};

int BlockBG[6][6] =
{
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1}
};

int ScoreBG[4][6] =
{
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1},
};

int Tetrismap[30][12] = {
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {-1,0,0,0,0,0,0,0,0,0,0,-1},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

FILE* fp;

// on "init" you need to initialize your instance
bool Game::init()
{
    fp = fopen("C:\\Users\\USER\\Desktop\\APK\\TetrisPorting\\Proj\\점수\\점수.txt", "wt");
    fprintf(fp, "");
    fclose(fp);
    fp = fopen("C:\\Users\\USER\\Desktop\\APK\\TetrisPorting\\Proj\\점수\\점수.txt", "at");
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (!(Tetrismap[i][j] == -1 || Tetrismap[i][j] == 2))
            {
                Tetrismap[i][j] = 0;
            }
        }
    }
    width = 270;
    height = 480;
    mapX = 12, mapY = 30;
    widthBlock = 16;
    heightBlock = widthBlock;
    blankX = 0;
    blankY = ((height / 4) / 2) + widthBlock * 7;
    score = 0;
    line = 0;
    blockForm = 0;
    blockRotation = 0;
    NextblockForm = 0;
    NextblockRotation = 0;
    initX = widthBlock * 5;
    initY = height;
    x = initX, y = height;
    gameXInit = 5;
    gameYInit = 0;
    gameX = 5;
    gameY = 0;
    randomCut = 0;
    count = 0;
    TimeCount = 0;
    minus = 0;
    TimeOverBlock = 60;
    nextX = 28.5, nextY = 5;
    BlockSize = 8;
    nColor = 3;
    NextColor = 3;
    TimeC = 0;
    startC = 0;
    gameOverLoop = 0;
    GameOverTimer = 0;
    FirstHoldBlockCount = 0;
    HoldBlock = 0;
    HoldCount = 0;
    Holdon = 0;
    HoldColor = 3;
    level = 1;
    DownDropTime = 60;
    Pause = 0;
    BlockMoved = false;
    MovedCount = 0;
    StartCurrX = 0;
    StartCurrY = 0;
    StartPos_X;
    StartPos_Y;
    StartPos_X2;
    StartPos_Y2;

    //////////////////////////////
    // 1. super init first
    
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 블럭 노드
    PauseSprite = Sprite::create("Pause.png");
    PauseSprite->setPosition(Vec2((widthBlock * 6), height - (heightBlock * 10)));
    PauseSprite->setVisible(0);
    this->addChild(PauseSprite, 51);

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BackGround.mp3", true);

    BlockDraw = DrawNode::create();
    PreviewDraw = DrawNode::create();
    MainShape = DrawNode::create();
    NextBlockShape = DrawNode::create();
    HoldBlockShape = DrawNode::create();
    LineDrawRect = DrawNode::create();
    LevelDrawRect = DrawNode::create();
    ScoreDraw = DrawNode::create();

    LevelLabel = Label::create();
    Score = Label::create();
    lineLabel = Label::create();

    nextX = 26, nextY = 46.5;
    for (int row = 0; row < 4; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (ScoreBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                LevelDrawRect->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }
    LevelDrawRect->setLineWidth(30);

    LevelDrawRect->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
        (height - (nextY * BlockSize)) - (BlockSize * 4)), Color4F::ORANGE);
    LevelDrawRect->setLineWidth(1);
    this->addChild(LevelDrawRect,10);

    auto PauseButton = ui::Button::create("PauseButton.png");
    PauseButton->setPosition(Vec2((width - (widthBlock * 2.5) + 5), heightBlock * 2.5));
    this->addChild(PauseButton);
    PauseButton->addTouchEventListener(CC_CALLBACK_2(Game::pauseButton, this));

    nextX = 26, nextY = 27;
    for (int row = 0; row < 4; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (ScoreBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                NextBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }

    ScoreDraw->setLineWidth(30);

    NextBlockShape->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
        (height - (nextY * BlockSize)) - (BlockSize * 4)), Color4F::RED);
    ScoreDraw->setLineWidth(1);
    this->addChild(ScoreDraw);

    nextX = 29, nextY = 4;
    nextLabel = Label::createWithTTF("NEXT", "fonts/CookieRun Black.ttf", 20);
    nextLabel->setTextColor(Color4B(255,120,40,255));
    nextLabel->setPosition(Vec2(nextX * BlockSize, height - (nextY * BlockSize)));
    nextLabel->enableOutline(Color4B::WHITE, 4);
    this->addChild(nextLabel,40);
    nextLabel->getFontAtlas()->setAliasTexParameters();

    nextX = 29, nextY = 15;
    holdLabel = Label::createWithTTF("HOLD", "fonts/CookieRun Black.ttf", 20);
    holdLabel->setTextColor(Color4B(255,80,140,255));
    holdLabel->setPosition(Vec2(nextX * BlockSize, height - (nextY * BlockSize)));
    holdLabel->enableOutline(Color4B::WHITE, 4);
    this->addChild(holdLabel,40);
    holdLabel->getFontAtlas()->setAliasTexParameters();


    nextX = 26, nextY = 16;
    DrawNode* HideBlank = DrawNode::create();
    HideBlank->drawSolidRect(Vec2(nextX * BlockSize, height - (nextY * BlockSize)), Vec2((nextX * BlockSize) + BlockSize * 3, height - (nextY * BlockSize) + BlockSize * 2), Color4F::WHITE);
    nextX = 28, nextY = 27.5;
    HideBlank->drawSolidRect(Vec2(nextX * BlockSize, height - (nextY * BlockSize)), Vec2((nextX * BlockSize) + BlockSize * 3, height - (nextY * BlockSize) + BlockSize * 2), Color4F::WHITE);
  
    nextX = 29, nextY = 26;
    ScoreLabel = Label::createWithTTF("SCORE", "fonts/CookieRun Black.ttf", 18);
    ScoreLabel->setTextColor(Color4B(0,100,230,255));
    ScoreLabel->setPosition(Vec2((nextX * BlockSize), (height - (nextY * BlockSize))));
    ScoreLabel->enableOutline(Color4B::WHITE, 4);
    this->addChild(ScoreLabel,40);
    ScoreLabel->getFontAtlas()->setAliasTexParameters();

    nextX = 29, nextY = 36;
    LineText = Label::createWithTTF("LINE", "fonts/CookieRun Black.ttf", 22);
    LineText->setTextColor(Color4B(0,255,100,255));
    LineText->setPosition(Vec2(nextX * BlockSize, height - (nextY * BlockSize)));
    LineText->enableOutline(Color4B::WHITE, 3);
    this->addChild(LineText, 30);
    LineText->getFontAtlas()->setAliasTexParameters();

    nextX = 29, nextY = 45.5;
    LevelText = Label::createWithTTF("LEVEL", "fonts/CookieRun Black.ttf", 20 );
    LevelText->setTextColor(Color4B(203,85,156,255));
    LevelText->setPosition(Vec2(nextX * BlockSize, height - (nextY * BlockSize)));
    LevelText->enableOutline(Color4B::WHITE, 4);
    this->addChild(LevelText, 30);
    LevelText->getFontAtlas()->setAliasTexParameters();

    // 스코어 라벨
    Score = Label::createWithTTF("", "fonts/DungGeunMo.ttf", 13);
    Score->setTextColor(Color4B::BLACK);
    Score->setPosition(Vec2(14.5 * widthBlock, height - (heightBlock * 13) - 20));
    this->addChild(Score, 30);
    this->addChild(HideBlank, 19);
   
    // 키보드 리스너
    EventListenerKeyboard* Keyboard = EventListenerKeyboard::create();
    Keyboard->onKeyPressed = CC_CALLBACK_2(Game::KeyboardInput, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard, this);

    // 터치 리스너
    EventListenerTouchOneByOne* RotationTouch = EventListenerTouchOneByOne::create();
    RotationTouch->setSwallowTouches(true);
    RotationTouch->onTouchBegan = CC_CALLBACK_2(Game::TouchBegan, this);
    RotationTouch->onTouchEnded = CC_CALLBACK_2(Game::RotationTouch, this);
    RotationTouch->onTouchMoved = CC_CALLBACK_2(Game::BlockMoveTouch, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(RotationTouch, this);



    // 배경화면 출력
    //BackGroundPrint();

    RandomBlock();
    NextBlockDraw(NextBlockShape);

    // 맵
    srand(time(NULL));
    this->addChild(BlockDraw, 3);
    this->addChild(PreviewDraw, 2);
    this->addChild(MainShape, 1);
    this->addChild(NextBlockShape, 5);
    this->addChild(LineDrawRect, 8);
    this->addChild(HoldBlockShape, 4);

    LinePrint();
    ScorePrint();
    levelprint();
   

    nextX = 26, nextY = 16;
    for (int row = 0; row < 6; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (BlockBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                HoldBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }
    HoldBlockShape->setLineWidth(30);

    HoldBlockShape->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
            (height - (nextY * BlockSize)) - (BlockSize * 6)), Color4F::GREEN);
    HoldBlockShape->setLineWidth(1);
    MapPrint();
    DrawBlock(BlockDraw);

    scheduleUpdate();

    return true;
}

int particleIsvisible = 0;

void Game::ParticleEffect()
{
    ParticleExplosion* Explosion_Particle = ParticleExplosion::create();
    Explosion_Particle->setPosition(Vec2(width / 2, height / 2));
    Explosion_Particle->setName("Explosion_Particle");
    Explosion_Particle->setVisible(true);
    Explosion_Particle->setOpacity(20);
    ParticleFire* Fire_Particle = ParticleFire::create();
    Fire_Particle->setPosition(Vec2(width / 2, height / 2));
    Fire_Particle->setName("Fire_Particle");
    Fire_Particle->setVisible(true);
    Explosion_Particle->setOpacity(30);

    if (particleIsvisible == 0)
    {
     
    }
    else if (particleIsvisible == 1)
    {
        particleIsvisible++;
    }
    else if (particleIsvisible == 2)
    {
        if (Explosion_Particle->isVisible() == true && Fire_Particle->isVisible() == true)
        {
            particleIsvisible = 0;
        }
    }
    else
    {
        log("Particle Unkown");
        return;
    }
}

void Game::RandomBlock()
{
    blockForm = NextblockForm; //
    nColor = NextColor;
    switch (blockForm)
    {
    case 0: {
        NextColor = 3;
        break;
    }
    case 1: {
        NextColor = 4;
        break;
    }
    case 2: {
        NextColor = 5;
        break;
    }
    case 3: {
        NextColor = 6;
        break;
    }
    case 4: {
        NextColor = 7;
        break;
    }
    case 5: {
        NextColor = 8;
        break;
    }
    case 6: {
        NextColor = 9;
        break;
    }
    }
    NextblockForm = rand() % 7;
    log("nColor = %d", nColor);
    log("NextColor = %d", NextColor);

}

void Game::DrawBlock(cocos2d::DrawNode* BlockDraw)
{
    nextX = 27.5, nextY = 5;
    BlockDraw->clear();
    if (nColor == 3)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::GREEN);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 4)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::YELLOW);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 5)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::BLUE);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 6)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::RED);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 7)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 8)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::ORANGE);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
    else if (nColor == 9)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((gameX * widthBlock) + (widthBlock * cols),
                        (height - (gameY * heightBlock)) - (heightBlock * row)), Vec2((gameX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (gameY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::WHITE);
                }
            }
        }
    }
}


void Game::NextBlockDraw(cocos2d::DrawNode* BlockDraw)
{
    BlockDraw->clear();
    nextX = 26, nextY = 5;
    for (int row = 0; row < 6; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (BlockBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                NextBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }
    BlockDraw->setLineWidth(30);

    NextBlockShape->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
            (height - (nextY * BlockSize)) - (BlockSize * 6)), Color4F::BLUE);
    BlockDraw->setLineWidth(1);
    if (NextblockForm == 1 || NextblockForm == 2 || NextblockForm == 0 || NextblockForm == 4)
    {
        nextX = 27.5, nextY = 6;
    }
    else if (NextblockForm == 3)
    {
        nextX = 26.5, nextY = 6;
    }
    else
    {
        nextX = 27, nextY = 6;
    }
    if (NextColor == 3)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::GREEN);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 4)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::YELLOW);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 5)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLUE);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 6)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::RED);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 7)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 8)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::ORANGE);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (NextColor == 9)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[NextblockForm][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
}

void Game::HoldBlockDraw(cocos2d::DrawNode* BlockDraw)
{
    BlockDraw->clear();
    nextX = 26, nextY = 16;
    for (int row = 0; row < 6; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (BlockBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                HoldBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }
    HoldBlockShape->setLineWidth(30);

    HoldBlockShape->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
            (height - (nextY * BlockSize)) - (BlockSize * 6)), Color4F::BLUE);
    HoldBlockShape->setLineWidth(1);
    if (HoldBlock == 1 || HoldBlock == 2 || HoldBlock == 0 || HoldBlock == 4)
    {
        nextX = 27.5, nextY = 17;
    }
    else if (NextblockForm == 3)
    {
        nextX = 26.5, nextY = 17;
    }
    else
    {
        nextX = 27, nextY = 17;
    }

    //BlockDraw->drawRect(Vec2(12 * widthBlock, height - (heightBlock * 2)), Vec2((12 * widthBlock) + (widthBlock * 10), height - (heightBlock * 5)), Color4F::WHITE);
    if (HoldColor == 3)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::GREEN);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 4)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::YELLOW);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 5)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLUE);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 6)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::RED);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 7)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 8)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::ORANGE);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
    else if (HoldColor == 9)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[HoldBlock][0][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    BlockDraw->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::MAGENTA);
                    BlockDraw->drawRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::BLACK);
                }
            }
        }
    }
}

void Game::Preview()
{
    int tempX = gameX;
    int tempY = gameY;
    while (crash(tempX, tempY + 1) == false)
    {
        tempY++;
    }
    PreviewDraw->clear();
    if (nColor == 3)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::GREEN);
                }
            }
        }
    }
    else if (nColor == 4)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::YELLOW);
                }
            }
        }
    }
    else if (nColor == 5)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::BLUE);
                }
            }
        }
    }
    else if (nColor == 6)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::RED);
                }
            }
        }
    }
    else if (nColor == 7)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::MAGENTA);
                }
            }
        }
    }
    else if (nColor == 8)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::ORANGE);
                }
            }
        }
    }
    else if (nColor == 9)
    {
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 4; cols++) {
                if (block[blockForm][blockRotation][row][cols] == 1) { // block값이 1일 == block이 잇을때
                    if (row + tempY != 0)
                    {
                        Tetrismap[row + tempY][cols + tempX] = PREVIEW;
                    }

                    PreviewDraw->drawRect(Vec2((tempX * widthBlock) + (widthBlock * cols),
                        (height - (tempY * heightBlock)) - (heightBlock * row)), Vec2((tempX * widthBlock) + (widthBlock * cols) + widthBlock,
                            (height - (tempY * heightBlock)) - (heightBlock * row) - heightBlock), Color4F::MAGENTA);
                }
            }
        }
    }
}

bool Game::crash(int x, int y, int Ps) { // x,y 를 매개변수로 받음.
    for (int row = 0; row < 4; row++) { // y값 검사
        for (int cols = 0; cols < 4; cols++) { // x값 검사
            if (block[blockForm][blockRotation + Ps][row][cols] == 1) { // 블럭 1값을 찾으면,
                int scan = Tetrismap[row + y][cols + x]; // scan변수 선언,  scan변수는 맵의[][]의 값을 가지며 if문을 들어가 검사함.
                if (scan == -1 || scan >= 2 && scan <= 9) { // 그래서 1이나 2가 감지되면,
                    return true; // true값을 반환
                }
            }
        }
    }

    return false;
    // 아니면 false값을 반환함.
}

void Game::BlockRotation()
{
    BlockDraw->clear();
    DrawBlock(BlockDraw);
}

void Game::ScorePrint()
{
    nextX = 26, nextY = 27;
    for (int row = 0; row < 4; row++) {
        for (int cols = 0; cols < 6; cols++) {
            if (ScoreBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                NextBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                    (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                        (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
            }
        }
    }
    NextBlockShape->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
        (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
            (height - (nextY * BlockSize)) - (BlockSize * 4)), Color4F::RED);

    if (Score != nullptr)
    {
        this->removeChild(Score, true);
    }
    char scoreTemp[50] = { '\0', };
    sprintf(scoreTemp, "%d", score);
    Score = Label::createWithTTF(scoreTemp, "fonts/NanumGothicBold.ttf", 13);
    Score->setTextColor(Color4B::BLACK);
    Score->setPosition(Vec2(14.5 * widthBlock, height - (heightBlock * 13) - 20.2));
    this->addChild(Score, 30);

}

void Game::LinePrint()
{
    
        nextX = 26, nextY = 37;
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 6; cols++) {
                if (ScoreBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                    NextBlockShape->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
                }
            }
        }
        LineDrawRect->setLineWidth(30);

        LineDrawRect->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
            (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
                (height - (nextY * BlockSize)) - (BlockSize * 4)), Color4F(244,231,0,255));
        LineDrawRect->setLineWidth(1);
        
    
    if (lineLabel != nullptr)
    {
        this->removeChild(lineLabel, true);
    }
    char LineTemp[50] = { '\0', };
    sprintf(LineTemp, "%d", line);
    lineLabel = Label::createWithTTF(LineTemp, "fonts/NanumGothicBold.ttf", 13);
    lineLabel->setTextColor(Color4B::BLACK);
    lineLabel->setPosition(Vec2(14.5 * widthBlock, height - (heightBlock * 19.4)));
    this->addChild(lineLabel, 50);
}

void Game::levelprint()
{
    
    if (LevelDrawRect == nullptr)
    {
        nextX = 26, nextY = 45.5;
        for (int row = 0; row < 4; row++) {
            for (int cols = 0; cols < 6; cols++) {
                if (ScoreBG[row][cols] == 1 || BlockBG[row][cols] == 0) { // block값이 1일 == block이 잇을때
                    LevelDrawRect->drawSolidRect(Vec2((nextX * BlockSize) + (BlockSize * cols),
                        (height - (nextY * BlockSize)) - (BlockSize * row)), Vec2((nextX * BlockSize) + (BlockSize * cols) + BlockSize,
                            (height - (nextY * BlockSize)) - (BlockSize * row) - BlockSize), Color4F::WHITE);
                }
            }
        }
        LevelDrawRect->setLineWidth(30);
        LevelDrawRect->drawRect(Vec2((nextX * BlockSize) + (BlockSize * 0),
            (height - (nextY * BlockSize)) - (BlockSize * 0)), Vec2((nextX * BlockSize) + (BlockSize * 6),
                (height - (nextY * BlockSize)) - (BlockSize * 4)), Color4F::ORANGE);
        LevelDrawRect->setLineWidth(1);
        this->addChild(LevelDrawRect);
        LevelDrawRect->setLineWidth(30);
    }
    
    if (LevelLabel != nullptr)
    {
        this->removeChild(LevelLabel, true);
    }
    this->removeChild(LevelLabel, true);
    char leveltemp[50] = { '\0', };
    sprintf(leveltemp, "%d", level);
    LevelLabel = Label::createWithTTF(leveltemp, "fonts/NanumGothicBold.ttf", 13);
    LevelLabel->setTextColor(Color4B::BLACK);
    LevelLabel->setPosition(Vec2(14.5 * widthBlock, height - (heightBlock * 24.2)));

    this->addChild(LevelLabel, 40);
}

void Game::MapPrint()
{
    MainShape->clear();
    float x1, y1, x2, y2;
    
    x1 = 0, y1 = height, x2 = widthBlock, y2 = height - heightBlock;
    for (int i = 0; i < mapY; i++)
    {
        for (int j = 0; j < mapX; j++)
        {
            if (Tetrismap[i][j] == -1 || Tetrismap[i][j] == 2) // 벽
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 3) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::GREEN);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 4) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::YELLOW);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 5) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::BLUE);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 6) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::RED);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 7) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::MAGENTA);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 8) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::ORANGE);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else if (Tetrismap[i][j] == 9) // 블럭
            {
                MainShape->drawSolidRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::MAGENTA);
                MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::WHITE);
            }
            else
            {
                //MainShape->drawRect(Vec2(x1 + (widthBlock * j), y1 - (heightBlock * i)), Vec2(x2 + (widthBlock * j), y2 - (heightBlock * i)), Color4F::GRAY);
            }
        }
    }

}

void Game::BackGroundPrint()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto Wallpaper = Sprite::create("Wallpaper.jpg");
    Size WallpaperSize = Wallpaper->getContentSize();
    Wallpaper->setContentSize(WallpaperSize / 2.5);
    Wallpaper->setPosition(Point(((visibleSize.width / 2) + origin.x), ((visibleSize.height / 2) + origin.y)));
    Wallpaper->setOpacity(50.0f);
    this->addChild(Wallpaper);

}

void Game::RemoveLine() {
    for (int ScanLine = 30; ScanLine >= 0; ScanLine--) { // 22 ( 세로 1 ) 아래에서부터 위로
        int BlockCount = 0;
        for (int ScanCols = 1; ScanCols < 12; ScanCols++) { //  ( 가로 1 )
            if (Tetrismap[ScanLine][ScanCols] >= 3 && Tetrismap[ScanLine][ScanCols] <= 11) { // 맵의 아래쪽부터 위로 검사함. 2발견시
                BlockCount++; // count++;
            }
        }
        if (BlockCount >= 10) { // 벽돌이 다 차있다면
            for (int j = 0; ScanLine - j >= 0; j++) { // i번째
                for (int cols = 1; cols < 11; cols++) { // 줄 검사
                    if (ScanLine - j - 1 >= 0)
                    {
                        Tetrismap[ScanLine - j][cols] = Tetrismap[ScanLine - j - 1][cols];
                    }
                    else
                    {
                        Tetrismap[ScanLine - j][cols] = 0;
                    }
                }
            }
            score += 100; 
            line += 1; 
            if (line % 10 == 0)
            {
                if (DownDropTime - 20 != 0)
                {
                    DownDropTime -= 20;
                    level++;
                }
            }
            SimpleAudioEngine::getInstance()->playEffect("Line.mp3");
        }
    }
}

bool Game::GameOver()
{
    for (int i = 1; i < 11; i++)
        if (Tetrismap[1][i] != 0)
        {
            return true;
        }
    return false;
}

void Game::GameEnd()
{
    if (gameOverLoop == 1)
    {

        GameOverSprite = Sprite::create("GameOver.png");
        GameOverSprite->setPosition(Vec2((widthBlock * 6), height - (heightBlock * 10)));
        auto blink = Blink::create(3, 4);
        GameOverSprite->runAction(blink);
        this->addChild(GameOverSprite, 11);
    }
    if (GameOverTimer == 180)
    {
        auto RankS = RankingScene::createScene();
        Director::getInstance()->replaceScene(RankS);
        
        fprintf(fp, "%d번째 시도 점수 : %d점", TryCount, score);
        fprintf(fp, "\n");
       
        TryCount++;
    }
}

void Game::PauseOn()
{
    if (Pause == 1)
    {
        Show* ShowA = Show::create();
        PauseSprite->runAction(ShowA);
    }
    else if (Pause == 0)
    {
        Hide* hideA = Hide::create();
        PauseSprite->runAction(hideA);
    }
}

void Game::update(float dt)
{
    /*
    // 커서 좌표
    POINT a;
    HWND hWnd;
    RECT window_size;
    a.x = 0;
    a.y = 0;
    GetCursorPos(&a);
    hWnd = WindowFromPoint(a);
    ScreenToClient(hWnd, &a);
    GetWindowRect(hWnd, &window_size);
    StartCurrY = a.y;
    StartCurrX = a.x;

    */

    if (BlockMoved == true)
    {
        MovedCount++;
    }
    else
    {
        MovedCount = 0;
    }
    if (Pause == 1)
    {
        PauseOn();
    }
    else
    {
        PauseOn();
        if (GameOver() == true)
        {
            GameOverTimer++; // 밥먹고옴
            gameOverLoop++;
            GameEnd();
        }
        else
        {
            MapPrint();
            RemoveLine();
            Preview();
            DrawBlock(BlockDraw);
            if (crash(gameX, gameY + 1) == true) // 다시 생각해 보자
            {
                log("TimeCount = %d", TimeCount);
                TimeCount++;
                if (TimeCount == TimeOverBlock)
                {
                    TimeCount = 0;
                    log("Block on Array");
                    DrawArray(gameX, gameY);
                    gameX = gameXInit;
                    gameY = gameYInit;
                    x = initX;
                    y = initY;
                    Holdon = 0;
                    RandomBlock();
                    NextBlockDraw(NextBlockShape);
                }
            }
            else
            {
                TimeCount = 0;
            }

            count++;
            if (count % DownDropTime == 0 && count != 0 && crash(gameX, gameY + 1) == false)
            {

                gameY++;
            }
            LinePrint();
            levelprint();
            ScorePrint();
        }
    }
}

void Game::DrawArray(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[blockForm][blockRotation][i][j] == 1)
                Tetrismap[i + gameY][j + gameX] = nColor;
        }
    }
    MapPrint();
}


void Game::DropDown()
{
    while (crash(gameX, gameY + 1) == false)
    {
        gameY++;
        stop = 1;
    }
    stop = 0;
    TimeCount = TimeOverBlock-1;
}

void Game::KeyboardInput(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    switch (keycode)
    {
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    {

        if (crash(gameX, gameY + 1) == false)
        {
            gameY++;

        }


        keyout = 0;
        break;
    }
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    {
        if (crash(gameX - 1, gameY) == false)
        {
            gameX--;

        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    {
        if (crash(gameX + 1, gameY) == false)
        {
            gameX++;

        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    {
        int currBlockRotation = blockRotation;
        if (blockForm == 0 && blockRotation != 4)
        {
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }

            if (crash(gameX, gameY, 1) == false)
            {
                blockRotation++;
                BlockRotation();
                return;
            }
        }
        if (blockForm == 3 && blockRotation != 4)
        {
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }
            if (crash(gameX, gameY, 1) == true)
            {
                if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX, gameY - 1, 1) == false)
                {
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX, gameY - 2, 1) == false)
                {
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX, gameY - 3, 1) == false)
                {
                    gameY -= 3;
                    blockRotation++;
                    BlockRotation();
                    return;

                }

                // 
                else if (crash(gameX + 1, gameY - 1, 1) == false)
                {
                    gameX++;
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return;

                }
                else if (crash(gameX + 2, gameY - 1, 1) == false)
                {
                    gameX += 2;
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return;

                }

                else if (crash(gameX + 1, gameY - 2, 1) == false)
                {
                    gameX++;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;

                }
                else if (crash(gameX + 2, gameY - 2, 1) == false)
                {
                    gameX += 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;

                }

                else if (crash(gameX + 1, gameY - 3, 1) == false)
                {
                    gameX++;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;

                }
                else if (crash(gameX + 2, gameY - 3, 1) == false)
                {
                    gameX += 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
            }
        }
        if (blockRotation != 4 && blockForm != 6)
        {
            if (crash(gameX, gameY, 1) == true)
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX - 1, gameY, 1) == false)
                {
                    gameX--;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                if (crash(gameX + 1, gameY, 1) == false)
                {
                    gameX++;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }

                // 위아래(1)
                if (crash(gameX - 1, gameY - 1, 1) == false)
                {
                    gameX--;
                    gameY--;
                    blockRotation++;
                    BlockRotation();

                }
                else if (crash(gameX - 2, gameY - 1, 1) == false)
                {
                    gameX -= 2;
                    gameY--;
                    blockRotation++;
                    BlockRotation();

                }

                // 위아래(2)
                if (crash(gameX - 1, gameY - 2, 1) == false)
                {
                    gameX--;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX - 2, gameY - 2, 1) == false)
                {
                    gameX -= 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                if (crash(gameX + 1, gameY, 1) == false)
                {
                    gameX++;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }

                //위
                if (crash(gameX, gameY - 1, 1) == false)
                {
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX, gameY - 2, 1) == false)
                {
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else
                {
                    blockRotation = currBlockRotation;
                    return;
                }
            }

            if (blockForm == 0 && blockRotation + 1 == 4)
            {
                blockRotation = 0;
                return;
            }
            if (crash(gameX - 1, gameY) == false && crash(gameX + 1, gameY) == true)
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return;
                }
            }
            if (crash(gameX + 1, gameY) == true && crash(gameX - 1, gameY) == true) //  현재 블럭이 좌 우 충돌 시
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX + 1, gameY, 1) == true || crash(gameX - 1, gameY, 1) == true) //  현재 블럭이 좌 우 충돌 시
                {
                    if (crash(gameX, gameY - 2, 1) == false) // 두칸을 올렷을시에 충돌하지 않으면
                    {
                        gameY -= 2;
                        blockRotation++;
                        BlockRotation();
                        return;

                    }
                    else // 두 칸을 올려도 충돌한다면.
                    {
                        return;
                    }
                }
            }
            // X
            if (crash(gameX + 1, gameY, 1) == true) // 바꾼블럭이 오른쪽과 충돌한다면
            {
                if (crash(gameX - 1, gameY, 1) == false) // 바꾼 블럭의 중심축을 x를 1 감소시켰을때 충돌하는지 확인
                {
                    gameX--;
                    blockRotation++;
                    BlockRotation();
                    return;

                }
                else
                {
                    return;
                }
            }

            if (crash(gameX - 1, gameY, 1) == true) // 바꾼 블럭이 왼쪽과 충돌한다면
            {
                if (crash(gameX + 2, gameY, 1) == false) // 바꾼 블럭의 중심축을 x를 1 증가시켰을때 충돌하는지 확인
                {

                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return;


                }
                else
                {
                    return;

                }
            }

            // Y

            if (crash(gameX, gameY + 1, 1) == true) // 바꾼 블럭이 아래와 충돌한다면
            {

                if (crash(gameX, gameY - 1, 1) == false)
                {

                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return;


                }
                else
                {
                    return;

                }
            }
            if (crash(gameX, gameY - 1, 1) == true)
            {

                if (crash(gameX, gameY + 1) == false)
                {

                    gameY++;
                    blockRotation++;
                    BlockRotation();
                    return;


                }
                else
                {
                    return;
                }
            }
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }
            blockRotation++;
            BlockRotation();

        }
        else
        {
            blockRotation = 0;
        }
        log("Rot = %d", blockRotation);
        log("Rot = %d", blockRotation);

        break;

    }
    case EventKeyboard::KeyCode::KEY_SPACE:
    {
        DropDown();
        break;
    }
    case EventKeyboard::KeyCode::KEY_C:
    {
        FirstHoldBlockCount++;
        if (FirstHoldBlockCount == 1)
        {
            HoldColor = nColor;
            HoldBlock = blockForm;
            blockForm = NextblockForm;
        }
        else
        {
            if (Holdon == 0)
            {
                gameX = gameXInit, gameY = gameYInit;
                int tempC = HoldColor;
                HoldColor = nColor;// 홀드한 블럭 색을 현재블럭색으로 저장해둠
                nColor = tempC; // 현재블럭색을 홀드색고 ㅏ맞춤.
                int temp = HoldBlock;
                HoldBlock = blockForm;
                blockForm = temp;
                Holdon++;
            }
        }
        HoldBlockDraw(HoldBlockShape);
        HoldCount++;
        break;
    }
    case EventKeyboard::KeyCode::KEY_P:
    {
        if (Pause == 0)
        {
            Pause = 1;
            SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        else
        {
            Pause = 0;
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
    }
    }
}

bool Game::RotationTouch(cocos2d::Touch* Touch, cocos2d::Event* Event)
{

    if (MovedCount < 15 && MovedCount != 0 && (StartPos_Y2 - 60 > StartCurrY) &&  Pause == 0)
    {
        DropDown();
        return true;
    }
    if (MovedCount < 15 && MovedCount != 0 && (StartPos_Y2 + 60 < StartCurrY) && Pause == 0)
    {
        FirstHoldBlockCount++;
        if (FirstHoldBlockCount == 1)
        {
            HoldColor = nColor;
            HoldBlock = blockForm;
            blockForm = NextblockForm;
        }
        else
        {
            if (Holdon == 0)
            {
                gameX = gameXInit, gameY = gameYInit;
                int tempC = HoldColor;
                HoldColor = nColor;// 홀드한 블럭 색을 현재블럭색으로 저장해둠
                nColor = tempC; // 현재블럭색을 홀드색고 ㅏ맞춤.
                int temp = HoldBlock;
                HoldBlock = blockForm;
                blockForm = temp;
                Holdon++;
            }
        }
        HoldBlockDraw(HoldBlockShape);
        HoldCount++;
    }

    m = StartPos_X - StartCurrX;

    m2 = StartPos_Y2 - StartCurrY;


    if ((BlockMoved == false) && Pause == 0 || ((BlockMoved == true) && (m < 2 && m2 < 2) && (MovedCount < 5)) && Pause == 0)
    {

        int currBlockRotation = blockRotation;
        if (blockForm == 0 && blockRotation != 4)
        {
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }

            if (crash(gameX, gameY, 1) == false)
            {
                blockRotation++;
                BlockRotation();
                return true;
            }
        }
        if (blockForm == 3 && blockRotation != 4)
        {
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }
            if (crash(gameX, gameY, 1) == true)
            {
                if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX, gameY - 1, 1) == false)
                {
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX, gameY - 2, 1) == false)
                {
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX, gameY - 3, 1) == false)
                {
                    gameY -= 3;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }

                // 
                else if (crash(gameX + 1, gameY - 1, 1) == false)
                {
                    gameX++;
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }
                else if (crash(gameX + 2, gameY - 1, 1) == false)
                {
                    gameX += 2;
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }

                else if (crash(gameX + 1, gameY - 2, 1) == false)
                {
                    gameX++;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }
                else if (crash(gameX + 2, gameY - 2, 1) == false)
                {
                    gameX += 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }

                else if (crash(gameX + 1, gameY - 3, 1) == false)
                {
                    gameX++;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }
                else if (crash(gameX + 2, gameY - 3, 1) == false)
                {
                    gameX += 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
            }
        }
        if (blockRotation != 4 && blockForm != 6)
        {
            if (crash(gameX, gameY, 1) == true)
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX - 1, gameY, 1) == false)
                {
                    gameX--;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                if (crash(gameX + 1, gameY, 1) == false)
                {
                    gameX++;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }

                // 위아래(1)
                if (crash(gameX - 1, gameY - 1, 1) == false)
                {
                    gameX--;
                    gameY--;
                    blockRotation++;
                    BlockRotation();

                }
                else if (crash(gameX - 2, gameY - 1, 1) == false)
                {
                    gameX -= 2;
                    gameY--;
                    blockRotation++;
                    BlockRotation();

                }

                // 위아래(2)
                if (crash(gameX - 1, gameY - 2, 1) == false)
                {
                    gameX--;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX - 2, gameY - 2, 1) == false)
                {
                    gameX -= 2;
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                if (crash(gameX + 1, gameY, 1) == false)
                {
                    gameX++;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }

                //위
                if (crash(gameX, gameY - 1, 1) == false)
                {
                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX, gameY - 2, 1) == false)
                {
                    gameY -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else
                {
                    blockRotation = currBlockRotation;
                    return true;
                }
            }

            if (blockForm == 0 && blockRotation + 1 == 4)
            {
                blockRotation = 0;
                return true;
            }
            if (crash(gameX - 1, gameY) == false && crash(gameX + 1, gameY) == true)
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX - 2, gameY, 1) == false)
                {
                    gameX -= 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
                else if (crash(gameX + 2, gameY, 1) == false)
                {
                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return true;
                }
            }
            if (crash(gameX + 1, gameY) == true && crash(gameX - 1, gameY) == true) //  현재 블럭이 좌 우 충돌 시
            {
                if (blockRotation + 1 == 4)
                {
                    blockRotation = -1;
                }
                if (crash(gameX + 1, gameY, 1) == true || crash(gameX - 1, gameY, 1) == true) //  현재 블럭이 좌 우 충돌 시
                {
                    if (crash(gameX, gameY - 2, 1) == false) // 두칸을 올렷을시에 충돌하지 않으면
                    {
                        gameY -= 2;
                        blockRotation++;
                        BlockRotation();
                        return true;

                    }
                    else // 두 칸을 올려도 충돌한다면.
                    {
                        return true;
                    }
                }
            }
            // X
            if (crash(gameX + 1, gameY, 1) == true) // 바꾼블럭이 오른쪽과 충돌한다면
            {
                if (crash(gameX - 1, gameY, 1) == false) // 바꾼 블럭의 중심축을 x를 1 감소시켰을때 충돌하는지 확인
                {
                    gameX--;
                    blockRotation++;
                    BlockRotation();
                    return true;

                }
                else
                {
                    return true;
                }
            }

            if (crash(gameX - 1, gameY, 1) == true) // 바꾼 블럭이 왼쪽과 충돌한다면
            {
                if (crash(gameX + 2, gameY, 1) == false) // 바꾼 블럭의 중심축을 x를 1 증가시켰을때 충돌하는지 확인
                {

                    gameX += 2;
                    blockRotation++;
                    BlockRotation();
                    return true;


                }
                else
                {
                    return true;

                }
            }

            // Y

            if (crash(gameX, gameY + 1, 1) == true) // 바꾼 블럭이 아래와 충돌한다면
            {

                if (crash(gameX, gameY - 1, 1) == false)
                {

                    gameY--;
                    blockRotation++;
                    BlockRotation();
                    return true;


                }
                else
                {
                    return true;

                }
            }
            if (crash(gameX, gameY - 1, 1) == true)
            {

                if (crash(gameX, gameY + 1) == false)
                {

                    gameY++;
                    blockRotation++;
                    BlockRotation();
                    return true;


                }
                else
                {
                    return true;
                }
            }
            if (blockRotation + 1 == 4)
            {
                blockRotation = -1;
            }
            blockRotation++;
            BlockRotation();

        }
        else
        {
            blockRotation = 0;
        }


        //
    }
    else
    {
        BlockMoved = false;
    }
    log("Rot = %d", blockRotation);

    return true;
}
int i = 0;
bool Game::BlockMoveTouch(cocos2d::Touch* Touch, cocos2d::Event* Event)
{
    StartCurrY = Touch->getLocation().y;
    StartCurrX = Touch->getLocation().x;
    log("x = %d, y = %d", StartCurrX, StartCurrY);
    if (StartPos_Y - 8 > StartCurrY && (StartCurrY > 0 && StartCurrY < 480))
        {
            if (crash(gameX, gameY + 1) == false)
            {
                gameY++;
                stop = 1;
                StartPos_Y = Touch->getLocation().y;
            }
        }

    if (stop == 1)
    {
        if (StartPos_X -  32> StartCurrX)
        {
            if (crash(gameX - 1, gameY) == false)
            {
                gameX--;
                StartPos_X = Touch->getLocation().x;
                

            }
        }
        else if (StartPos_X + 32 < StartCurrX)
        {


            if (crash(gameX + 1, gameY) == false)
            {
                gameX++;
                StartPos_X = Touch->getLocation().x;
               
            }
        }
    }
    else
    {
        if (StartPos_X - 16 > StartCurrX)
        {
            if (crash(gameX - 1, gameY) == false)
            {
                gameX--;
                StartPos_X = Touch->getLocation().x;


            }
        }
        else if (StartPos_X + 16< StartCurrX)
        {


            if (crash(gameX + 1, gameY) == false)
            {
                gameX++;
                StartPos_X = Touch->getLocation().x;

            }
        }
    }
    
       
    
   
        
    
    BlockMoved = true;
    return true;
}

bool Game::TouchBegan(cocos2d::Touch* Touch, cocos2d::Event* Event)
{
    BlockMoved = false;
    StartPos_X = Touch->getLocation().x;
    StartPos_Y = Touch->getLocation().y;
    StartPos_X2 = Touch->getLocation().x;
    StartPos_Y2 = Touch->getLocation().y;
    StartPos_X3 = Touch->getLocation().x;
    StartPos_Y3 = Touch->getLocation().y;
    return true;
}

void Game::pauseButton(Ref* sender, cocos2d::ui::Widget::TouchEventType Type)
{
    switch (Type)
    {
    case cocos2d::ui::Widget::TouchEventType::BEGAN:
    {
        if (Pause == 0)
        {
            Pause = 1;
            if (op == nullptr)
            {
                op = DrawNode::create();
                op->drawSolidRect(Vec2(0, 0), Vec2(192 ,480), Color4F::BLACK);
                op->setOpacity(85);
                this->addChild(op,50);
            }
            else
            {
                Show* ShowOp = Show::create();
                op->runAction(ShowOp);
            }
            SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        else
        {
            Hide* hideOp = Hide::create();
            op->runAction(hideOp);
            Pause = 0;
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
        break;
    }
    }
}



void Game::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
