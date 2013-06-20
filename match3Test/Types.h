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

typedef vector<Node *> NodePool;
typedef map<string, GLuint> TextureMap;

struct Vector2 {
    Int x, y;
    
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
    
#define v2(x, y) (Vector2{x, y})

struct Size2 {
    Int w, h;
};

struct Rect4 {
    Float x, y, w, h;
};
    
struct UV {
    Float u, v;
};

#endif
