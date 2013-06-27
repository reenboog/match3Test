//
//  Chip.h
//  match3Test
//
//  Created by Alex Gievsky on 20.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__Chip__
#define __match3Test__Chip__

#include "Types.h"
#include "Node.h"
#include "Sprite.h"

class Chip: public Node {
private:
    ChipType _type;
    ChipState _state;
    Sprite *_sprite;
    
    Vector2 _gridCoords;
public:
    Chip(ChipType type);
    ~Chip();
    
    void setType(ChipType type);
    void setGridCoords(Int col, Int row);
    void setGridCoords(Vector2 coords);

    Vector2 getGridCoords();

    ChipType getType();
    
    Bool update(Float dt);
    
    ChipState getState();
    
    void die();
private:
    void setState(ChipState state);
    UVRect uvRectForChipType(ChipType type);
};

#endif /* defined(__match3Test__Chip__) */
