//
//  SoundManager.h
//  match3Test
//
//  Created by Alex Gievsky on 26.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__SoundManager__
#define __match3Test__SoundManager__

#include "Types.h"

#include <SDL_mixer/SDL_mixer.h>

typedef map<string, Mix_Chunk *> EffectMap;

class SoundManager {
private:
    static SoundManager *__instance;
    Mix_Music *_background;
    
    EffectMap _effects;
    
private:
    SoundManager();
    Mix_Chunk* loadEffect(string file);
public:
    ~SoundManager();
    
    Bool playEffect(string file);
    Bool playBackground(string file);

    void pauseBackground();
    void stopBackground();
    void resumeBackground();
    
    static SoundManager *mngr();
    void purge();

    Bool preloadEffect(string file);
};

#endif /* defined(__match3Test__SoundManager__) */
