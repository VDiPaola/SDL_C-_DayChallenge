//
//  player.cpp
//  SDL_Program
//
//  Created by Enzo on 05/12/2019.
//  Copyright © 2019 Marta,Anoop,Enzo. All rights reserved.
//

#include "player.hpp"


player::player(std::string Newname){
    name = Newname;
}

void player::move(int x, int y){
    xpos += x;
    ypos += y;
}

