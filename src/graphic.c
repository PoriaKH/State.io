//
// Created by PoriaKP on 1/19/2022.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "graphic.h"
#include "main.h"
#include "math.h"
#include <stdio.h>

int x0_click,y0_click;
int x1_click,y1_click;
int LEN_BETWEEN_SOLDIERS = 10;

void drawBox(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color) {
    Sint16 width1 = 1000 * y / 8;
    Sint16 height1 = 800 * x / 8;
    boxColor(sdlRenderer, width1, height1, width1 + 1000 / 8, height1 + 800 / 8, color);
}

int click (SDL_Event event){
    int flag=0;


    if(SDL_PollEvent(&event)){
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            x0_click = event.button.x;
            y0_click = event.button.y;
        }
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            flag=1;
            x1_click = event.button.x;
            y1_click = event.button.y;
        }
    }

    if(flag == 1)
        return 1;
    else
        return 0;
}
int is_valid_start(map mps){
    int flag1 = -1;
    for(int i = 1; i <= NUM_OF_TILES_FOR_EACH_MAP; i++)
    {
        if(x0_click <= mps.tiles[i].x2 && x0_click >= mps.tiles[i].x1 && y0_click <= mps.tiles[i].y2 && y0_click >= mps.tiles[i].y1)
        {
            flag1 = i;
            break;
        }
    }
    if(flag1 != -1)
    {
        if(mps.tiles[flag1].soldiers == 0)
            flag1 = -1;
    }
    return flag1;
}
int is_valid_end(map mps,int start){
    if(start == -1)
        return -1;

    int flag2 = -1;
    for(int j = 1; j <= NUM_OF_TILES_FOR_EACH_MAP; j++)
    {
        if(x1_click <= mps.tiles[j].x2 && x1_click >= mps.tiles[j].x1 && y1_click <= mps.tiles[j].y2 && y1_click >= mps.tiles[j].y1)
        {
            flag2 = j;
            break;
        }
    }

    if(flag2 != -1) {
        if (mps.tiles[flag2].soldiers >= MAX_NUM_OF_SOLDIERS_AT_ALL) {
            printf("mps.tiles[start].soldiers = %d  end = %d\n",mps.tiles[start].soldiers,mps.tiles[flag2].soldiers);
            if (mps.tiles[start].b_color == mps.tiles[flag2].b_color) {
                flag2 = -1;
            }
        }
    }
    return flag2;
}
int check_soldiers_len(double x_soldiers[],double y_soldiers[],int i){
    if(len_cal(x_soldiers[i-1],x_soldiers[i],y_soldiers[i-1],y_soldiers[i]) < LEN_BETWEEN_SOLDIERS)
        return 0;
    else
        return 1;
}
int is_arrived (int x,int y,tile c){
    int len_from_circle = (x - c.x_o) * (x - c.x_o) + (y - c.y_o) * (y - c.y_o) ;

    if(len_from_circle <= cubes_r)
        return 1;
    else
        return 0;
}
int color_check(tile s,tile e){
    if(s.c_color == e.c_color)
        return 1;
    else
        return -1;
}