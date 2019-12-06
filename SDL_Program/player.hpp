//
//  player.hpp
//  SDL_Program
//
//  Created by Enzo on 05/12/2019.
//  Copyright © 2019 Marta,Anoop,Enzo. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <string>

class player{
    public:
    int health = 100;
    std::string name = "default";
    
    player(std::string Newname);
    
    void move(int x, int y);
    
    int xpos = 0;
    int ypos = 0;
    int speed = 20;
    int score = 0;
    
    
};

#endif /* player_hpp */
