//
//  App.cpp
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "App.h"
#include "SurfaceManager.h"

App::~App() {
    delete _scene;
    delete SurfaceManager::mngr();
}

App::App() {
    _mainSurface = NULL;
    _running = true;
}

Int App::run() {
    if(init() == false) {
        return -1;
    }
    
    SDL_Event event;
    
    while(_running) {
        while(SDL_PollEvent(&event)) {
            onEvent(&event);
        }
        
        loop();
        render();
    }
    
    cleanup();
    
    return 0;
}

Bool App::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    if((_mainSurface = SDL_SetVideoMode(755, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    _scene = new GameScene();
    _scene->init();
    
    return true;
}

void App::onEvent(SDL_Event *event) {
    if(event->type == SDL_QUIT) {
        _running = false;
    }
}

void App::loop() {
    Float dt = 0; //todo: get some time here
    _scene->update(dt);
}

void App::render() {
    _scene->visit(_mainSurface);
    
    SDL_Flip(_mainSurface);
}

void App::cleanup() {
    SDL_FreeSurface(_mainSurface);
    SDL_Quit();
}