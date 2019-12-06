//
//  screen.cpp
//  SDL_Program
//
//  Created by Enzo on 05/12/2019.
//  Copyright © 2019 Marta,Anoop,Enzo. All rights reserved.
//

#include <stdio.h>
#include "screen.h"
#include <iostream>
#include<time.h>
#include "monster.hpp"
#include <fstream>
using namespace std;

#include <SDL2_image/SDL_image.h>
#include<SDL2/SDL_messagebox.h>

SDL_Texture *playerTexture;
SDL_Texture *appleTexture;
SDL_Texture *monsterTexture;
SDL_Rect srcR, destR;
SDL_Rect ApplesrcR, appleR;
SDL_Rect monstersrcR, monsterR;

monster monster;

bool touchingMonster = false;
bool touchingApple = false;

Screen::Screen(class player*a)
:
player(a)
{
    //constructor
}
Screen::~Screen(){
    //deconstructor
}

void Screen::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    //initialize the screen
    screenWidth = width;
    screenHeight = height;
    int flags = 0;
    //if they want fullscreen set flag to fullscreen
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "screen initialised" << endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            cout << "window created" << endl;
            
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 51, 245, 229, 255);
            cout << "renderer created" << endl;
        }
        isRunning = true;
        
    }else{
        isRunning = false;
    }
    
    //create surface and texture for player
    SDL_Surface *tempSurface = IMG_Load("/Users/enzo/Desktop/Weeks/Week7/SDL_Program/SDL_Program/assets/player.png");
    
    playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if(playerTexture){
        cout << "player loaded" << endl;
    }
    
    
    //create surface and texture for apple
    tempSurface = IMG_Load("/Users/enzo/Desktop/Weeks/Week7/SDL_Program/SDL_Program/assets/apple.png");
    
    appleTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if(playerTexture){
        cout << "apple loaded" << endl;
    }
    
    //create surface and texture for monster
    tempSurface = IMG_Load("/Users/enzo/Desktop/Weeks/Week7/SDL_Program/SDL_Program/assets/monster.png");

    monsterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if(playerTexture){
        cout << "apple loaded" << endl;
    }
    
    //sets initial apple position
    appleR.x = 100;
    appleR.y = 100;

}

void Screen::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    

    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        //player controls
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_w:
                    player->ypos-= player->speed;
                    break;
                case SDLK_a:
                    player->xpos -= player->speed;
                    break;
                case SDLK_s:
                    player->ypos+= player->speed;
                    break;
                case SDLK_d:
                    player->xpos += player->speed;
                    break;

            }
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            break;
        
        defualt:
            break;
    }
}

void Screen::update(){
    srand(time(0));
    destR.w = 128;
    destR.h = 128;
    destR.x = player->xpos;
    destR.y = player->ypos;
    
    appleR.w = 32;
    appleR.h = 32;
    
    monsterR.w = monster.width;
    monsterR.h = monster.height;
    
    
    //if the player is inside the apple
    if( (touchingApple == false) && ( ( (destR.x + destR.w/2) > appleR.x) && ( (destR.x + destR.w/3) < (appleR.x + appleR.w) ) ) && ( ( (destR.y + destR.h/2) > (appleR.y - appleR.h) ) && ( (destR.y + destR.h/5) < (appleR.y + appleR.h) ) ) ) {
        //touching apple
        //add score and update in file
        touchingApple = true;
        player->score++;
        //score file
        ofstream myfile;
        myfile.open ("Desktop/score.txt");
        myfile << player->score;
        myfile.close();
        //randomly sets position of apple
        int rndX = rand()%((screenWidth-50)-0 + 1) + 0;
        int rndY = rand()%((screenHeight-50)-0 + 1) + 0;
        appleR.x = rndX;
        appleR.y = rndY;
    }else{
        touchingApple = false;
    }
    
    //if the player is touching monster
    if((touchingMonster == false) && ( ( (destR.x + destR.w/2) > monsterR.x) && ( (destR.x + destR.w/3) < (monsterR.x + monsterR.w) ) ) && ( ( (destR.y + destR.h/2) > (monsterR.y - monsterR.h) ) && ( (destR.y + destR.h/5) < (monsterR.y + monsterR.h) ) ) ) {
        //touching monster
        //take away score and update in file
        touchingMonster = true;
        player->score--;
        //score file
        ofstream myfile;
        myfile.open ("Desktop/score.txt");
        myfile << player->score;
        myfile.close();
        //makes bg red when monster touches player
        changeBGColour(255, 0, 0, 255);
       
    }else{
        //not touching monster
        touchingMonster = false;
        changeBGColour(51, 245, 229, 255);
    }
    
    
    //monster movements
    bool directionDoesntWork = true;
    while(directionDoesntWork){
        directionDoesntWork = false;
        
        //change temp direction to see where its going
        int tempX = monsterR.x;
        int tempY = monsterR.y;
        switch(monster.direction){
            case 0:
            tempY -= monster.speed;
            break;
            case 1:
            tempY -= monster.speed;
            tempX += monster.speed;
            break;
            case 2:
            tempX += monster.speed;
            break;
            case 3:
            tempY += monster.speed;
            tempX += monster.speed;
            break;
            case 4:
            tempY += monster.speed;
            break;
            case 5:
            tempY += monster.speed;
            tempX -= monster.speed;
            break;
            case 6:
            tempX -= monster.speed;
            break;
            case 7:
            tempY -= monster.speed;
            tempX -= monster.speed;
            break;
        }
        
        
    if( (tempX < 1) || ( (tempX + monsterR.w) > screenWidth-5 ) || (tempY < 1) || ( (tempY+monsterR.h) > screenHeight-5 ) ){
        //monster out of bounds change direction
        int rndDir = rand()%(7-0 + 1) + 0;
        monster.direction = rndDir;
        directionDoesntWork = true;
        
    }
        
    }
    
    //update monsters position
    switch(monster.direction){
        case 0:
        monster.ypos -= monster.speed;
        break;
        case 1:
        monster.ypos -= monster.speed;
        monster.xpos += monster.speed;
        break;
        case 2:
        monster.xpos += monster.speed;
        break;
        case 3:
        monster.ypos += monster.speed;
        monster.xpos += monster.speed;
        break;
        case 4:
        monster.ypos += monster.speed;
        break;
        case 5:
        monster.ypos += monster.speed;
        monster.xpos -= monster.speed;
        break;
        case 6:
        monster.xpos -= monster.speed;
        break;
        case 7:
        monster.ypos -= monster.speed;
        monster.xpos -= monster.speed;
        break;
    }
    
    monsterR.x = monster.xpos;
    monsterR.y = monster.ypos;

}


void Screen::render(){
    
    SDL_RenderClear(renderer);
    //add stuff to be renderered

    //renders player
    SDL_RenderCopy(renderer, playerTexture, nullptr, &destR);
    SDL_RenderCopy(renderer, appleTexture, nullptr, &appleR);
    SDL_RenderCopy(renderer, monsterTexture, nullptr, &monsterR);
 

    SDL_RenderPresent(renderer);
    
    
}

void Screen::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    cout << "screen ended" << endl;
}

void Screen::changeBGColour(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
