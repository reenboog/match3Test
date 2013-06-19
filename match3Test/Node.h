//
//  Node.h
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __kingTest__Node__
#define __kingTest__Node__

#include <SDL/SDL.h>
#include "Types.h"

class Node {
private:
    Vector2 _pos;
    Bool _active;
    Bool _hidden;
    
    Int _tag;
    Int _z;
    
    Node *_parent;
    NodePool _children;
private:
    void reorderChildren();
    Bool isChild(Node *child);
public:
    Node();
    virtual ~Node();
public:
    virtual Bool init();
    virtual void cleanup();
    
    void visit(SDL_Surface *dst);
    virtual void render(SDL_Surface *dst);
    virtual Bool update(Float dt);
    //
    Node* getParent();
    void setParent(Node *parent);
    
    Bool addChild(Node *child);
    Bool removeChild(Node *child);
    //
    void setZ(Int z);
    Int getZ();
    
    void setPos(Vector2 pos);
    Vector2 getPos();
    
    virtual void updateGeometry();
};

#endif /* defined(__kingTest__Node__) */
