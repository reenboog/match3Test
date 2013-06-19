//
//  GameScene.h
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __kingTest__GameScene__
#define __kingTest__GameScene__

#include "Node.h"

class Sprite;

class GameScene: public Node {
private:
    Sprite *_back;
public:
    GameScene();
    ~GameScene();
public:
    virtual Bool init();
    virtual void cleanup();
    
    virtual void render(SDL_Surface *dst);
    virtual Bool update(Float dt);

};

#endif /* defined(__kingTest__GameScene__) */
