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

#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
// using namespace
using namespace cocos2d;

class Game : public cocos2d::Scene
{
public:


    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Game);

    // Label Structure
    cocos2d::Label* Score;
    cocos2d::Label* lineLabel;
    cocos2d::Label* LevelLabel;
    cocos2d::Label* nextLabel;
    cocos2d::Label* holdLabel;
    cocos2d::Label* ScoreLabel;
    cocos2d::Label* LineText;
    cocos2d::Label* LevelText;
    cocos2d::Label* DLabel;

    // DrawNode(Rect) Structure
    cocos2d::DrawNode* LineDrawRect;
    cocos2d::DrawNode* LevelDrawRect;
    cocos2d::DrawNode* BlockDraw;
    cocos2d::DrawNode* op;
    cocos2d::DrawNode* NextBlockShape;
    cocos2d::DrawNode* HoldBlockShape;
    cocos2d::DrawNode* MainShape;
    cocos2d::DrawNode* PreviewDraw;
    cocos2d::DrawNode* ScoreDraw;

    // Sprite(in Game) Structure
    cocos2d::Sprite* GameOverSprite;
    cocos2d::Sprite* PauseSprite;

    void GameEffect();
    void Preview();
    void DrawBlock(cocos2d::DrawNode* BlockDraw);
    void ScorePrint();
    void LinePrint();
    void MapPrint();
    void BackGroundPrint();
    void RandomBlock();
    void KeyboardInput(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void pauseButton(Ref* sender, cocos2d::ui::Widget::TouchEventType Type);
    void update(float dt);
    void BlockRotation();
    bool crash(int x, int y, int Ps = 0);
    void DrawArray(int x, int y);
    void RemoveLine();
    void NextBlockDraw(cocos2d::DrawNode* BlockDraw);
    void DropDown();
    void ParticleEffect();
    bool GameOver();
    void GameEnd();
    void HoldBlockDraw(cocos2d::DrawNode* BlockDraw);
    void levelprint();
    void PauseOn();
    //void ActuallyGlow();
    bool RotationTouch(cocos2d::Touch* Touch, cocos2d::Event* Event);
    bool BlockMoveTouch(cocos2d::Touch* Touch, cocos2d::Event* Event);
    bool TouchBegan(cocos2d::Touch* Touch, cocos2d::Event* Event);
    //192 x 480

};

#endif // __Game_SCENE_H__
