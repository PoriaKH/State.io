//
// Created by PoriaKP on 1/19/2022.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "graphic.h"
#include "main.h"
#include "math.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int x0_click,y0_click;
int x1_click,y1_click;
int LEN_BETWEEN_SOLDIERS = 10;
int final_flag2 = 0;
int final_flag3 = 1;
int arrived_flag = 0;
int j_backup = 0;
int end_backup = -1;
int delta = 0;
int time_flag = 0;

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
void send_soldiers(map* c,int start,int end,SDL_Renderer *sdlRenderer,double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],int* final__flag){


    if(final_flag2 == 0) {
        final_flag2 = 1;

        NUM_OF_SOLDIERS = c->tiles[start].soldiers / 2;

        if(c->tiles[start].soldiers % 2 == 1)
            delta = 1;

        if(delta)
            NUM_OF_SOLDIERS = c->tiles[start].soldiers / 2 + 1;

        for(int i = 0; i < NUM_OF_SOLDIERS ; i++) {
            x_soldiers[i] = c->tiles[start].x_o;
            y_soldiers[i] = c->tiles[start].y_o;
        }
    }

    double len = len_cal(c->tiles[start].x_o,c->tiles[end].x_o,c->tiles[start].y_o,c->tiles[end].y_o);
    double V_x = (double)soldiers_speed * (c->tiles[end].x_o - c->tiles[start].x_o) / len;
    double V_y = (double)soldiers_speed * (c->tiles[end].y_o - c->tiles[start].y_o) / len;

    if(final_flag3 == 1) {
        for (int i = 0; i < NUM_OF_SOLDIERS; i++) {
            for (int j = 0; j <= i; j++) {
                if(i != 0){
                    //check
                    if(!check_soldiers_len(x_soldiers,y_soldiers,i)){
                        i--;
                    }
                }
                x_soldiers[j] += V_x;
                y_soldiers[j] += V_y;

            }
            for (int j = j_backup; j <= i; j++) {
                bool arrived_0 = is_arrived(x_soldiers[j],y_soldiers[j],c->tiles[end]);

                if(arrived_0) {
                    j_backup = j + 1;
                    arrived_flag = 1;
// friend -> 1 , enemy -> -1
                    int friend_or_enemy = color_check(c->tiles[start],c->tiles[end]);

                    if(friend_or_enemy == 1) {
                        if(c->tiles[end].soldiers + 2 <= MAX_NUM_OF_SOLDIERS_AT_ALL)
                            c->tiles[end].soldiers += 2;
                    }
                    else if(friend_or_enemy == -1) {
                        if(c->tiles[end].soldiers - 2 >= 0)
                            c->tiles[end].soldiers -= 2;

                        else{
                            c->tiles[end].c_color = c->tiles[start].c_color;
                            c->tiles[end].b_color = c->tiles[start].b_color;
                            c->tiles[end].team = c->tiles[start].team;
                        }
                    }


                    char text[10];
                    sprintf(text, "%d", c->tiles[end].soldiers);
                    if (counter(c->tiles[end].soldiers) == 0 || counter(c->tiles[end].soldiers) == 1)
                        stringColor(sdlRenderer, c->tiles[end].x_o - 3, c->tiles[end].y_o - 3, text, 0xff000000);

                    if (counter(c->tiles[end].soldiers) == 2)
                        stringColor(sdlRenderer, c->tiles[end].x_o - 8, c->tiles[end].y_o - 3, text, 0xff000000);

                    if(counter(c->tiles[i].soldiers) == 3)
                        stringColor(sdlRenderer, c->tiles[end].x_o - 11, c->tiles[end].y_o - 3, text, 0xff000000);

                }

                if(!arrived_0){
                    filledCircleColor(sdlRenderer, x_soldiers[j], y_soldiers[j], soldiers_r, c->tiles[start].c_color);
                }
            }
            c->tiles[start].soldiers = 0;
            SDL_RenderPresent(sdlRenderer);

            if (i == NUM_OF_SOLDIERS - 1)
                final_flag3 = 0;
        }
    }

    if(final_flag3 == 0) {
        for (int j = j_backup; j < NUM_OF_SOLDIERS; j++) {
            x_soldiers[j] += V_x;
            y_soldiers[j] += V_y;

            bool arrived = is_arrived(x_soldiers[j],y_soldiers[j],c->tiles[end]);
            if(arrived) {
                j_backup = j + 1;
                arrived_flag = 1;
                int friend_or_enemy = color_check(c->tiles[start], c->tiles[end]);
                int damage = 2;

                if(j == NUM_OF_SOLDIERS - 1){
                    if(delta == 1){
                        damage = 1;
                    }
                }

                if (friend_or_enemy == 1) {
                    if(c->tiles[end].soldiers + damage <= MAX_NUM_OF_SOLDIERS_AT_ALL)
                        c->tiles[end].soldiers += damage;
                }
                else if (friend_or_enemy == -1) {
                    if (c->tiles[end].soldiers - damage >= 0)
                        c->tiles[end].soldiers -= damage;

                    else {
                        c->tiles[end].c_color = c->tiles[start].c_color;
                        c->tiles[end].b_color = c->tiles[start].b_color;
                        c->tiles[end].team = c->tiles[start].team;

                        c->tiles[end].soldiers = damage - c->tiles[end].soldiers - 1;
                    }
                }

                char text[10];
                sprintf(text, "%d", c->tiles[end].soldiers);
                if (counter(c->tiles[end].soldiers) == 0 || counter(c->tiles[end].soldiers) == 1)
                    stringColor(sdlRenderer, c->tiles[end].x_o - 3, c->tiles[end].y_o - 3, text, 0xff000000);

                if (counter(c->tiles[end].soldiers) == 2)
                    stringColor(sdlRenderer, c->tiles[end].x_o - 8, c->tiles[end].y_o - 3, text, 0xff000000);

                if(counter(c->tiles[end].soldiers) == 3)
                    stringColor(sdlRenderer, c->tiles[end].x_o - 11, c->tiles[end].y_o - 3, text, 0xff000000);
            }

            if(!arrived)
                filledCircleColor(sdlRenderer, x_soldiers[j], y_soldiers[j], soldiers_r, c->tiles[start].c_color);

            else if(j == NUM_OF_SOLDIERS - 1){
                *final__flag = 0;
                final_flag2 = 0;
                final_flag3 = 1;
                j_backup = 0;
                arrived_flag = 0;
                end_backup = -1;
                delta = 0;
            }

        }
    }
    SDL_RenderPresent(sdlRenderer);
}