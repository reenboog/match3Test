//
//  Sprite.h
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__Sprite__
#define __match3Test__Sprite__

#include "Node.h"

class Sprite: public Node {
private:
    string _file;
    SDL_Rect _rect;
    SDL_Surface *_surface;
public:
    ~Sprite();
    Sprite(string file);
    Sprite(string file, SDL_Rect rect);
public:
    virtual Bool init();
    virtual void cleanup();
    
    virtual void render(SDL_Surface *dst);
    virtual Bool update(Float dt);
    
    virtual void updateGeometry();
    
    SDL_Rect getRect();
private:
    void visit(SDL_Surface *dst);
};

#endif /* defined(__match3Test__Sprite__) */
