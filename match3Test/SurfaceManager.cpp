//
//  SurfaceManager.cpp
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "SurfaceManager.h"

SurfaceManager* SurfaceManager::__instance = nullptr;

SurfaceManager::~SurfaceManager() {
    purge();
}

SurfaceManager::SurfaceManager() {
    //fake for a while
}

SurfaceManager* SurfaceManager::mngr() {
    if(__instance == nullptr) {
        __instance = new SurfaceManager();
    }
    
    return __instance;
}

void SurfaceManager::purge() {
    for(auto srf: _surfaces) {
        SDL_FreeSurface(srf.second);
    }
    
    _surfaces.clear();
}

SDL_Surface* SurfaceManager::surfaceByName(string name) {
    auto it = _surfaces.find(name);
    
    if(it == _surfaces.end()) {
        SDL_Surface *surf = IMG_Load(name.c_str());
        
        if(surf) {
            _surfaces.insert({name, surf});
            return surf;
        } else {
            printf("erorr loading image: %s", name.c_str());
            return nullptr;
        }
    } else {
        return it->second;
    }
}