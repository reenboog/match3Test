//
//  Types.h
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef kingTest_Types_h
#define kingTest_Types_h

#include <vector>
#include <string>
#include <map>

#include <OpenGL/OpenGL.h>

using namespace std;

typedef char Char;
typedef int Int;
typedef bool Bool;
typedef float Float;
typedef double Double;

class Node;

enum ChipType {
    CT_Red,
    CT_Green,
    CT_Blue,
    CT_Yellow,
    CT_Pink
};

enum ChipState {
    CS_Init,
    CS_Normal,
    CS_Dying,
    CS_Dead
};

struct Vector2 {
    Float x, y;
    
    Bool operator == (const Vector2 &r) {
        return x == r.x && y == r.y;
    }

    Vector2 operator +(const Vector2 &r) {
        Vector2 result{x + r.x, y + r.y};
        return result;
    }

    Vector2& operator +=(const Vector2 &r) {
        x = x + r.x;
        y = y + r.y;
        
        return *this;
    }

    Vector2 operator -() const {
        Vector2 result = *this;
        result.x = -x;
        result.y = -y;
        
        return result;
    }

    Vector2& operator -=(const Vector2 &r) {
        *this += -r;
        return *this;
    }
};
    
typedef vector<Node *> NodePool;
typedef map<string, GLuint> TextureMap;
typedef vector<Vector2> Vec2Collection;
    
#define v2(x, y) (Vector2{(Float)x, (Float)y})

inline Float cut(Float num, Float min, Float max) {
    if(num < min)
    {
        num = min;
    } else if(num > max) {
        num = max;
    }
    return num;
}

struct Size2 {
    Int w, h;
};

struct Rect4 {
    Float x, y, w, h;
};
    
struct UV {
    Float u, v;
};
    
struct UVRect {
    UV _0;
    UV _1;
};

#endif
