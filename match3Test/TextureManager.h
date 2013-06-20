//
//  SurfaceManager.h
//  match3Test
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__SurfaceManager__
#define __match3Test__SurfaceManager__

#include "Types.h"

class TextureManager {
private:
    static TextureManager *__instance;
    
    TextureMap _textures;
private:
    TextureManager();
public:
    ~TextureManager();
    
    GLuint textureByName(string name);

    void purge();
    
    static TextureManager *mngr();
};

#endif /* defined(__match3Test__SurfaceManager__) */
