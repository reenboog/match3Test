//
//  SurfaceManager.cpp
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "TextureManager.h"

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

TextureManager* TextureManager::__instance = nullptr;

TextureManager::~TextureManager() {
    purge();
}

TextureManager::TextureManager() {
    //fake for a while
}

TextureManager* TextureManager::mngr() {
    if(__instance == nullptr) {
        __instance = new TextureManager();
    }
    
    return __instance;
}

void TextureManager::purge() {
    for(auto tex: _textures) {
        glDeleteTextures(1, &tex.second);
    }
    
    _textures.clear();
}

GLuint TextureManager::textureByName(string name) {
    auto it = _textures.find(name);
    
    if(it == _textures.end()) {
        SDL_Surface *surf = IMG_Load(name.c_str());
        
        if(surf) {
            GLuint texture = -1;
            GLenum texture_format;
            GLint  nOfColors = -1;
            
            if((surf->w & (surf->w - 1)) != 0) {
                printf("warning: %s's width is not a power of 2\n", name.c_str());
            }
            
            if ((surf->h & (surf->h - 1)) != 0) {
                printf("warning: %s's height is not a power of 2\n", name.c_str());
            }
            
            nOfColors = surf->format->BytesPerPixel;
            
            if(nOfColors == 4) {
                if(surf->format->Rmask == 0x000000ff) {
                    texture_format = GL_RGBA;
                } else {
                    texture_format = GL_BGRA;
                }
            } else if(nOfColors == 3) {
                if(surf->format->Rmask == 0x000000ff) {
                    texture_format = GL_RGB;
                } else {
                    texture_format = GL_BGR;
                }
            } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
            }
            
            glGenTextures( 1, &texture );
            
            glBindTexture(GL_TEXTURE_2D, texture);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surf->w, surf->h, 0,
                         texture_format, GL_UNSIGNED_BYTE, surf->pixels);
            
            SDL_FreeSurface(surf);
            
            _textures.insert({name, texture});
            
            return texture;
            
        } else {
            printf("erorr loading image: %s", name.c_str());
            return -1;
        }
    } else {
        return it->second;
    }
}