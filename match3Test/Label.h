//
//  Label.h
//  match3Test
//
//  Created by Alex Gievsky on 27.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__Label__
#define __match3Test__Label__

#include "Sprite.h"

#include <SDL_ttf/SDL_ttf.h>

class Label: public Sprite {
private:
    string _text;
    
    SDL_Color _color;
    
    TTF_Font *_font;
public:
    Label(string text, Int size = 20, SDL_Color color = {255, 255, 255}, string file = "mainFont.ttf");
    ~Label();
    
    string getText();
    void setText(string text);
    
    void setColor(Uint8 r, Uint8 g, Uint8 b);
};

#endif /* defined(__match3Test__Label__) */
