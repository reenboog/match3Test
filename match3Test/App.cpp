//
//  App.cpp
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "App.h"
#include "TextureManager.h"

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "GameScene.h"
#include "Constants.h"

#include <SDL_image/SDL_image.h>

App::~App() {
    delete _scene;
    delete TextureManager::mngr();
}

App::App() {
    _mainSurface = nullptr;
    _running = true;
    _leftMouseDown = false;
    _scene = nullptr;
    
    _oldTime = 0;
    _currentTime = 0;
}

Int App::run() {
    if(init() == false) {
        return -1;
    }
    
    SDL_Event event;
    
    _currentTime = SDL_GetTicks();
    
    while(_running) {
        _oldTime = _currentTime;
        _currentTime = SDL_GetTicks();
        
        Float dt = (_currentTime - _oldTime) / 1000.0f;
        
        while(SDL_PollEvent(&event)) {
            onEvent(&event);
        }
        
        loop(dt);
        render();
    }
    
    cleanup();
    
    return 0;
}

Bool App::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    
    if((_mainSurface = SDL_SetVideoMode(kScreenWidth, kScreenHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == nullptr) {
        return false;
    }
    
    glClearColor(0, 0, 0, 0);
    
    glViewport(0, 0, kScreenWidth, kScreenHeight);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, kScreenWidth, kScreenHeight, 0, 1, -1);
    
    glMatrixMode(GL_MODELVIEW);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glLoadIdentity();
    
    _scene = new GameScene();
    _scene->init();
    
    return true;
}

void App::onEvent(SDL_Event *event) {
    if(event->type == SDL_QUIT) {
        _running = false;
    } else if(event->type == SDL_MOUSEBUTTONDOWN) {
        if(event->button.button == SDL_BUTTON_LEFT) {
            _leftMouseDown = true;
            _scene->onLeftMouseDown(event->button.x, event->button.y);
        } else {
            //right button is down
        }
    } else if(event->type == SDL_MOUSEBUTTONUP) {
        if(event->button.button == SDL_BUTTON_LEFT) {
            _leftMouseDown = false;
            _scene->onLeftMouseUp(event->button.x, event->button.y);
        } else {
            //right button is up
        }
    } else if(event->type == SDL_MOUSEMOTION) {
        if(_leftMouseDown) {
            _scene->onLeftMouseDragged(event->motion.x, event->motion.y);
        } else {
            _scene->onMouseMove(event->motion.x, event->motion.y);
        }
    }
}

void App::loop(Float dt) {
    _scene->update(dt);
}

void App::render() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    _scene->visit();
    
    SDL_GL_SwapBuffers();
}

void App::cleanup() {
    SDL_FreeSurface(_mainSurface);
    SDL_Quit();
}