
#include <iostream>
#include <SDL2/SDL.h>

#include "screen.h"
#include "player.hpp"
#include <fstream>

using namespace std;

Screen *screen = nullptr;

const char* title = "game";
const int XPOS = 0;
const int YPOS = 0;

const int WIDTH = 600;
const int HEIGHT = 600;

const bool FULLSCREEN = false;


int main() {
    //limit framerate
    const int FPS = 120;
    const int frameDelay = 1000/FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    //score file
    ofstream myfile;
    myfile.open ("Desktop/score.txt");
    myfile << "0";
    myfile.close();

    
    
    //creates player object and passes a reference into the screen object
    player player("steve");
    screen = new Screen(&player);
    
    //initialise screen (title, x, y, width, height, fullscreen)
    screen->Init(title, XPOS, YPOS, WIDTH, HEIGHT, FULLSCREEN);
    
    //while the screen is running do the game loop
    while(screen->running()){
        
        
        frameStart = SDL_GetTicks();
        screen->handleEvents();
        screen->update();
        screen->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    
    screen->clean();
    
    return 0;
}
