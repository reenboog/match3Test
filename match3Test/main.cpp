////
////  main.m
////  match3Test
////
////  Created by Alex Gievsky on 18.06.13.
////  Copyright (c) 2013 reenboog. All rights reserved.
////
//
//#import <Cocoa/Cocoa.h>
//
//int main(int argc, char *argv[])
//{
//    return NSApplicationMain(argc, (const char **)argv);
//}



#include <SDL/SDL.h>
#include "App.h"

int main(int argc, char ** argv) {
    App app;
    return app.run();
}

