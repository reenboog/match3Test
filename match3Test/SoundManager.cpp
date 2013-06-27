//
//  SoundManager.cpp
//  match3Test
//
//  Created by Alex Gievsky on 26.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "SoundManager.h"


SoundManager* SoundManager::__instance = nullptr;

SoundManager::~SoundManager() {
    purge();
}

SoundManager::SoundManager() {
    //fake for a while
    _background = nullptr;
    
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

SoundManager* SoundManager::mngr() {
    if(__instance == nullptr) {
        __instance = new SoundManager();
    }
    
    return __instance;
}

void SoundManager::purge() {
    for(auto effect: _effects) {
        Mix_FreeChunk(effect.second);
    }
    
    _effects.clear();

    Mix_FreeMusic(_background);
    _background = nullptr;
}

Bool SoundManager::playEffect(string file) {
    auto effectIt = _effects.find(file);
    
    if(effectIt != _effects.end()) {
        Mix_PlayChannel(-1, effectIt->second, 0);
    } else {
        Mix_Chunk *chunk = loadEffect(file);
        
        if(chunk) {
            Mix_PlayChannel(-1, chunk, 0);
            
            _effects.insert({file, chunk});
        } else {
            return false;
        }
    }
    
    return true;
}

Mix_Chunk* SoundManager::loadEffect(string file) {
    return Mix_LoadWAV(file.c_str());
}

Bool SoundManager::preloadEffect(string file) {
    if(!loadEffect(file)) {
        return  false;
    } else {
        return true;
    }
}

Bool SoundManager::playBackground(string file) {
    _background = Mix_LoadMUS(file.c_str());
    
    if(!_background) {
        return false;
    }
    
    Mix_PlayMusic(_background, -1);
    
    return true;
}

void SoundManager::pauseBackground() {
    Mix_PauseMusic();
}

void SoundManager::stopBackground() {
    Mix_PauseMusic();
    Mix_RewindMusic();
}

void SoundManager::resumeBackground() {
    Mix_ResumeMusic();
}