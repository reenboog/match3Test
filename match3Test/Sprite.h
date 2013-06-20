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
    
    GLuint _texture;

    UV _uvCoords[4];
    Size2 _size;
    
public:
    ~Sprite();
    
    Sprite(string file);
    Sprite(string file, Int x, Int y, Int w, Int h);
public:
    virtual void cleanup();
    
    virtual void render();
    virtual Bool update(Float dt);
    
    Size2 getSize();
private:
    void loadTexture(string file, Float x, Float y, Float width, Float height);
};

#endif /* defined(__match3Test__Sprite__) */
