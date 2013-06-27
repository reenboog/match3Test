//
//  Label.cpp
//  match3Test
//
//  Created by Alex Gievsky on 27.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Label.h"

Label::~Label() {
    glDeleteTextures(1, &_texture);
    
    TTF_CloseFont(_font);
}

Label::Label(string text, Int size, SDL_Color color, string file) {
    _texture = -1;
    _file = file;
    _color = color;
    
    _font = TTF_OpenFont(file.c_str(), size);
    
    setText(text);
}

void Label::setText(string text) {
    
    if(_texture == -1) {
        glDeleteTextures(1, &_texture);
    }

	SDL_Surface *message = TTF_RenderText_Blended(const_cast<TTF_Font*>(_font), text.c_str(), _color);
    
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
    
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, message->w, message->h, 0, GL_BGRA,
	             GL_UNSIGNED_BYTE, message->pixels);
    
    _size.w = message->w;
    _size.h = message->h;
    
    _uvCoords[0] = {1, 1};
    _uvCoords[1] = {1, 0};
    _uvCoords[2] = {0, 0};
    _uvCoords[3] = {0, 1};
    
	SDL_FreeSurface(message);
}

void Label::setColor(Uint8 r, Uint8 g, Uint8 b) {
    _color = {r, g, b};
    
    setText(_text);
}