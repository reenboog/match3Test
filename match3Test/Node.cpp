//
//  Node.cpp
//  kingTest
//
//  Created by Alex Gievsky on 18.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#include "Node.h"

Node::Node() {
    init();
}

Node::~Node() {
    cleanup();
}


Bool Node::init() {
    _pos = {0, 0};
    _active = true;
    _hidden = false;
    
    _tag = 0;
    _z = 0;
    
    _parent = nullptr;

    return true;
}

void Node::cleanup() {
    for(Node *child: _children) {
        delete child;
    }
    
    _children.clear();
}

void Node::visit(SDL_Surface *dst) {
    
    if(_hidden) {
        return;
    }
    
    //let's keep all the children unsorted fo simplicity
    for(Node *node: _children) {
        if(node->getZ() < 0) {
            node->visit(dst);
        }
    }
    
    render(dst);
    
    //sorry, but too lazy to calculate the displaceent of the first positive element
    //let's leave this for another test
    for(Node *node: _children) {
        if(node->getZ() >= 0) {
            node->visit(dst);
        }
    }
}

void Node::render(SDL_Surface *dst) {
    //override me
}

Bool Node::update(Float dt) {
    return true;
}

void Node::reorderChildren() {
    //?
}

Bool Node::isChild(Node *child) {
    return find(_children.begin(), _children.end(), child) != _children.end();;
}

Node* Node::getParent() {
    return _parent;
}

void Node::setParent(Node *newParent) {
    //assume we don't share any children wetween parents
    //to keep simplicity
    if(_parent) {
        _pos -= _parent->getPos();
    }
    
    _parent = newParent;
    
    if(newParent) {
        _pos += newParent->getPos();
    }
}

Bool Node::addChild(Node *child) {
    
    if(isChild(child)) {
        return false;
    }
    
    _children.push_back(child);
    child->setParent(this);
        
    return true;
}

Bool Node::removeChild(Node *child) {
    if(!isChild(child)) {
        return false;
    }
    
    child->setParent(NULL);
    
    auto it = find(_children.begin(), _children.end(), child);
    
    _children.erase(it);
    
    delete child;
    
    return true;
}

void Node::setZ(Int z) {
    _z = z;
    
    //reorder
}

Int Node::getZ() {
    return _z;
}

void Node::setPos(Vector2 pos) {
    _pos = pos;
    
    if(_parent) {
        _pos += _parent->getPos();
    }
    
    //recalulate bounds
    updateGeometry();
}

Vector2 Node::getPos() {
    return _pos;
}

void Node::updateGeometry() {
    
}
