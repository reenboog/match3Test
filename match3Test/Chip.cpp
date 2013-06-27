//
//  Chip.cpp
//  match3Test
//
//  Created by Alex Gievsky on 20.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Chip.h"
#include "Constants.h"

Chip::~Chip() {
    
}

Chip::Chip(ChipType type) {
    //create sprite
    //Sprite(string file, Int x, Int y, Int w, Int h);
    _sprite = new Sprite("stones.png", 0, 0, 35, 35);
    _state = CS_Init;
    _sprite->setScale(0);
    
    addChild(_sprite);
    
    setType(type);
}

void Chip::setType(ChipType type) {
    
    if(type >= kNumOfChipTypes) {
        printf("! error applying chip type: %i", type);
        
        type = CT_Red;
    }
    //just apply appropriate uv-coords
    _type = type;
    
    UVRect rect = uvRectForChipType(type);
    _sprite->setUV(rect._0.u, rect._0.v, rect._1.u, rect._1.v);
}

ChipType Chip::getType() {
    return _type;
}

void Chip::setGridCoords(Int col, Int row) {
    _gridCoords = v2(col, row);
}

void Chip::setGridCoords(Vector2 coords) {
    _gridCoords = coords;
}

Vector2 Chip::getGridCoords() {
    return _gridCoords;
}

void Chip::setState(ChipState state) {
    _state = state;
}

ChipState Chip::getState() {
    return _state;
}

void Chip::die() {
    _state = CS_Dying;
}

Bool Chip::update(Float dt) {
    Node::update(dt);
    
    switch(_state) {
        
        case CS_Init: {
            _sprite->setScale(_sprite->getScale() + 5 * dt);
            if(_sprite->getScale() >= 1.0) {
                _sprite->setScale(1.0);
                _state = CS_Normal;
            }
        } break;
        case CS_Normal: {
            
        } break;
        case CS_Dying: {
            
            setScale(getScale() - 10 * dt);
            
            if(getScale() <= 0) {
                setScale(0);
                setState(CS_Dead);
            }
            
        } break;
        case CS_Dead: {
            this->removeFromParent();
        } break;
    }
    
    return true;
}

UVRect Chip::uvRectForChipType(ChipType type) {
    
    //waring: magic numbers!
    static const UVRect rects[] = {
        {{0, 36 / 128.0}, {35 / 128.0, 70 / 128.0}},  //red
        {{36 / 128.0, 0}, {70 / 128.0, 35 / 128.0}},  //green
        {{71 / 128.0, 0}, {105 / 128.0, 35 / 128.0}}, //blue
        {{0, 0}, {35 / 128.0, 35 / 128.0}},           //yellow
        {{0, 70 / 128.0}, {35 / 128.0, 105 / 128.0}}  //pink
    };
    
    return rects[type];
}