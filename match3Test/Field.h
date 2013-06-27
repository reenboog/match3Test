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
typedef vector<ChipVector> ChipMatrix;

class GameScene;

class Field: public Node {
private:
    ChipVector _chips;

    Chip *_firstChip;
    //Chip *_secondChip;
    
    Bool _isSwapping;
    Bool _isDropping;
    
    GameScene *_game;
    Sprite *_chipSelection;
public:
    Field();
    ~Field();
    
    //initialize the field
    void init();
    void setUpGrid();

    void visit();
    void render();
    Bool update(Float dt);
    void moveChips(Float dt);

    Chip* addChip(Int col, Int row);
    Chip* getChipAt(Int col, Int row);
    Chip* getChipAtXandY(Int x, Int y);
    
    void swap(Chip *a, Chip *b);
    void clear(Bool bruteKill = true);
    void shuffle();
    
    void setGameDelegate(GameScene *game);
    
    //mouse stuff
    void onLeftMouseUp(Int x, Int y);
private:
    Bool isItPossibleToPlay();
    ChipMatrix getMatchesIfAny();

    void removeMatchesIfAny();
    void displaceChips(Chip *base);
    void addNewChips();

    Bool doesChipPatternMatch(Int col, Int row, Vec2Collection mustHave, Vec2Collection needOne);
};

#endif /* defined(__match3Test__Field__) */
