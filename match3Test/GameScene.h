//
//  GameScene.h
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __kingTest__GameScene__
#define __kingTest__GameScene__

#include "Node.h"

class Sprite;
class Field;
class Label;

class GameScene: public Node {
private:
    //logic
    Int _score;
    Float _timeLeft;
    
    Field *_field;
    Label *_scoreLabel;
    Label *_countLabel;
    Label *_restartLabel;

    Bool _gameOver;
    
    Sprite *_back;
public:
    GameScene();
    ~GameScene();
public:
    virtual Bool init();
    
    virtual void render();
    virtual Bool update(Float dt);
    
    void restart();
    void gameOver();
    
    //mouse stuff
    void onLeftMouseDown(Int x, Int y);
    void onLeftMouseUp(Int x, Int y);
    void onLeftMouseDragged(Int x, Int y);
    void onMouseMove(Int x, Int y);
    
    //score logic
    void applyPoints(Int points);

    void setScore(Int score);
    Int getScore();
    
    //time logic
    void tick(Float dt);
    Float getTimeLeft();
    
    void setTimeLeft(Float time);
};

#endif /* defined(__kingTest__GameScene__) */