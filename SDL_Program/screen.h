//
//  screen.h
//  SDL_Program
//
//  Created by Enzo on 05/12/2019.
//  Copyright © 2019 Marta,Anoop,Enzo. All rights reserved.
//

#ifndef screen_h
#define screen_h

#include <SDL2/SDL.h>
#include "player.hpp"


class Screen{
    public:
    Screen(class player *a);
    ~Screen();
    
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();
    
    void changeBGColour(int r, int g, int b, int a);
    
    bool running(){return isRunning;};
    
    private:
    bool isRunning;
    
    int screenHeight;
    int screenWidth;
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    player* player;
    
    
};

#endif /* screen_h */
