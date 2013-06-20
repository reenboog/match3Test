//
//  App.h
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __kingTest__App__
#define __kingTest__App__

#include <SDL/SDL.h>

#include "Types.h"

class GameScene;

class App {
private:
    bool _running;
    SDL_Surface *_mainSurface;
    
    GameScene *_scene;
    
public:
    App();
    ~App();
    
    Int run();
public:
    
    Bool init();
    void onEvent(SDL_Event *event);
    void loop();
    void render();
    void cleanup();
};

#endif /* defined(__kingTest__App__) */
