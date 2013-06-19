//
//  Sprite.cpp
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Sprite.h"
#include "SurfaceManager.h"

Sprite::~Sprite() {
    //------------------------------------------------
    printf("-sprite %s destroyed. \n", _file.c_str());
}

Sprite::Sprite(string file) {
    _file = file;
    
    _surface = SurfaceManager::mngr()->surfaceByName(file);
    _rect = {0, 0, (Uint16)_surface->w, (Uint16)_surface->h};
    
    init();
    
    
    //------------------------------------------------
    printf("+sprite %s created. \n", _file.c_str());
}

Sprite::Sprite(string file, SDL_Rect rect) {
    _file = file;
    _rect = rect;
    
    _surface = SurfaceManager::mngr()->surfaceByName(file);
    
    init();
}

void Sprite::updateGeometry() {
    Vector2 pos = getPos();

    _rect.x = pos.x;
    _rect.y = pos.y;
}

SDL_Rect Sprite::getRect() {
    
}

Bool Sprite::init() {
    return true;
}

void Sprite::cleanup() {
    
}

void Sprite::render(SDL_Surface *dst) {
    Node::render(dst);
    
    
    
    //apply x and y
    //SDL_SetAlpha(_surface, SDL_RLEACCEL | SDL_SRCALPHA,(Uint8) 10);
    SDL_BlitSurface(_surface, nullptr, dst, &_rect);
}

Bool Sprite::update(Float dt) {
    return true;
}