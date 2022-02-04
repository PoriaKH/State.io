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
extern float soldiers_speed_team1;
extern float soldiers_speed_team2;
extern float soldiers_speed_team3;
extern float soldiers_speed_team4;

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
void send_soldiers(map* c,int start,int end,SDL_Renderer *sdlRenderer,double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],int* final__flag,int on_potion,int tile0,int tile1,int* on_potion_pointer,int* using_potion_pointer,time_t* power_start_pointer,float* soldiers_speed_team1_pointer,float* soldiers_speed_team2_pointer,float* soldiers_speed_team3_pointer,float* soldiers_speed_team4_pointer,int power_num,int* who_is_using_potion_pointer);
void draw_image(SDL_Renderer *sdlRenderer,tile tile0,tile tile1,int power_num);
int potion_check(double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],tile tile0,tile tile1);
void draw_image_2(SDL_Renderer *sdlRenderer,int power_num);
#endif //MYF_GRAPHIC_H
