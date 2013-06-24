//
//  GameScene.cpp
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include <SDL_image/SDL_image.h>
#include "GameScene.h"
#include "Sprite.h"

GameScene::GameScene() {
    _back = nullptr;
}

GameScene::~GameScene() {
    cleanup();
}

Bool GameScene::init() {
    _back = new Sprite("back.png");
    _back->setPos(v2(755 / 2, 300));
    _back->setRotation(0);
        
    this->addChild(_back);
    
    Sprite *stone = nullptr;

    stone = new Sprite("stones.png", 0, 0, 35, 35);
    stone->setPos({100, 100});
    _back->addChild(stone);
    
    stone = new Sprite("stones.png", 36, 0, 34, 35);
    stone->setPos({200, 100});
    _back->addChild(stone);
    
    stone = new Sprite("stones.png", 72, 0, 35, 35);
    stone->setPos({300, 100});
    _back->addChild(stone);
    
    stone = new Sprite("stones.png", 0, 36, 35, 35);
    stone->setPos({100, 200});
    _back->addChild(stone);
    
    stone = new Sprite("stones.png", 0, 72, 35, 35);
    stone->setPos({100, 300});
    _back->addChild(stone);
    
    return true;
}

void GameScene::cleanup() {
    Node:Node::cleanup();
}

void GameScene::render() {
    Node::render();
}

Bool GameScene::update(Float dt) {
    Node::update(dt);
    
    return true;
}

void GameScene::onLeftMouseDown(Int x, Int y) {
    printf("left btn down: x %i, y %i\n", x, y);
}

void GameScene::onLeftMouseUp(Int x, Int y) {
    printf("left btn up: x %i, y %i\n", x, y);
}

void GameScene::onLeftMouseDragged(Int x, Int y) {
    printf("left btn dragged: x %i, y %i\n", x, y);
}

void GameScene::onMouseMove(Int x, Int y) {
    printf("left btn moved: x %i, y %i\n", x, y);
}
