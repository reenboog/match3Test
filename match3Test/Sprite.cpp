//
//  Sprite.cpp
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Sprite.h"
#include "TextureManager.h"
#include "Types.h"

Sprite::~Sprite() {
    //------------------------------------------------
    printf("-sprite %s destroyed. \n", _file.c_str());
}

Sprite::Sprite() {
    
}

Sprite::Sprite(string file) {
    loadTexture(file, 0, 0, -1, -1);
}

Sprite::Sprite(string file, Int x, Int y, Int w, Int h) {
    
    loadTexture(file, x, y, w, h);
}

void Sprite::loadTexture(string file, Float x, Float y, Float width, Float height) {
    
    _anchorPoint = v2(0.5, 0.5);
    
    _file = file;
    
    _texture = TextureManager::mngr()->textureByName(file);
    
    GLint tWidth;
    GLint tHeight;
    
    //get width and height
    glBindTexture(GL_TEXTURE_2D, _texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &tHeight);
    
    _size.w = (width == -1 ? tWidth : width);
    _size.h = (height == -1 ? tHeight : height);
    
    _uvCoords[0] = {(x + _size.w) / tWidth, (y + _size.h) / tHeight};
    _uvCoords[1] = {(x + _size.w) / tWidth, y / tHeight};
    _uvCoords[2] = {x / tWidth, y / tHeight};
    _uvCoords[3] = {x / tWidth, (y + _size.h) / tHeight};
    
    printf("+sprite %s created. \n", _file.c_str());
}

Size2 Sprite::getSize() {
    return _size;
}

void Sprite::cleanup() {
    
}

void Sprite::render() {
    Node::render();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    Float hw = _size.w / 2.0;
    Float hh = _size.h / 2.0;
    
    //apply anchor point
    
    Vector2 anchorCorrection = v2((0.5 - _anchorPoint.x) * _size.w, (0.5 - _anchorPoint.y) * _size.h);
    
    glBegin(GL_QUADS);
	
	glTexCoord2f(_uvCoords[0].u, _uvCoords[0].v);
	glVertex3f(hw + anchorCorrection.x, hh + anchorCorrection.y, 0.0f);
    
	glTexCoord2f(_uvCoords[1].u, _uvCoords[1].v);
	glVertex3f(hw + anchorCorrection.x, -hh + anchorCorrection.y, 0.0f);
    
	glTexCoord2f(_uvCoords[2].u, _uvCoords[2].v);
	glVertex3f(-hw + anchorCorrection.x, -hh + anchorCorrection.y, 0.0f);
    
	glTexCoord2f(_uvCoords[3].u, _uvCoords[3].v);
	glVertex3f(-hw + anchorCorrection.x, hh + anchorCorrection.y , 0.0f);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

Bool Sprite::update(Float dt) {
    return true;
}

void Sprite::setUV(Float u0, Float v0, Float u1, Float v1) {
    _uvCoords[0].u = u1; _uvCoords[0].v = v1;
    _uvCoords[1].u = u1; _uvCoords[1].v = v0;
    _uvCoords[2].u = u0; _uvCoords[2].v = v0;
    _uvCoords[3].u = u0; _uvCoords[3].v = v1;
}

Vector2 Sprite::getAnchorPoint() {
    return _anchorPoint;
}

void Sprite::setAnchorPoint(Vector2 anchor) {
    _anchorPoint = anchor;
}
