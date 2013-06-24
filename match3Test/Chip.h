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

class Chip {
private:
    ChipType _type;
public:
    Chip();
    ~Chip();
    
    ChipType getType();
};

#endif /* defined(__match3Test__Chip__) */
