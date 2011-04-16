#include "gui.h"
#include "resources.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include <SDL_ttf.h>

using namespace std;

static SDL_Surface* screen = NULL;
static TTF_Font* font = NULL;
static TTF_Font* consoleFont = NULL;

bool initGUI()
{
  if( SDL_Init(SDL_INIT_VIDEO) <0 )
    return false;
  
  screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
  
  if(screen == NULL)
    return false;
  
  if( TTF_Init() < 0)
    return false;
  
  font=TTF_OpenFont("arial.ttf", 8);
  if(font == NULL)
    return false;
  
  consoleFont=TTF_OpenFont("arial.ttf", 20);
  if(consoleFont == NULL)
    return false;
}

void clearScreen()
{
  SDL_Rect dest;
  dest.x = dest.y = 0;
  dest.w = 1024;
  dest.h = 768;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 255, 255, 255));
}

void renderMap(Game& g)
{
  SDL_Surface* land = loadImage("images/land.png");
  SDL_Surface* water = loadImage("images/water.png");
  
  SDL_Rect dest;
  
  dest.w = 19;
  dest.h = 19;
  
  for(int i = 0; i < g.states[0].tiles.size(); i++)
  {
    if(g.states[0].tiles[i].id == 0) continue;
    dest.x = g.states[0].tiles[i].x * 19;
    dest.y = g.states[0].tiles[i].y * 19;
      
    if(g.states[0].tiles[i].type)
    {
     SDL_BlitSurface(water, NULL, screen, &dest);
    }
    else
    {
      SDL_BlitSurface(land, NULL, screen, &dest);
    }
  }
}

void drawText(Game& g, int turn)
{
  stringstream message;
  SDL_Rect dest;
  dest.x = 760;
  dest.y = 0;
  SDL_Surface* image;
  SDL_Color purple = {255,0,255};
  SDL_Color black = {0,0,0};
  
  message << "Player 1 gold: ";
  message << g.states[turn].players[0].gold;
  
  image = TTF_RenderText_Solid(consoleFont, message.str().c_str(), black);
  SDL_BlitSurface(image, NULL, screen, &dest);
  dest.y += image->h;
  SDL_FreeSurface(image);
  
  message.str("");
  
  message << "Player 2 gold: ";
  message << g.states[turn].players[1].gold;
  
  image = TTF_RenderText_Solid(consoleFont, message.str().c_str(), purple);
  SDL_BlitSurface(image, NULL, screen, &dest);
  dest.y += image->h;
  SDL_FreeSurface(image);
}

void renderTurn(Game& g, int turn)
{
  
  SDL_Surface* ship = loadImage("images/ship.png");
  SDL_Surface* image = NULL;
  SDL_Rect dest;
  SDL_Color yellow = {255,255,0};
  SDL_Color purple = {255,0,255};
  SDL_Color black = {0,0,0};
  SDL_Color color;
  char buf[9];
  dest.w = 19;
  dest.h = 19;
  int owner[40][40];
  int gold[40][40];
  int pirates[40][40];
  
  for(int i = 0; i < 40; i++)
  {
    for(int j = 0; j < 40; j++)
    {
      owner[i][j] = 0;
      gold[i][j] = 0;
      pirates[i][j] = 0;
    }
  }
  
  clearScreen();
  renderMap(g);
  
  for(int i = 0; i < g.states[turn].ports.size(); i++)
  {
    if(g.states[turn].ports[i].id == 0) continue;
    if(g.states[turn].ports[i].owner == 0)
    {
      image = loadImage("images/port1.png");
    }
    else if(g.states[turn].ports[i].owner == 1)
    {
      image = loadImage("images/port2.png");
    }
    else
    {
      image = loadImage("images/port3.png");
    }
    dest.x = g.states[turn].ports[i].x * 19;
    dest.y = g.states[turn].ports[i].y * 19;
    SDL_BlitSurface(image, NULL, screen, &dest);
  }
  
  for(int i = 0; i < g.states[turn].treasures.size(); i++)
  {
    if(g.states[turn].treasures[i].id == 0) continue;
    gold[g.states[turn].treasures[i].x][g.states[turn].treasures[i].y] += g.states[turn].treasures[i].gold;
  }
  
  for(int i = 0; i < g.states[turn].pirates.size(); i++)
  {
    if(g.states[turn].pirates[i].id == 0) continue;
    pirates[g.states[turn].pirates[i].x][g.states[turn].pirates[i].y] += 1;
    gold[g.states[turn].pirates[i].x][g.states[turn].pirates[i].y] += g.states[turn].pirates[i].gold;
    owner[g.states[turn].pirates[i].x][g.states[turn].pirates[i].y] = g.states[turn].pirates[i].owner;
  }
  
  for(int i = 0; i < g.states[turn].ships.size(); i++)
  {
    if(g.states[turn].ships[i].id == 0) continue;
    gold[g.states[turn].ships[i].x][g.states[turn].ships[i].y] += g.states[turn].ships[i].gold;
    dest.x = g.states[turn].ships[i].x * 19;
    dest.y = g.states[turn].ships[i].y * 19;
    SDL_BlitSurface(ship, NULL, screen, &dest);
  }
  
  for(int i = 0; i < 40; i++)
  {
    for(int j = 0; j < 40; j++)
    {
      if(gold[i][j] != 0)
      {
        dest.x = i * 19 + 10;
        dest.y = j * 19 + 19;
        
        sprintf(buf, "%d", gold[i][j]);
        image = TTF_RenderText_Solid(font, buf, yellow);
        dest.y -= image->h;
        dest.x -= image->w / 2;
        SDL_BlitSurface(image, NULL, screen, &dest);
        SDL_FreeSurface(image);
      }
      if(pirates[i][j] != 0)
      {
        dest.x = i * 19 + 10;
        dest.y = j * 19;
        
        if(owner[i][j] == 0)
        {
          color = black;
        }
        else if(owner[i][j] == 1)
        {
          color = purple;
        }
        else
        {
          color = yellow;
        }
          
        sprintf(buf, "%d", pirates[i][j]);
        
        image = TTF_RenderText_Solid(font, buf, color);
        dest.x -= image->w / 2;
        SDL_BlitSurface(image, NULL, screen, &dest);
        SDL_FreeSurface(image);
      }
    }
  }
  
  drawText(g, turn);
  
  SDL_Flip(screen);
}

void mainLoop(Game& g)
{
  int turn = 0;
  
  while(true)
  {
    renderTurn(g, turn);
    
    SDL_Event event;
    while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
          printf("Mouse button %d pressed at (%d,%d)\n",
                event.button.button, event.button.x, event.button.y);
          break;
        case SDL_QUIT:
          return;
      }
    }
    
    SDL_Delay(100);
    
    turn++;
    
    if (turn >= g.states.size())
      break;
  }
}