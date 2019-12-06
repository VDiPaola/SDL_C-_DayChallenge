//
//  monster.hpp
//  SDL_Program
//
//  Created by Enzo on 05/12/2019.
//  Copyright © 2019 Marta,Anoop,Enzo. All rights reserved.
//

#ifndef monster_hpp
#define monster_hpp

#include <stdio.h>

class monster{
    public:
    int xpos = 500;
    int ypos = 500;
    int width = 64;
    int height = 64;
    int speed = 5;
    int direction = 0;
};

#endif /* monster_hpp */
