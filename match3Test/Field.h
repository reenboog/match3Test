//
//  Field.h
//  match3Test
//
//  Created by Alex Gievsky on 20.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef __match3Test__Field__
#define __match3Test__Field__

#include "Types.h"
#include "Node.h"
#include "Chip.h"

typedef vector<Chip *> ChipVector;

class Field: public Node {
private:
    ChipVector _chips;
public:
    Field();
};

#endif /* defined(__match3Test__Field__) */
