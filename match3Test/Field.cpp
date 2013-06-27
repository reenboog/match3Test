//
//  Field.cpp
//  match3Test
//
//  Created by Alex Gievsky on 20.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Field.h"
#include "Constants.h"
#include "GameScene.h"

#include "SoundManager.h"

#include <random>

Field::~Field() {
    
}

Field::Field() {
    _game = nullptr;
    
    _firstChip = nullptr;
    //_secondChip = nullptr;
    _chipSelection = nullptr;
    
    _isSwapping = false;
    _isDropping = false;
}

void Field::init() {
    srand((int)time(NULL));

    this->removeAllChildren(true);
    
    _chips.resize(kFieldWidth * kFieldHeight);
    
    _chipSelection = new Sprite("chipSelection.png");
    _chipSelection->setHidden(true);
    _chipSelection->setZ(1);

    this->addChild(_chipSelection);
    this->setPos(kFieldBasePoint);
    
    setUpGrid();
}

void Field::setUpGrid() {
    //not the best algorithm: it doesn't completely exclude the potentiality of being stuck
    //within the loop
    while(1) {
        for(int i = 0; i < kFieldHeight; ++i) {
            for(int j = 0; j < kFieldWidth; ++j) {
                addChip(j, i);
            }
        }
        
        if(!getMatchesIfAny().empty()) {
            clear();
            continue;
        }
        
        if(!isItPossibleToPlay()) {
            clear();
            continue;
        }
        
        break;
    }
}

Chip* Field::addChip(Int col, Int row) {
    //all the chips ared by default just for simplicity and convenience
    Chip *chip = new Chip(CT_Red);
    chip->setGridCoords(col, row);
    chip->setPos(v2(col * (kChipSpacing + kChipWidth) + kChipWidth / 2, row * (kChipSpacing + kChipHeight) + kChipHeight / 2));

    //it is possible to experiment with better distribution,
    //but let's keep it simple for a while
    chip->setType(static_cast<ChipType>(rand() % kNumOfChipTypes));
    
    _chips[row * kFieldWidth + col] = chip;
    this->addChild(chip);
    
    //chip->gotoAndStop(chip->getType());
    
    return chip;
}

Chip* Field::getChipAt(Int col, Int row) {
    //assume we have not errors here
    
    return _chips[row * kFieldWidth + col];
    
    //return nullptr;
}

Chip* Field::getChipAtXandY(Int x, Int y) {
    
    x -= kFieldBasePoint.x;
    y -= kFieldBasePoint.y;
    
    Int col = (x + kChipSpacing) / (kChipWidth + kChipSpacing);
    Int row = (y + kChipSpacing) / (kChipHeight + kChipSpacing);
    
    return getChipAt(col, row);
}

void Field::swap(Chip *a, Chip *b) {
    auto swapper = [&](Chip *_1, Chip *_2) {
        Vector2 tmpCoords = _1->getGridCoords();
        
        _1->setGridCoords(_2->getGridCoords());
        _2->setGridCoords(tmpCoords);
        
        _chips[_1->getGridCoords().y * kFieldWidth + _1->getGridCoords().x] = _1;
        _chips[_2->getGridCoords().y * kFieldWidth + _2->getGridCoords().x] = _2;
    };
    
    swapper(a, b);
    
    if(getMatchesIfAny().empty()) {
        //swap(b, a) ?
        swapper(a, b);
    } else {
        _isSwapping = true;
    }
}

void Field::clear(Bool bruteKill) {
    for(Chip *chip: _chips) {
        if(bruteKill) {
            this->removeChild(chip, bruteKill);
        } else {
            chip->die();
        }
    }
    
    _chips.clear();
    _chips.resize(kFieldWidth * kFieldHeight);
}

void Field::shuffle() {
    clear(false);
    setUpGrid();
    //addNewChips();
}

void Field::setGameDelegate(GameScene *game) {
    _game = game;
}

Bool Field::update(Float dt) {
    
    moveChips(dt);
    
    return true;
}


void Field::visit() {
    //crop chips at the top
    glEnable(GL_SCISSOR_TEST);
    glScissor(320, 150, kFieldAreaWidth, kFieldAreaHeight);

    Node::visit();
    
    glDisable(GL_SCISSOR_TEST);
}

void Field::render() {
    Node::render();
}

void Field::moveChips(Float dt) {
    //dt should be kept in mind!
    Bool moved = false;

    for(Int i = 0; i < kFieldHeight; ++i) {
        for(Int j = 0; j < kFieldWidth; ++j) {

            Chip *chip = _chips[i * kFieldWidth + j];
            if(chip != nullptr) {
                
                Vector2 currentPos = chip->getPos();
                Vector2 requiredPos = v2(chip->getGridCoords().x * (kChipSpacing + kChipWidth) + kChipWidth / 2,
                                         chip->getGridCoords().y * (kChipSpacing + kChipHeight) + kChipHeight / 2);
                //move to the bottom
                if(currentPos.y < requiredPos.y) {
                    //use gravity instead of constant speed
                    Vector2 pos = v2(chip->getPos().x, cut(chip->getPos().y + 750 * dt, currentPos.y, requiredPos.y));
                    
                    chip->setPos(pos); //apply speed here
                    
                    moved = true;
                } else if(currentPos.y > requiredPos.y) {
                    //move to the top
                    //use gravity instead of constant speed
                    Vector2 pos = v2(chip->getPos().x, cut(chip->getPos().y - 350 * dt, requiredPos.y, currentPos.y));
                    
                    chip->setPos(pos); //apply speed here
                    
                    moved = true;
                } else if(currentPos.x < requiredPos.x) {
                    //move to the right
                    //use gravity instead of constant speed
                    Vector2 pos = v2(cut(chip->getPos().x + 350 * dt, currentPos.x, requiredPos.x), chip->getPos().y);
                    
                    chip->setPos(pos); //apply speed here
                    
                    moved = true;
                } else if(currentPos.x > requiredPos.x) {
                    //move to the left
                    //use gravity instead of constant speed
                    Vector2 pos = v2(cut(chip->getPos().x - 350 * dt, requiredPos.x, currentPos.x), chip->getPos().y);
                    
                    chip->setPos(pos); //apply speed here
                    
                    moved = true;
                }
            }
        }
    }
    
    if(_isDropping && !moved) {
        _isDropping = false;
        removeMatchesIfAny();
    } else if(_isSwapping && !moved) {
        _isSwapping = false;
        removeMatchesIfAny();
    }
}

Bool Field::doesChipPatternMatch(Int col, Int row, Vec2Collection mustHave, Vec2Collection needOne) {
    auto typeMatcher = [&](Int col, Int row, ChipType type) -> Bool {
        if(col < 0 || col > (kFieldWidth - 1) || row < 0 || row > (kFieldHeight - 1)) {
            return false;
        }
        
        return getChipAt(col, row)->getType() == type;
    };
    
    Int numOfMustHave = static_cast<Int>(mustHave.size());
    Chip *currentChip = getChipAt(col, row);
    
    if(currentChip == nullptr) {
        return false;
    }
    
    ChipType currentType = currentChip->getType();
    
    for(Int i = 0; i < numOfMustHave; ++i) {
        if(!typeMatcher(col + mustHave[i].x, row + mustHave[i].y, currentType)) {
            return false;
        }
    }
    
    for(Int i = 0; i < needOne.size(); ++i) {
        if(typeMatcher(col + needOne[i].x, row + needOne[i].y, currentType)) {
            return true;
        }
    }
    
    return false;
}

Bool Field::isItPossibleToPlay() {
        
    for(Int row = 0; row < kFieldHeight; ++row) {
        for(Int col = 0; col < kFieldWidth; ++col) {
            if(doesChipPatternMatch(col, row, {{1, 0}}, {{-2, 0}, {-1, -1}, {-1, 1}, {2, -1}, {2, 1}, {3, 0}})) {
                return true;
            }
            
            if(doesChipPatternMatch(col, row, {{2, 0}}, {{1, -1}, {1, 1}})) {
                return true;
            }
            
            if(doesChipPatternMatch(col, row, {{0, 1}}, {{0, -2}, {-1, -1}, {1, -1}, {-1, 2}, {1, 2}, {0, 3}})) {
                return true;
            }
            
            if(doesChipPatternMatch(col, row, {{0, 2}}, {{-1, 1}, {1, 1}})) {
                return true;
            }
        }
    }
    
    return false;
}

void Field::removeMatchesIfAny() {
    auto matches = getMatchesIfAny();

    Int numOfMatches = static_cast<Int>(matches.size());

    for(Int i = 0; i < numOfMatches; ++i) {
        Int points = kScorePerChip * ((Int)matches[i].size() - 1); //-1 ?
        for(Int j = 0; j < matches[i].size(); ++j) {
            
            Chip *chip = matches[i][j];
            auto chipIt = find(_chips.begin(), _chips.end(), chip);
            
            if(chipIt != _chips.end()) {
                //show scores label and apply fade int/scale effect to it
                //these points should be applied once only by the way
                _game->applyPoints(points);
                
                _chips[chip->getGridCoords().y * kFieldWidth + chip->getGridCoords().x] = nullptr;
                
                displaceChips(chip);
                //would be nice to add this chip to a special list and
                //apply some basic scale/ fade out effect maybe
                //and use removeChild(chip, false) instead
                //this->removeChild(chip);
                chip->die();
                
                SoundManager::mngr()->playEffect("chipBreak.wav");
            }
        }
    }
    
    addNewChips();

    if(matches.empty()) {
        if(!isItPossibleToPlay()) {
            //onGameOver();
            shuffle();
        }
    }
}

void Field::displaceChips(Chip *base) {
    Int baseCol = base->getGridCoords().x;
    Int baseRow = base->getGridCoords().y;

    for(Int row = baseRow - 1; row >= 0; row--) {
        if(getChipAt(baseCol, row) != nullptr) {
            Chip *currentChip = _chips[row * kFieldWidth + baseCol];

            currentChip->setGridCoords(currentChip->getGridCoords().x, currentChip->getGridCoords().y + 1);
            _chips[(row + 1) * kFieldWidth + baseCol] = currentChip;
            _chips[row * kFieldWidth + baseCol] = nullptr;
        }
    }
}

void Field::addNewChips() {
    for(Int col = 0; col < kFieldWidth; ++col) {
        Int numOfMissingChips = 0;
        for(int row = kFieldHeight - 1; row >= 0; row--) {
            if(getChipAt(col, row) == nullptr) {
                
                Chip *newChip = addChip(col, row);
                //row * (kChipSpacing + kChipHeight) + kChipHeight / 2
                newChip->setPos(v2(newChip->getPos().x, -(numOfMissingChips++ * (kChipSpacing + kChipHeight) + kChipHeight / 2)));
                
                _isDropping = true;
            }
        }
    }
}

ChipMatrix Field::getMatchesIfAny() {
    ChipMatrix resultingMatch;
    
    auto checkRows = [&](Int row, Int col) -> ChipVector {
        Chip *chipToCheck = getChipAt(col, row);
        
        ChipVector result;
        result.push_back(chipToCheck);
        
        if(chipToCheck == nullptr) {
            return result;
        }
        
        //todo: add nullptr-chip check
        for(Int i = 1; col + i < kFieldWidth; ++i) {
            Chip *currentChip = getChipAt(col + i, row);
           
            if(currentChip && chipToCheck->getType() == currentChip->getType()) {
                result.push_back(currentChip);
            } else {
                return result;
            }
        }
        
        return result;
    };
    
    auto checkColumns = [&](Int row, Int col) -> ChipVector {
        Chip *chipToCheck = getChipAt(col, row);
        
        ChipVector result;
        result.push_back(chipToCheck);
        
        if(chipToCheck == nullptr) {
            return result;
        }

        for(Int i = 1; row + i < kFieldHeight; ++i) {
            Chip *currentChip = getChipAt(col, row + i);

            if(currentChip && chipToCheck->getType() == currentChip->getType()) {
                result.push_back(currentChip);
            } else {
                return result;
            }
        }
        
        return result;
    };
    
    for(Int row = 0; row < kFieldHeight; ++row) {
        //assume our match is invalid in case it consists of less than 3 elements
        //we should skip 2 last rows since they can not
        //make a match of more than 2 elements
        for(Int col = 0; col < kFieldWidth - 2; ++col) {
            auto match = checkRows(row, col);
            if(match.size() > 2) {
                resultingMatch.push_back(match);
                //skip this match
                col += (match.size() - 1);
            }
        }
    }
    
    for(Int col = 0; col < kFieldWidth; ++col) {
        for(Int row = 0; row < kFieldHeight - 2; ++row) {
            auto match = checkColumns(row, col);
            if(match.size() > 2) {
                resultingMatch.push_back(match);
                row += (match.size() - 1);
            }
        }
    }
    
    return resultingMatch;
}

void Field::onLeftMouseUp(Int x, Int y) {
    Chip *chip = getChipAtXandY(x, y);
    
    if(chip == nullptr) {
        return;
    }
    
    SoundManager::mngr()->playEffect("btnClick.wav");
    
    //this is the first time we select a chip
    if(_firstChip == nullptr) {
        _chipSelection->setHidden(false);
        _chipSelection->setPos(chip->getPos());
        _firstChip = chip;
    } else if(_firstChip == chip) {
        //deselect a previously selected chip
        _chipSelection->setHidden(true);
        _firstChip = nullptr;
    } else {
        //we selected another chip: it is possible it's a neighbour chip
        _chipSelection->setHidden(true);
        
        Vector2 firstCoords = _firstChip->getGridCoords();
        Vector2 secondCoords = chip->getGridCoords();
        //check if this is the same row and neighbour column
        if(firstCoords.y == secondCoords.y && abs(firstCoords.x - secondCoords.x) == 1) {
            swap(_firstChip, chip);
            _firstChip = nullptr;
        } else if(firstCoords.x == secondCoords.x && abs(firstCoords.y - secondCoords.y) == 1) {
            swap(_firstChip, chip);
            _firstChip = nullptr;
        } else {
            //this is a distant chip, so select it and deselect the previous one
            _firstChip = chip;
            _chipSelection->setPos(chip->getPos());
            _chipSelection->setHidden(false);
        }
    }
}