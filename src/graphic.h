//
// Created by PoriaKP on 1/19/2022.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "main.h"
#ifndef MYF_GRAPHIC_H
#define MYF_GRAPHIC_H
extern int x0_click,y0_click;
extern int x1_click,y1_click;
extern const int MAX_NUM_OF_SOLDIERS_AT_ALL;
extern int NUM_OF_SOLDIERS;
extern const int soldiers_speed;
extern const int soldiers_r;
extern int arrived_flag;
extern int end_backup;
extern int time_flag;

void drawBox(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color);
int click (SDL_Event event);
int is_valid_start(map mps);
int is_valid_end(map mps,int start);
int check_soldiers_len(double x_soldiers[],double y_soldiers[],int j);
int is_arrived (int x,int y,tile c);
int color_check(tile s,tile e);
void send_soldiers(map* c,int start,int end,SDL_Renderer *sdlRenderer,double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],int* final__flag);

#endif //MYF_GRAPHIC_H
