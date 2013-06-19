//
//  SurfaceManager.h
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__SurfaceManager__
#define __match3Test__SurfaceManager__

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "Types.h"

class SurfaceManager {
private:
    static SurfaceManager *__instance;
    
    SurfaceMap _surfaces;
private:
    SurfaceManager();
public:
    ~SurfaceManager();
    
    SDL_Surface* surfaceByName(string name);

    void purge();
    
    static SurfaceManager *mngr();
};

#endif /* defined(__match3Test__SurfaceManager__) */
