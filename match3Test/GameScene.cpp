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
    Node::init();
        
//    SDL_Surface *tmp = NULL;
//    
//    if((tmp = IMG_Load("img0.png")) == NULL) {
//        printf("error loading mage.");
//        return false;
//    }
//    
//    _tmp = SDL_DisplayFormat(tmp);
//    SDL_FreeSurface(tmp);
    
    _back = new Sprite("back.jpg");
    //_back->setPos(v2(10, 10));
    
    Sprite *t = new Sprite("img0.png");
    _back ->addChild(t);
    
    t->setPos(v2(20, 100));
    
    this->addChild(_back);
    
    return true;
}

void GameScene::cleanup() {
    Node:Node::cleanup();
}

void GameScene::render(SDL_Surface *dst) {
    Node::render(dst);
}

Bool GameScene::update(Float dt) {
    Node::update(dt);
    
    return true;
}
