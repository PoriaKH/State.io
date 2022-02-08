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
#include <SDL_image.h>
#include <string.h>
#include <SDL_ttf.h>
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
int y_pointer = 324;
int x_pointer = 530;
int y_pointer_2 = 324;
char name[25];
int onmenu = 1;
int on_get_players = 1;
int ongetname = 1;
int on_maps = 0;
int on_map0 = 0;
int on_map1 = 0;
int on_map2 = 0;
int on_map3 = 0;
int on_leaderboard = 0;
int on__exit = 0;
int start_game = 0;
TTF_Font* font;
TTF_Font* font2;
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
    for(int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++)
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
    for(int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++)
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
void send_soldiers(map* c,int start,int end,SDL_Renderer *sdlRenderer,double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],int* final__flag,int on_potion,int tile0,int tile1,int* on_potion_pointer,int* using_potion_pointer,time_t* power_start_pointer,float* soldiers_speed_team1_pointer,float* soldiers_speed_team2_pointer,float* soldiers_speed_team3_pointer,float* soldiers_speed_team4_pointer,int power_num,int* who_is_using_potion_pointer){
    float soldiers_speed;
    if(c->tiles[start].team == 1)
        soldiers_speed = soldiers_speed_team1;
    if(c->tiles[start].team == 2)
        soldiers_speed = soldiers_speed_team2;
    if(c->tiles[start].team == 3)
        soldiers_speed = soldiers_speed_team3;
    if(c->tiles[start].team == 4)
        soldiers_speed = soldiers_speed_team4;

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

                    if(*using_potion_pointer)
                        if(power_num == 2)
                            if(c->tiles[end].team == *who_is_using_potion_pointer)
                                friend_or_enemy = 1;

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
                    if(*on_potion_pointer)
                        if(j == 0){
                            if(potion_check(x_soldiers,y_soldiers,c->tiles[tile0],c->tiles[tile1])){
                                if(power_num == 4){
                                    if(c->tiles[start].team == 1) {
                                        *who_is_using_potion_pointer = 1;
                                    }
                                    if(c->tiles[start].team == 2) {
                                        *who_is_using_potion_pointer = 2;
                                    }
                                    if(c->tiles[start].team == 3) {
                                        *who_is_using_potion_pointer = 3;
                                    }
                                    if(c->tiles[start].team == 4) {
                                        *who_is_using_potion_pointer = 4;
                                    }
                                }
                                if(power_num == 1){
                                    if(c->tiles[start].team == 1){
                                        *soldiers_speed_team2_pointer *= 0.3;
                                        *soldiers_speed_team3_pointer *= 0.3;
                                        *soldiers_speed_team4_pointer *= 0.3;
                                        *who_is_using_potion_pointer = 1;
                                    }
                                    if(c->tiles[start].team == 2){
                                        *soldiers_speed_team1_pointer *= 0.3;
                                        *soldiers_speed_team3_pointer *= 0.3;
                                        *soldiers_speed_team4_pointer *= 0.3;
                                        *who_is_using_potion_pointer = 2;
                                    }
                                    if(c->tiles[start].team == 3){
                                        *soldiers_speed_team1_pointer *= 0.3;
                                        *soldiers_speed_team2_pointer *= 0.3;
                                        *soldiers_speed_team4_pointer *= 0.3;
                                        *who_is_using_potion_pointer = 3;
                                    }
                                    if(c->tiles[start].team == 4){
                                        *soldiers_speed_team1_pointer *= 0.3;
                                        *soldiers_speed_team2_pointer *= 0.3;
                                        *soldiers_speed_team3_pointer *= 0.3;
                                        *who_is_using_potion_pointer = 4;
                                    }
                                }
                                if(power_num == 2){
                                    if(c->tiles[start].team == 1) {
                                        *who_is_using_potion_pointer = 1;
                                    }
                                    if(c->tiles[start].team == 2) {
                                        *who_is_using_potion_pointer = 2;
                                    }
                                    if(c->tiles[start].team == 3) {
                                        *who_is_using_potion_pointer = 3;
                                    }
                                    if(c->tiles[start].team == 4) {
                                        *who_is_using_potion_pointer = 4;
                                    }
                                }
                                if(power_num == 3){
                                    V_x *= 2.5;
                                    V_y *= 2.5;
                                    if(c->tiles[start].team == 1) {
                                        *soldiers_speed_team1_pointer *= 2.5;
                                        *who_is_using_potion_pointer = 1;
                                    }
                                    if(c->tiles[start].team == 2) {
                                        *soldiers_speed_team2_pointer *= 2.5;
                                        *who_is_using_potion_pointer = 2;
                                    }
                                    if(c->tiles[start].team == 3) {
                                        *soldiers_speed_team3_pointer *= 2.5;
                                        *who_is_using_potion_pointer = 3;
                                    }
                                    if(c->tiles[start].team == 4) {
                                        *soldiers_speed_team4_pointer *= 2.5;;
                                        *who_is_using_potion_pointer = 4;
                                    }
                                }

                                *on_potion_pointer = 0;
                                *using_potion_pointer = 1;
                                *power_start_pointer = time(NULL);
                            }
                        }
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
                if(*using_potion_pointer)
                    if(power_num == 2)
                        if(c->tiles[end].team == *who_is_using_potion_pointer)
                            friend_or_enemy = 1;

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
void draw_image(SDL_Renderer *sdlRenderer,tile tile0,tile tile1,int power_num)
{
    SDL_Texture *my_Texture;
    if(power_num == 1)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power1.png");
    if(power_num == 2)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power2.png");
    if(power_num == 3)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power3.png");
    if(power_num == 4)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power4.png");

    if(!my_Texture)
        printf("image not loaded!\n");

    int w1,h1;
    SDL_QueryTexture(my_Texture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;

    texr1.h = 23;
    texr1.w = 30;

    texr1.x = avg(tile0.x_o,tile1.x_o) - texr1.w / 2;
    texr1.y = avg(tile0.y_o,tile1.y_o) - texr1.h / 2;

    SDL_RenderCopy(sdlRenderer, my_Texture, NULL, &texr1);
    SDL_DestroyTexture(my_Texture);
}
int potion_check(double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL],tile tile0,tile tile1){
    Sint16 w = 30;
    Sint16 h = 23;

    Sint16 x_up = avg(tile0.x_o,tile1.x_o) - w / 2;
    Sint16 x_down = avg(tile0.x_o,tile1.x_o) + w / 2;

    Sint16 y_up = avg(tile0.y_o,tile1.y_o) - h / 2;
    Sint16 y_down = avg(tile0.y_o,tile1.y_o) + h / 2;


    if(((int)x_soldiers[0] >= x_up && (int)x_soldiers[0] <= x_down && (int)y_soldiers[0] >= y_up && (int)y_soldiers[0] <= y_down) || ((int)x_soldiers[NUM_OF_SOLDIERS - 1] >= x_up && (int)x_soldiers[NUM_OF_SOLDIERS - 1] <= x_down && (int)y_soldiers[NUM_OF_SOLDIERS - 1] >= y_up && (int)y_soldiers[NUM_OF_SOLDIERS - 1] <= y_down))
        return 1;
    else
        return 0;
}
void draw_image_2(SDL_Renderer *sdlRenderer,int power_num)
{
    SDL_Texture *my_Texture;
    if(power_num == 1)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power1.png");
    if(power_num == 2)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power2.png");
    if(power_num == 3)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power3.png");
    if(power_num == 4)
        my_Texture = IMG_LoadTexture(sdlRenderer,"../images/potions/power4.png");

    if(!my_Texture)
        printf("image not loaded!\n");

    int w1,h1;
    SDL_QueryTexture(my_Texture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;

    texr1.h = 42;
    texr1.w = 30;

    texr1.x = 41;
    texr1.y = 1;

    SDL_RenderCopy(sdlRenderer, my_Texture, NULL, &texr1);
    SDL_DestroyTexture(my_Texture);
}
void draw_image_final(SDL_Renderer *sdlRenderer,int xp,int yp,char* address,int width,int height)
{
    int n = strlen(address);
    char char_array[n + 1];

    strcpy(char_array, address);
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture(sdlRenderer, char_array);
    if(!myTexture)
        printf("image not loaded !\n");

    int w1,h1;
    SDL_QueryTexture(myTexture,NULL,NULL,&w1,&h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy(sdlRenderer, myTexture, NULL, &texr1);
    SDL_DestroyTexture(myTexture);
}
void mainmenu_event(int* y_pointer) {
    if(on_you_won || on_you_lost){
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            on_you_won = 0;
            on_you_lost = 0;
        }
        if(e.type == SDL_MOUSEBUTTONUP) {
            on_you_won = 0;
            on_you_lost = 0;
        }
            if (e.type == SDL_KEYDOWN) {
                on_you_won = 0;
                on_you_lost = 0;
        }
    }
    if(on_leaderboard){
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_BACKSPACE:
                    on_leaderboard = 0;
                    onmenu = 1;
                    break;
                case SDLK_ESCAPE:
                    on_leaderboard = 0;
                    onmenu = 1;
                    break;
            }
        }
    }
    if (onmenu == 1 && on_get_players == 0){
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_DOWN:
                    if (*y_pointer != 464)
                        *y_pointer += 70;
                    break;
                case SDLK_UP:
                    if (*y_pointer != 324)
                        *y_pointer -= 70;
                    break;
                case SDLK_RETURN:
                    switch (*y_pointer) {
                        case 324:
                            onmenu = 0;
                            on_maps = 1;
                            break;
                        case 394:
                            onmenu = 0;
                            on_leaderboard = 1;
                            break;
                        case 464:
                            onmenu = 0;
                            on__exit = 1;
                            start_game = 1;
                    }
            }
        }
    } if (on_maps && NUM_OF_PLAYERS != 2) {
        SDL_Event e;
        SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_DOWN:
                        if (*y_pointer != 534)
                            *y_pointer += 70;
                        break;
                    case SDLK_UP:
                        if (*y_pointer != 324)
                            *y_pointer -= 70;
                        break;
                    case SDLK_BACKSPACE:
                        on_maps = 0;
                        onmenu = 1;
                        *y_pointer = 324;
                        break;
                        case SDLK_SPACE: {

                            if (*y_pointer == 324) {
                                on_map0 = 1;
                                on_maps = 0;
                            }
                            if (*y_pointer == 394) {
                                on_map1 = 1;
                                on_maps = 0;
                            } else if (*y_pointer == 464) {
                                on_map2 = 1;
                                on_maps = 0;
                            } else if (*y_pointer == 534) {
                                int n = rand() % 3;
                                if (n == 0) {
                                    on_map0 = 1;
                                    on_maps = 0;
                                } else if (n == 1) {
                                    on_map1 = 1;
                                    on_maps = 0;
                                } else if (n == 2) {
                                    on_map2 = 1;
                                    on_maps = 0;
                                }
                            }
                            break;
                        }
                }
            }
        }
    if (on_maps && NUM_OF_PLAYERS == 2) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_DOWN:
                    if (*y_pointer != 604)
                        *y_pointer += 70;
                    break;
                case SDLK_UP:
                    if (*y_pointer != 324)
                        *y_pointer -= 70;
                    break;
                case SDLK_BACKSPACE:
                    on_maps = 0;
                    onmenu = 1;
                    *y_pointer = 324;
                    break;
                case SDLK_SPACE: {

                    if (*y_pointer == 324) {
                        on_map0 = 1;
                        on_maps = 0;
                    }
                    if (*y_pointer == 394) {
                        on_map1 = 1;
                        on_maps = 0;
                    } else if (*y_pointer == 464) {
                        on_map2 = 1;
                        on_maps = 0;
                    } else if (*y_pointer == 534) {
                        on_map3 = 1;
                        on_maps = 0;
                    } else if (*y_pointer == 604) {
                        int n = rand() % 3;
                        if (n == 0) {
                            on_map0 = 1;
                            on_maps = 0;
                        } else if (n == 1) {
                            on_map1 = 1;
                            on_maps = 0;
                        } else if (n == 2) {
                            on_map2 = 1;
                            on_maps = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
    if(on_map0){
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.key.keysym.sym == SDLK_BACKSPACE){
                on_maps = 1;
                on_map0 = 0;
        }
        if(e.key.keysym.sym == SDLK_RETURN){
            the_chosen_map = 0;
            on_map0 = 0;
            onmenu = 0;
            start_game = 1;
        }
    }
    if(on_map1) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.key.keysym.sym == SDLK_BACKSPACE) {
            on_maps = 1;
            on_map1 = 0;
        }
        if(e.key.keysym.sym == SDLK_RETURN){
            the_chosen_map = 1;
            on_map1 = 0;
            onmenu = 0;
            start_game = 1;
        }
    }
    if(on_map2) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.key.keysym.sym == SDLK_BACKSPACE) {
            on_maps = 1;
            on_map2 = 0;
        }
        if(e.key.keysym.sym == SDLK_RETURN){
            the_chosen_map = 2;
            on_map2 = 0;
            onmenu = 0;
            start_game = 1;
        }
    }
    if(on_map3) {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.key.keysym.sym == SDLK_BACKSPACE) {
            on_maps = 1;
            on_map3 = 0;
        }
        if(e.key.keysym.sym == SDLK_RETURN){
            the_chosen_map = 3;
            on_map3 = 0;
            onmenu = 0;
            start_game = 1;
        }
    }
    if(on_get_players == 1){
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_DOWN:
                    if (*y_pointer != 464)
                        *y_pointer += 70;
                    break;
                case SDLK_UP:
                    if (*y_pointer != 324)
                        *y_pointer -= 70;
                    break;
                case SDLK_RETURN:
                    switch (*y_pointer) {
                        case 324:
                            on_get_players = 0;
                            NUM_OF_PLAYERS = 2;
                            break;
                        case 394:
                            on_get_players = 0;
                            NUM_OF_PLAYERS = 3;
                            break;
                        case 464:
                            on_get_players = 0;
                            NUM_OF_PLAYERS = 4;
                    }
            }
        }
    }
}
void show_map(SDL_Renderer* sdlRenderer,int map_num,map mps[]){
    for(int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {
        boxColor(sdlRenderer, mps[map_num].tiles[i].x1, mps[map_num].tiles[i].y1, mps[map_num].tiles[i].x2, mps[map_num].tiles[i].y2,mps[map_num].tiles[i].b_color);
        filledCircleColor(sdlRenderer, mps[map_num].tiles[i].x_o, mps[map_num].tiles[i].y_o, cubes_r, mps[map_num].tiles[i].c_color);

        SDL_SetRenderDrawColor(sdlRenderer,0xff,0xff,0xff,0xff);
        SDL_Rect the_rect = {mps[map_num].tiles[i].x1,mps[map_num].tiles[i].y1,mps[map_num].tiles[i].height,mps[map_num].tiles[i].width};
        SDL_RenderDrawRect(sdlRenderer,&the_rect);
    }
    SDL_RenderPresent(sdlRenderer);
}
void choose_players(SDL_Renderer* sdlRenderer)
{
    int* y_pointer_2_ptr = & y_pointer_2;
    while(on_get_players) {
        mainmenu_event(y_pointer_2_ptr);
        draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
        draw_image_final(sdlRenderer, 300, 295, "../images/menu/1.png", 200, 58);
        draw_image_final(sdlRenderer, 300, 365, "../images/menu/2.png", 200, 58);
        draw_image_final(sdlRenderer, 300, 435, "../images/menu/3.png", 200, 58);
        draw_image_final(sdlRenderer,227,20,"../images/menu/enternum.png",345,44);
        filledCircleRGBA(sdlRenderer, x_pointer, y_pointer_2, 24, 255, 0, 0, 255);
        SDL_RenderPresent(sdlRenderer);
    }
}
void create_text(SDL_Renderer *sdlRenderer,char* text,int x_text,int y_text,SDL_Color color)
{
    SDL_Surface *my_surface = TTF_RenderText_Solid(font2, text,color);
    SDL_Texture *my_texture = SDL_CreateTextureFromSurface(sdlRenderer,my_surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(my_texture,NULL,NULL,&texW,&texH);
    SDL_Rect dstrec = {x_text,y_text,texW,texH};

    SDL_RenderCopy(sdlRenderer,my_texture,NULL,&dstrec);

    SDL_DestroyTexture(my_texture);
    SDL_FreeSurface(my_surface);
}
void mainmenu(SDL_Renderer* sdlRenderer,map mps[])
{
    font = TTF_OpenFont("../fonts/arial.ttf",50);
    font2 = TTF_OpenFont("../fonts/arial.ttf",35);
    int maxLen = 17;
    int editingName = 0;

    if(!font)
        printf("font not loaded\n");
    SDL_Color color = {0,0,0};
    SDL_Color color2 = {255,255,0};
    SDL_Color color3 = {255,255,255};

    SDL_StartTextInput();
    while(!start_game) {
        int *y_pointer_ptr = &y_pointer;

        while (ongetname) {
            draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
            SDL_Event Event;
            SDL_Surface *surfaceName;
            if (strlen(name) == 0) {
                surfaceName = TTF_RenderText_Solid(font, "Enter your name ...", color);
            }
            if (strlen(name) > 0) {
                surfaceName = TTF_RenderText_Solid(font, name, color);
            }
            int nameW = 0;
            int nameH = 0;
            int nameX = 50;
            int nameY = 100;
            SDL_Texture *textureName = SDL_CreateTextureFromSurface(sdlRenderer, surfaceName);
            SDL_QueryTexture(textureName, NULL, NULL, &nameW, &nameH);

            SDL_Rect dstrectName = {nameX, nameY, nameW, nameH};


            SDL_Rect borderName;
            borderName.x = nameX;
            borderName.y = nameY;
            borderName.w = nameW;
            borderName.h = nameH;

            SDL_Color colorBorder1;
            if (editingName == true) {
                colorBorder1.r = 255;
                colorBorder1.g = 255;
                colorBorder1.b = 0;
                colorBorder1.a = 255;
            }
            if (editingName == false && strlen(name) == 0) {
                colorBorder1.r = 255;
                colorBorder1.g = 0;
                colorBorder1.b = 0;
                colorBorder1.a = 255;
            }
            if (editingName == false && strlen(name) > 0) {
                colorBorder1.r = 0;
                colorBorder1.g = 255;
                colorBorder1.b = 0;
                colorBorder1.a = 255;
            }
            SDL_SetRenderDrawColor(sdlRenderer, colorBorder1.r, colorBorder1.g, colorBorder1.b, colorBorder1.a);
            SDL_RenderFillRect(sdlRenderer, &borderName);


            SDL_RenderCopy(sdlRenderer, textureName, NULL, &dstrectName);


            while (SDL_PollEvent(&Event)) {
                if (Event.type == SDL_MOUSEBUTTONDOWN) {
                    if (Event.button.button == SDL_BUTTON_LEFT) {
                        if (Event.button.x > nameX && Event.button.x < nameX + nameW && Event.button.y > nameY &&
                            Event.button.y < nameY + nameH) {

                            editingName = true;
                        }
                    }
                }
                if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_RETURN && editingName == false &&
                    strlen(name) > 0) {
                    ongetname = false;
                } else if ((Event.type == SDL_TEXTINPUT || Event.type == SDL_KEYDOWN) && editingName == true) {
                    if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_RETURN && strlen(name) > 0) {
                        SDL_DestroyTexture(textureName);
                        SDL_FreeSurface(surfaceName);
                        editingName = false;
                    }
                    if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_BACKSPACE && strlen(name) > 0 &&
                        strlen(name) <= maxLen) {
                        name[strlen(name) - 1] = '\0';
                    } else if (Event.type == SDL_TEXTINPUT && strlen(name) < maxLen) {
                        name[strlen(name)] = Event.text.text[0];
                        name[strlen(name) + 1] = '\0';
                    }
                }
            }
            SDL_RenderPresent(sdlRenderer);

        }
        while (onmenu) {
            mainmenu_event(y_pointer_ptr);
            draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
            draw_image_final(sdlRenderer, 300, 295, "../images/menu/maps.png", 200, 58);
            draw_image_final(sdlRenderer, 300, 365, "../images/menu/leaderboard.png", 200, 58);
            draw_image_final(sdlRenderer, 300, 435, "../images/menu/exit.png", 200, 58);
            filledCircleRGBA(sdlRenderer, x_pointer, y_pointer, 24, 255, 0, 0, 255);
            SDL_RenderPresent(sdlRenderer);

        }
        while (on_maps) {
            mainmenu_event(y_pointer_ptr);
            if(NUM_OF_PLAYERS != 2) {
                draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
                draw_image_final(sdlRenderer, 300, 295, "../images/menu/map1.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 365, "../images/menu/map2.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 435, "../images/menu/map3.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 505, "../images/menu/random.png", 200, 58);
            }
            else {
                draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
                draw_image_final(sdlRenderer, 300, 295, "../images/menu/map1.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 365, "../images/menu/map2.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 435, "../images/menu/map3.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 505, "../images/menu/map4.png", 200, 58);
                draw_image_final(sdlRenderer, 300, 575, "../images/menu/random.png", 200, 58);
            }
            draw_image_final(sdlRenderer,227,20,"../images/menu/pressspace.png",345,44);
            filledCircleRGBA(sdlRenderer, x_pointer, y_pointer, 24, 255, 0, 0, 255);
            SDL_RenderPresent(sdlRenderer);
        }
        while(on_map0){
            mainmenu_event(y_pointer_ptr);
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            show_map(sdlRenderer,0,mps);
        }
        while(on_map1){
            mainmenu_event(y_pointer_ptr);
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            show_map(sdlRenderer,1,mps);
        }
        while(on_map2){
            mainmenu_event(y_pointer_ptr);
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            show_map(sdlRenderer,2,mps);
        }
        while(on_map3){
            mainmenu_event(y_pointer_ptr);
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            show_map(sdlRenderer,3,mps);
        }
        while(on_leaderboard){
            mainmenu_event(y_pointer_ptr);
            draw_image_final(sdlRenderer, 0, 0, "../images/menu/menu.jpg", 800, 800);
            draw_image_final(sdlRenderer, 10, 10, "../images/menu/players.png", 283, 69);
            draw_image_final(sdlRenderer, 313, 10, "../images/menu/points.png", 283, 69);
            draw_image_final(sdlRenderer, 616, 10, "../images/menu/rank2.png", 126, 69);
            int y_text = 90;
            for(int i = 0; i < players_counter; i++){
                int x_text = 10 + 283/2 - strlen(players[i].user_name) * 10;
                create_text(sdlRenderer,players[i].user_name,x_text,y_text,color2);
                y_text += 50;
                if(y_text >= 750)
                    break;
            }
            y_text = 90;
            for(int i = 0; i < players_counter; i++){
                char text[5];
                for(int j = 0; j < 5; j++)
                    text[j] = '\0';
                sprintf(text,"%d",players[i].point);
                int x_text = 313 + 283/2 - strlen(text) * 10 - 10;
                create_text(sdlRenderer,text,x_text,y_text,color2);
                y_text += 50;
                if(y_text >= 750)
                    break;
            }
            y_text = 90;
            for(int i = 0; i < players_counter; i++){
                char text[5];
                for(int j = 0; j < 5; j++)
                    text[j] = '\0';
                sprintf(text,"%d",players[i].rank);
                int x_text = 616 + 126/2 - strlen(text) * 10;
                create_text(sdlRenderer,text,x_text,y_text,color2);
                y_text += 50;
                if(y_text >= 750)
                    break;
            }
            SDL_RenderPresent(sdlRenderer);
        }
    }
}