//
// Created by PoriaKP on 1/18/2022.
//

#ifndef MYF_MAIN_H
#define MYF_MAIN_H
#define MAX_TILES 35
#include <SDL_quit.h>
#include <SDL_render.h>
extern int NUM_OF_TILES_FOR_EACH_MAP;
extern const int cubes_r;
extern int NUM_OF_MAPS;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int the_chosen_map;
extern int NUM_OF_PLAYERS;
extern int players_counter;
extern int on_you_won;
extern int on_you_lost;

typedef struct tile{
    int width;
    int height;
    Sint16 x1,x2;
    Sint16 y1,y2;
    Uint32 b_color;
    Uint32 c_color;
    Sint16 x_o,y_o;
    Sint16 r;
    int team;
    int soldiers;
}tile;
typedef struct map{
    tile tiles[MAX_TILES];
}map;
typedef struct names{
    char user_name[35];
    int point;
    int rank;
}names;
names players[50];
#endif //MYF_MAIN_H
