//
//  GameScene.cpp
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "GameScene.h"
#include "Constants.h"
#include "Sprite.h"
#include "Chip.h"
#include "Field.h"
#include "Label.h"

#include "SoundManager.h"

#include <iostream>
#include <sstream>

GameScene::GameScene() {
    _back = nullptr;
    _score = 0;
    _timeLeft = 0;
    _scoreLabel = nullptr;
    _countLabel = nullptr;
    _gameOver = true;
}

GameScene::~GameScene() {
    cleanup();
}

Bool GameScene::init() {
    
    _back = new Sprite("back.png");
    _back->setPos(v2(755 / 2, 300));
    _back->setRotation(0);
        
    this->addChild(_back);
    
    _field = new Field();
    _field->init();
    _field->setGameDelegate(this);

    this->addChild(_field);
    
    _scoreLabel = new Label("0");
    _scoreLabel->setPos(v2(20, 20));
    _scoreLabel->setAnchorPoint(v2(0.0, 0.5));
    
    this->addChild(_scoreLabel);
    
    _countLabel = new Label("0", 40, {30, 60, 50});
    _countLabel->setPos(v2(730, 560));
    _countLabel->setAnchorPoint(v2(1, 0.5));
    
    this->addChild(_countLabel);
    
    _restartLabel = new Label("Press \'R\' to restart", 20, {100, 30, 30});
    _restartLabel->setPos(v2(10, 580));
    _restartLabel->setAnchorPoint(v2(0, 0.5));
    _restartLabel->setHidden(true);
    
    this->addChild(_restartLabel);
    
    SoundManager::mngr()->playBackground("md-1.mp3");
    SoundManager::mngr()->preloadEffect("btnClick.wav");
    SoundManager::mngr()->preloadEffect("chipBreak.wav");
    SoundManager::mngr()->preloadEffect("lvlComplete.wav");
    
    restart();
    
    return true;
}

void GameScene::render() {
    Node::render();
}

Bool GameScene::update(Float dt) {
    
    if(_gameOver) {
        return false;
    }
    
    Node::update(dt);
    
    tick(dt);
    
    if(_timeLeft <= 0) {
        gameOver();
    }
        
    return true;
}

void GameScene::restart() {
    setScore(0);
    setTimeLeft(kGameSessionTime);
    
    _field->shuffle();
    _restartLabel->setHidden(true);
    
    _gameOver = false;
}

void GameScene::gameOver() {
    setTimeLeft(0);
    
    _gameOver = true;
    
    _restartLabel->setHidden(false);
    
    SoundManager::mngr()->playEffect("lvlComplete.wav");
}

void GameScene::onLeftMouseDown(Int x, Int y) {
    //printf("left btn down: x %i, y %i\n", x, y);
}

void GameScene::onLeftMouseUp(Int x, Int y) {
    if(_gameOver) {
        return;
    }
    
    //printf("left btn up: x %i, y %i\n", x, y);
    if((x > kFieldBasePoint.x && x < (kFieldBasePoint.x + kFieldAreaWidth)) &&
       y > kFieldBasePoint.y && y < (kFieldBasePoint.y + kFieldAreaHeight)) {
        _field->onLeftMouseUp(x, y);
    }
}

void GameScene::onLeftMouseDragged(Int x, Int y) {
    //printf("left btn dragged: x %i, y %i\n", x, y);
}

void GameScene::onMouseMove(Int x, Int y) {
    //printf("left btn moved: x %i, y %i\n", x, y);
}

//logic

void GameScene::applyPoints(Int points) {
    _score += points;
    
    setScore(_score);
}

void GameScene::setScore(Int score) {
    _score = score;
    
    std::stringstream str;
    
    str << _score;
    
    _scoreLabel->setText(str.str());
}

Int GameScene::getScore() {
    return _score;
}

void GameScene::tick(Float dt) {
    _timeLeft -= dt;
    
    setTimeLeft(_timeLeft);
}

void GameScene::setTimeLeft(Float time) {
    _timeLeft = time;

    std::stringstream str;
    
    str << (Int)_timeLeft;
    
    _countLabel->setText(str.str());
}

Float GameScene::getTimeLeft() {
    return _timeLeft;
}
