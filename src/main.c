#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "math.h"
#include "graphic.h"
#define MIN_X 50
#define MIN_Y 70


#ifdef main
#undef main
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
const int NUM_OF_MAPS = 3;
const int min_width_of_tile = 70;
const int min_height_of_tile = 70;
const int cubes_r = 20;
const int soldiers_r = 4;
float soldiers_speed_team1 = 0.07;
float soldiers_speed_team2 = 0.07;
float soldiers_speed_team3 = 0.07;
float soldiers_speed_team4 = 0.07;
int NUM_OF_PLAYERS = 2;
const int FIRST_NUM_OF_SOLDIERS = 12;
const int FIRST_NUM_OF_SOLDIERS_TEAM_0 = 10;
const int MAX_NUM_OF_SOLDIERS_TO_REACH = 50;
const int MAX_NUM_OF_SOLDIERS_TO_REACH_TEAM0 = 10;
const int MAX_NUM_OF_SOLDIERS_AT_ALL = 500;

int the_chosen_map = 0;
int winner = -1;
int NUM_OF_SOLDIERS = 0;
int NUM_OF_TILES_FOR_EACH_MAP;
int team0[4] = {-1,-1,-1,-1};
int team1[2] = {-1,-1};
int team2[2] = {-1,-1};
int team3[1] = {-1};
int team4[1] = {-1};

Uint32 b_color1 = 0xff000099;             //red
Uint32 c_color1 = 0xff0000ff;

Uint32 b_color2 = 0xaa800000;             //blue
Uint32 c_color2 = 0xFFA50011;

Uint32 b_color3 = 0xFFEF00bb;             //pink
Uint32 c_color3= 0xFFEF00ff;

Uint32 b_color4 = 0x9100FFdd;             //yellow
Uint32 c_color4 = 0xE21ADBff;

Uint32 b_color_team_0 = 0x526D6Faa;
Uint32 c_color_team_0 = 0x526D6Fcc;

void fix(tile* c)
{
    c->width = c->y2 - c->y1;
    c->height = c->x2 - c->x1;
}
void clean(map* c,int num)
{
    for(int i=0;i<=num;i++)
    {
        c->tiles[i].width=0;
        c->tiles[i].height=0;
        c->tiles[i].y2=0;
        c->tiles[i].y1=0;
        c->tiles[i].x1=0;
        c->tiles[i].x2=0;
        c->tiles[i].y_o=0;
        c->tiles[i].x_o=0;
        c->tiles[i].r=0;
    }
}
void second_check(tile* c)
{
    if(c->y2 > SCREEN_WIDTH)
        c->y2 = SCREEN_WIDTH;

    if(c->x2 > SCREEN_HEIGHT)
        c->x2 = SCREEN_HEIGHT;

}
void initialize_teams(map* c)
{
    if(NUM_OF_PLAYERS == 2){
        //blue, red
        //NUM_OF_TILES_FOR_EACH_MAP = 8
        int n1 = rand() % 7 + 1;
        int n2 = rand() % 7 + 1;
        while(n1 == n2){
            n2 = rand() % 7 + 1;
        }
        c->tiles[n1].team = 1;
        c->tiles[n1].b_color = b_color1;
        c->tiles[n1].c_color = c_color1;
        c->tiles[n1].soldiers = FIRST_NUM_OF_SOLDIERS;
        team1[0] = n1;


        c->tiles[n2].team = 1;
        c->tiles[n2].b_color = b_color1;
        c->tiles[n2].c_color = c_color1;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;
        team1[1] = n2;

        int n3 = rand() % 7 + 1;
        while(n3 == n1 || n3 == n2){
            n3 = rand() % 7 + 1;
        }
        int n4 = rand() % 7 + 1;
        while(n4 == n3 || n4 == n2 || n4 == n1){
            n4 = rand() % 7 + 1;
        }

        c->tiles[n3].team = 2;
        c->tiles[n3].b_color = b_color2;
        c->tiles[n3].c_color = c_color2;
        c->tiles[n3].soldiers = FIRST_NUM_OF_SOLDIERS;
        team2[0] = n3;

        c->tiles[n4].team = 2;
        c->tiles[n4].b_color = b_color2;
        c->tiles[n4].c_color = c_color2;
        c->tiles[n4].soldiers = FIRST_NUM_OF_SOLDIERS;
        team2[1] = n4;

        int n5 = rand() % 7 + 1;
        while(n5 == n4 || n5 == n3 || n5 == n2 || n5 == n1){
            n5 = rand() % 7 + 1;
        }
        int n6 = rand() % 7 + 1;
        while(n6 == n5 || n6 == n4 || n6 == n3 || n6 == n2 || n6 == n1){
            n6 = rand() % 7 + 1;
        }
        int i = 1;
        for(;i < NUM_OF_TILES_FOR_EACH_MAP ; i++){
            if(i != n1 && i != n2 && i != n3 && i != n4 && i != n5 && i != n6)
                break;
        }
        int n7 = i;

        c->tiles[n5].team = 0;
        c->tiles[n5].b_color = b_color_team_0;
        c->tiles[n5].c_color = c_color_team_0;
        c->tiles[n5].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[0] = n5;

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[1] = n6;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[2] = n7;
    }
    if(NUM_OF_PLAYERS == 3){
        //blue, red and pink
        //NUM_OF_TILES_FOR_EACH_MAP = 8
        int n1 = rand() % 7 + 1;
        int n2 = rand() % 7 + 1;
        int n3 = rand() % 7 + 1;
        while(n1 == n2){
            n2 = rand() % 7 + 1;
        }
        while(n3 == n1 || n3 == n2){
            n3 = rand() % 7 + 1;
        }
        c->tiles[n1].team = 1;
        c->tiles[n1].b_color = b_color1;
        c->tiles[n1].c_color = c_color1;
        c->tiles[n1].soldiers = FIRST_NUM_OF_SOLDIERS;
        team1[0] = n1;

        c->tiles[n2].team = 2;
        c->tiles[n2].b_color = b_color2;
        c->tiles[n2].c_color = c_color2;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;
        team2[0] = n2;

        c->tiles[n3].team = 3;
        c->tiles[n3].b_color = b_color3;
        c->tiles[n3].c_color = c_color3;
        c->tiles[n3].soldiers = FIRST_NUM_OF_SOLDIERS;
        team3[0] = n3;

        int n4 = rand() % 7 + 1;
        while(n4 == n3 || n4 == n2 || n4 == n1){
            n4 = rand() % 7 + 1;
        }
        int n5 = rand() % 7 + 1;
        while(n5 == n4 || n5 == n3 || n5 == n2 || n5 == n1){
            n5 = rand() % 7 + 1;
        }
        int n6 = rand() % 7 + 1;
        while(n6 == n5 || n6 == n4 || n6 == n3 || n6 == n2 || n6 == n1){
            n6 = rand() % 7 + 1;
        }
        int i = 1;
        for(;i < NUM_OF_TILES_FOR_EACH_MAP ; i++){
            if(i != n1 && i!= n2 && i != n3 && i != n4 && i != n5 && i != n6)
                break;
        }
        int n7 = i;
        c->tiles[n4].team = 0;
        c->tiles[n4].b_color = b_color_team_0;
        c->tiles[n4].c_color = c_color_team_0;
        c->tiles[n4].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[0] = n4;

        c->tiles[n5].team = 0;
        c->tiles[n5].b_color = b_color_team_0;
        c->tiles[n5].c_color = c_color_team_0;
        c->tiles[n5].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[1] = n5;

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[2] = n6;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[3] = n7;
    }
    if(NUM_OF_PLAYERS == 4){
        //blue, red, pink and yellow
        //NUM_OF_TILES_FOR_EACH_MAP = 9
        int n1 = rand() % 7 + 1;
        int n2 = rand() % 7 + 1;
        int n3 = rand() % 7 + 1;
        int n4 = rand() % 7 + 1;
        while(n1 == n2){
            n2 = rand() % 7 + 1;
        }
        while(n3 == n1 || n3 == n2){
            n3 = rand() % 7 + 1;
        }
        while(n4 == n3 || n4 == n2 || n4 == n1){
            n4 = rand() % 7 + 1;
        }
        c->tiles[n1].team = 1;
        c->tiles[n1].b_color = b_color1;
        c->tiles[n1].c_color = c_color1;
        c->tiles[n1].soldiers = FIRST_NUM_OF_SOLDIERS;
        team1[0] = n1;

        c->tiles[n2].team = 2;
        c->tiles[n2].b_color = b_color2;
        c->tiles[n2].c_color = c_color2;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;
        team2[0] = n2;

        c->tiles[n3].team = 3;
        c->tiles[n3].b_color = b_color3;
        c->tiles[n3].c_color = c_color3;
        c->tiles[n3].soldiers = FIRST_NUM_OF_SOLDIERS;
        team3[0] = n3;

        c->tiles[n4].team = 4;
        c->tiles[n4].b_color = b_color4;
        c->tiles[n4].c_color = c_color4;
        c->tiles[n4].soldiers = FIRST_NUM_OF_SOLDIERS;
        team4[0] = n4;

        int n5 = rand() % 7 + 1;
        int n6 = rand() % 7 + 1;
        int n7 = rand() % 7 + 1;
        int n8 = rand() % 7 + 1;
        while(n5 == n4 || n5 == n3 || n5 == n2 || n5 == n1){
            n5 = rand() % 7 + 1;
        }
        while(n6 == n5 || n6 == n4 || n6 == n3 || n6 == n2 || n6 == n1){
            n6 = rand() % 7 + 1;
        }
        while(n7 == n6 || n7 == n5 || n7 == n4 || n7 == n3 || n7 == n2 || n7 == n1){
            n7 = rand() % 7 + 1;
        }
        int i = 1;
        for(;i < NUM_OF_TILES_FOR_EACH_MAP ; i++){
            if(i != n7 && i != n6 && i != n5 && i != n4 && i != n3 && i != n2 && i != n1)
                break;
        }
        n8 = i;
        c->tiles[n5].team = 0;
        c->tiles[n5].b_color = b_color_team_0;
        c->tiles[n5].c_color = c_color_team_0;
        c->tiles[n5].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[0] = n5;

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[1] = n6;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[2] = n7;

        c->tiles[n8].team = 0;
        c->tiles[n8].b_color = b_color_team_0;
        c->tiles[n8].c_color = c_color_team_0;
        c->tiles[n8].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
        team0[3] = n8;
    }
}
int who_is_winner(map c[])
{
    int flag = 0;
    int winner1;
    for(int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++){
        if(c[the_chosen_map].tiles[i].team != 0) {
            winner1 = c[the_chosen_map].tiles[i].team;

            if(flag == 0) {
                winner = winner1;
                flag++;
            }
        }
        if(winner1 != winner && ((winner1 == 1) || (winner == 1)))
            return -1;

        //printf("tile[%d] = %d\n",i,c->tiles[i].team);
    }
    return winner;
}
int main()
{
    // <----> Height
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        printf("SDL_image format not available\n");
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    TTF_Init();

    if(NUM_OF_PLAYERS == 2){
        NUM_OF_TILES_FOR_EACH_MAP = 8;
    }
    if(NUM_OF_PLAYERS == 3){
        NUM_OF_TILES_FOR_EACH_MAP = 8;
    }
    if(NUM_OF_PLAYERS == 4){
        NUM_OF_TILES_FOR_EACH_MAP = 9;
    }

//create map
    map mps[NUM_OF_MAPS];
    for(int k = 0;k < NUM_OF_MAPS ; k++)
    {
        srand(time(NULL));
        int x_lines; //ofoghi
        int y_lines; //amoodi

        if(k == 0){
            x_lines = 5;
            y_lines = 3;
        }
        if(k == 1){
            x_lines = 10;
            y_lines = 5;
        }
        if(k == 2){
            x_lines = 11;
            y_lines = 7;
        }

        int x[y_lines+1];
        int y[x_lines+1];
        tile tls[(x_lines + 1) * (y_lines + 1)];

        for (int i = 0; i <= y_lines; i++) {
            x[i] = rand() % SCREEN_HEIGHT;
            while(x[i] < MIN_X)
            {
                x[i] += rand() % SCREEN_HEIGHT;

                if(x[i] > SCREEN_HEIGHT)
                    x[i] %= SCREEN_HEIGHT;
            }
        }
        for (int i = 0; i <= x_lines; i++) {
            y[i] = rand() % SCREEN_WIDTH;
            while(y[i] < MIN_Y)
            {
                y[i] += rand() % SCREEN_WIDTH;

                if(y[i] > SCREEN_WIDTH)
                    y[i] %= SCREEN_WIDTH;
            }
        }
        sort(x, y_lines+1);
        sort(y, x_lines+1);

        int map_tiles_counter = 0;

        tls[0].x1 = 0;
        tls[0].y1 = 0;
        tls[0].x2 = x[0];
        tls[0].y2 = y[0];
        tls[0].x_o = avg(tls[0].x2,tls[0].x1);
        tls[0].y_o = avg(tls[0].y2,tls[0].y1);
        tls[0].height = tls[0].x2 - tls[0].x1;
        tls[0].width = tls[0].y2 - tls[0].y1;

        if(tls[0].height >=70 && tls[0].width >= 70)
        {
            mps[k].tiles[0] = tls[0];
            map_tiles_counter++;
        }



        int counter = 1;
        int base_width = 0;
        int base_height = 0;

        for (int i = 0; i <= x_lines; i++) {
            for (int j = 0; j <= y_lines; j++) {
                tile new;
                new.height = x[j] - base_height;
                base_height = new.height;

                new.width = y[i] - base_width;

                tls[counter].width = new.width;
                tls[counter].height = new.height;
                tls[counter].x1 = x[j];
                tls[counter].y1 = y[i];
                if(j != y_lines)
                {
                    tls[counter].x2 = x[j + 1];
                    if(i != x_lines)
                    {
                        tls[counter].y2 = y[i + 1];
                    }
                    else
                    {
                        tls[counter].y2 = SCREEN_WIDTH;
                    }
                }
                else
                {
                    tls[counter].x2 = SCREEN_HEIGHT;
                    if(i != x_lines)
                    {
                        tls[counter].y2 = y[i+1];
                    }
                    else
                    {
                        tls[counter].y2 = SCREEN_WIDTH;
                    }
                }

////fixing the values
                tile* c = &tls[counter];
                fix(c);
                if(tls[counter].height >= min_height_of_tile && tls[counter].width >= min_width_of_tile)
                {
                    tile* c = &tls[counter];
                    second_check(c);
                    tls[counter].x_o = avg(tls[counter].x1,tls[counter].x2);
                    tls[counter].y_o = avg(tls[counter].y1,tls[counter].y2);
                    mps[k].tiles[map_tiles_counter]= tls[counter];
                    map_tiles_counter++;
                }
                counter++;
            }
            base_height = 0;
            base_width = y[i];

        }
        if(map_tiles_counter < NUM_OF_TILES_FOR_EACH_MAP)
        {
            map* c = &mps[k];
            clean(c,map_tiles_counter);
            k--;
            map_tiles_counter = 0;
            continue;
        }
    }


    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    choose_players(sdlRenderer);
    if(on__exit == 1)
        return 0;

    map* c0 = &mps[0];
    map* c1 = &mps[1];
    map* c2 = &mps[2];
    initialize_teams(c0);
    initialize_teams(c1);
    initialize_teams(c2);

//show menu
    mainmenu(sdlRenderer,mps);
//
    int name_size = strlen(name);
    name[name_size] = '.';
    name[name_size + 1] = 't';
    name[name_size + 2] = 'x';
    name[name_size + 3] = 't';
    name[name_size + 4] = '\0';
    printf("%s",name);

    float soldiers_speed_team1_copy = soldiers_speed_team1;
    float soldiers_speed_team2_copy = soldiers_speed_team2;
    float soldiers_speed_team3_copy = soldiers_speed_team3;
    float soldiers_speed_team4_copy = soldiers_speed_team4;

    int final_flag = 0;
    int final_flag_important = 0;
    int final_flag2 = 0;
    int final_flag3 = 1;
    int arrived_flag = 0;
    int j_backup = 0;
    int end_backup = -1;
    int delta = 0;
    int time_flag = 0;
    int s = -1;
    int e = -1;

    double x_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL];
    double y_soldiers[MAX_NUM_OF_SOLDIERS_AT_ALL];

    time_t time_begin = time(NULL);
    time_t time_begin_for_bots = time(NULL);

    int tile0 = -1;
    int tile1 = -1;
    int power_num = 0;
    int on_potion = 0;
    int using_potion = 0;
    int who_is_using_potion = -1;
    int* who_is_using_potion_pointer = &who_is_using_potion;
    int k = 1;
    time_t power_begin = time(NULL);
    time_t power_end_copy = 0;
    time_t power_start = time(NULL);

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {

        winner = who_is_winner(mps);
        if(winner != -1)
            break;

        int power_flag = 0;
        if(on__exit)
            break;

        time_t time_end = time(NULL);
        time_t power_end = time(NULL);

        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);



        for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {
            boxColor(sdlRenderer, mps[the_chosen_map].tiles[i].x1, mps[the_chosen_map].tiles[i].y1, mps[the_chosen_map].tiles[i].x2, mps[the_chosen_map].tiles[i].y2,
                     mps[the_chosen_map].tiles[i].b_color);

            filledCircleColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o, mps[the_chosen_map].tiles[i].y_o, cubes_r, mps[the_chosen_map].tiles[i].c_color);
            char text[10];
            sprintf(text, "%d", mps[the_chosen_map].tiles[i].soldiers);

            if (arrived_flag == 0) {
                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 0 || counter(mps[the_chosen_map].tiles[i].soldiers) == 1)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 3, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);

                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 2)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 8, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);

                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 3)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 11, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);
            } else if (i != end_backup) {
                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 0 || counter(mps[the_chosen_map].tiles[i].soldiers) == 1)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 3, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);

                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 2)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 8, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);

                if (counter(mps[the_chosen_map].tiles[i].soldiers) == 3)
                    stringColor(sdlRenderer, mps[the_chosen_map].tiles[i].x_o - 11, mps[the_chosen_map].tiles[i].y_o - 3, text, 0xff000000);
            }

            if (time_end - time_begin >= 1) {
                if (mps[the_chosen_map].tiles[i].team != 0) {
                    if (mps[the_chosen_map].tiles[i].soldiers < MAX_NUM_OF_SOLDIERS_TO_REACH) {
                        if(using_potion)
                            if(power_num == 4)
                                if(mps[the_chosen_map].tiles[i].team == who_is_using_potion)
                                    k = 3;
                                else
                                    k = 1;

                        mps[the_chosen_map].tiles[i].soldiers += (time_end - time_begin) * k;
                        if(mps[the_chosen_map].tiles[i].soldiers > MAX_NUM_OF_SOLDIERS_TO_REACH)
                            mps[the_chosen_map].tiles[i].soldiers = MAX_NUM_OF_SOLDIERS_TO_REACH;
                        time_flag = 1;
                    }
                } else {
                    if(mps[the_chosen_map].tiles[i].soldiers >= MAX_NUM_OF_SOLDIERS_TO_REACH_TEAM0){
                        time_flag = 1;
                    }
                    if (mps[the_chosen_map].tiles[i].soldiers < MAX_NUM_OF_SOLDIERS_TO_REACH_TEAM0) {
                        mps[the_chosen_map].tiles[i].soldiers += time_end - time_begin;
                        if(mps[the_chosen_map].tiles[i].soldiers > MAX_NUM_OF_SOLDIERS_TO_REACH_TEAM0)
                            mps[the_chosen_map].tiles[i].soldiers = MAX_NUM_OF_SOLDIERS_TO_REACH_TEAM0;
                        time_flag = 1;
                    }
                }
            }
        }
//draw image
        if(using_potion){
            Uint32 COLOR;
            for(int x = 1; x < NUM_OF_TILES_FOR_EACH_MAP; x++)
                if(mps[the_chosen_map].tiles[x].team == who_is_using_potion)
                    COLOR = mps[the_chosen_map].tiles[x].c_color;

            filledCircleColor(sdlRenderer,20,20,19,COLOR);
            draw_image_2(sdlRenderer,power_num);
            if(power_end - power_start >= 10){
                soldiers_speed_team1 = soldiers_speed_team1_copy;
                soldiers_speed_team2 = soldiers_speed_team2_copy;
                soldiers_speed_team3 = soldiers_speed_team3_copy;
                soldiers_speed_team4 = soldiers_speed_team4_copy;
                using_potion = 0;
                power_begin = power_end;
                power_end_copy = power_end;
                k = 1;
            }
        }
        if(power_end - power_begin >= 25){
            power_begin = power_end;
            power_end_copy = power_end;
            tile0 = rand() % (NUM_OF_TILES_FOR_EACH_MAP-1) + 1;
            tile1 = rand() % (NUM_OF_TILES_FOR_EACH_MAP-1) + 1;
            while(tile1 == tile0)
                tile1 = rand() % (NUM_OF_TILES_FOR_EACH_MAP-1) + 1;

            power_num = rand() % 4 + 1;
            on_potion = 1;
        }
        if(power_end - power_end_copy <= 15 && on_potion == 1){
            draw_image(sdlRenderer,mps[the_chosen_map].tiles[tile0],mps[the_chosen_map].tiles[tile1],power_num);
            if(power_end - power_end_copy >= 15){
                power_end_copy = 0;
                power_begin = power_end;
                on_potion = 0;
            }
        }

        if (time_flag) {
            time_begin = time_end;
            time_flag = 0;
        }

        if (final_flag == 0)
            SDL_RenderPresent(sdlRenderer);
        //SDL_Delay(1000 / FPS);


        int start, end;

//bot attacks

        time_t time_end_for_bots = time(NULL);
        if (time_end_for_bots - time_begin_for_bots >= 5 && final_flag_important == 0) {
//tiles are from 1 to NUM_OF_TILES_FOR_EACH_MAP - 1
            if (NUM_OF_PLAYERS == 2) {
                if (s == -1 && e == -1) {
                    int tr = 1;
                    for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                        if (tr == 0)
                            break;

                        if (mps[the_chosen_map].tiles[i].team == 2) {
                            for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                if (mps[the_chosen_map].tiles[j].team == 1) {
                                    if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                        s = i;
                                        e = j;
                                        tr = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (i == NUM_OF_TILES_FOR_EACH_MAP - 1 && tr == 1) {
                            for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                                if (tr == 0)
                                    break;

                                if (mps[the_chosen_map].tiles[i].team == 2) {
                                    for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                        if (mps[the_chosen_map].tiles[j].team == 0) {
                                            if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                                s = i;
                                                e = j;
                                                tr = 0;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (s != -1 && e != -1) {
                    //printf("bot\n");
                    final_flag = 1;
                    int *final__flag = &final_flag;
                    map *c = &mps[the_chosen_map];
                    int* on_potion_pointer = &on_potion;
                    int* using_potion_pointer = &using_potion;
                    time_t* power_start_pointer = &power_start;
                    float* soldiers_speed_team1_pointer = &soldiers_speed_team1;
                    float* soldiers_speed_team2_pointer = &soldiers_speed_team2;
                    float* soldiers_speed_team3_pointer = &soldiers_speed_team3;
                    float* soldiers_speed_team4_pointer = &soldiers_speed_team4;

                    send_soldiers(c, s, e, sdlRenderer, x_soldiers, y_soldiers, final__flag,on_potion,tile0,tile1,on_potion_pointer,using_potion_pointer,power_start_pointer,soldiers_speed_team1_pointer,soldiers_speed_team2_pointer,soldiers_speed_team3_pointer,soldiers_speed_team4_pointer,power_num,who_is_using_potion_pointer);


                    if(on_potion)
                        if(potion_check(x_soldiers,y_soldiers,mps[the_chosen_map].tiles[tile0],mps[the_chosen_map].tiles[tile1])){
                            if(power_num == 4){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 2){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 3){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    soldiers_speed_team2 *= 2.5;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    soldiers_speed_team3 *= 2.5;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    soldiers_speed_team4 *= 2.5;
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 1){
                                if(mps[the_chosen_map].tiles[s].team == 2){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    who_is_using_potion = 4;
                                }
                            }
                            on_potion = 0;
                            using_potion = 1;
                            power_start = time(NULL);
                        }

                    if (final_flag == 0) {
                        time_begin_for_bots = time(NULL);
                        s = -1;
                        e = -1;
                    }
                }
            }
            if (NUM_OF_PLAYERS == 3) {
                if (s == -1 && e == -1) {
                    int tr = 1;
                    for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                        if (tr == 0)
                            break;

                        if (mps[the_chosen_map].tiles[i].team == 2 || mps[the_chosen_map].tiles[i].team == 3) {
                            for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                if (mps[the_chosen_map].tiles[j].team == 1) {
                                    if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                        s = i;
                                        e = j;
                                        tr = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (i == NUM_OF_TILES_FOR_EACH_MAP - 1 && tr == 1) {
                            for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                                if (tr == 0)
                                    break;

                                if (mps[the_chosen_map].tiles[i].team == 2 || mps[the_chosen_map].tiles[i].team == 3) {
                                    for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                        if (mps[the_chosen_map].tiles[j].team == 0) {
                                            if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                                s = i;
                                                e = j;
                                                tr = 0;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (s != -1 && e != -1) {
                    //printf("bot\n");
                    final_flag = 1;
                    int *final__flag = &final_flag;
                    map *c = &mps[the_chosen_map];
                    int* on_potion_pointer = &on_potion;
                    int* using_potion_pointer = &using_potion;
                    time_t* power_start_pointer = &power_start;
                    float* soldiers_speed_team1_pointer = &soldiers_speed_team1;
                    float* soldiers_speed_team2_pointer = &soldiers_speed_team2;
                    float* soldiers_speed_team3_pointer = &soldiers_speed_team3;
                    float* soldiers_speed_team4_pointer = &soldiers_speed_team4;

                    send_soldiers(c, s, e, sdlRenderer, x_soldiers, y_soldiers, final__flag,on_potion,tile0,tile1,on_potion_pointer,using_potion_pointer,power_start_pointer,soldiers_speed_team1_pointer,soldiers_speed_team2_pointer,soldiers_speed_team3_pointer,soldiers_speed_team4_pointer,power_num,who_is_using_potion_pointer);

                    if(on_potion)
                        if(potion_check(x_soldiers,y_soldiers,mps[the_chosen_map].tiles[tile0],mps[the_chosen_map].tiles[tile1])){
                            if(power_num == 4) {
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 2){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 3){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    soldiers_speed_team2 *= 2.5;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    soldiers_speed_team3 *= 2.5;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    soldiers_speed_team4 *= 2.5;
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 1){
                                if(mps[the_chosen_map].tiles[s].team == 2){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    who_is_using_potion = 4;
                                }
                            }
                            on_potion = 0;
                            using_potion = 1;
                            power_start = time(NULL);
                        }

                    if (final_flag == 0) {
                        time_begin_for_bots = time(NULL);
                        s = -1;
                        e = -1;
                    }
                }
            }
            if (NUM_OF_PLAYERS == 4) {
                if (s == -1 && e == -1) {
                    int tr = 1;
                    for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                        if (tr == 0)
                            break;

                        if (mps[the_chosen_map].tiles[i].team == 2 || mps[the_chosen_map].tiles[i].team == 3 || mps[the_chosen_map].tiles[i].team == 4) {
                            for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                if (mps[the_chosen_map].tiles[j].team == 1) {
                                    if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                        s = i;
                                        e = j;
                                        tr = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (i == NUM_OF_TILES_FOR_EACH_MAP - 1 && tr == 1) {
                            for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {

                                if (tr == 0)
                                    break;

                                if (mps[the_chosen_map].tiles[i].team == 2 || mps[the_chosen_map].tiles[i].team == 3 || mps[the_chosen_map].tiles[i].team == 4) {
                                    for (int j = 1; j < NUM_OF_TILES_FOR_EACH_MAP; j++) {
                                        if (mps[the_chosen_map].tiles[j].team == 0) {
                                            if (mps[the_chosen_map].tiles[j].soldiers < mps[the_chosen_map].tiles[i].soldiers) {
                                                s = i;
                                                e = j;
                                                tr = 0;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (s != -1 && e != -1) {
                    //printf("bot\n");
                    final_flag = 1;
                    int *final__flag = &final_flag;
                    map *c = &mps[the_chosen_map];
                    int* on_potion_pointer = &on_potion;
                    int* using_potion_pointer = &using_potion;
                    time_t* power_start_pointer = &power_start;
                    float* soldiers_speed_team1_pointer = &soldiers_speed_team1;
                    float* soldiers_speed_team2_pointer = &soldiers_speed_team2;
                    float* soldiers_speed_team3_pointer = &soldiers_speed_team3;
                    float* soldiers_speed_team4_pointer = &soldiers_speed_team4;

                    send_soldiers(c, s, e, sdlRenderer, x_soldiers, y_soldiers, final__flag,on_potion,tile0,tile1,on_potion_pointer,using_potion_pointer,power_start_pointer,soldiers_speed_team1_pointer,soldiers_speed_team2_pointer,soldiers_speed_team3_pointer,soldiers_speed_team4_pointer,power_num,who_is_using_potion_pointer);
                    if(on_potion)
                        if(potion_check(x_soldiers,y_soldiers,mps[the_chosen_map].tiles[tile0],mps[the_chosen_map].tiles[tile1])){
                            if(power_num == 4){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 2){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 3){
                                if(mps[the_chosen_map].tiles[s].team == 2) {
                                    soldiers_speed_team2 *= 2.5;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3) {
                                    soldiers_speed_team3 *= 2.5;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4) {
                                    soldiers_speed_team4 *= 2.5;
                                    who_is_using_potion = 4;
                                }
                            }
                            if(power_num == 1){
                                if(mps[the_chosen_map].tiles[s].team == 2){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 2;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 3){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team4 *= 0.3;
                                    who_is_using_potion = 3;
                                }
                                if(mps[the_chosen_map].tiles[s].team == 4){
                                    soldiers_speed_team1 *= 0.3;
                                    soldiers_speed_team2 *= 0.3;
                                    soldiers_speed_team3 *= 0.3;
                                    who_is_using_potion = 4;
                                }
                            }
                            on_potion = 0;
                            using_potion = 1;
                            power_start = time(NULL);
                        }

                    if (final_flag == 0) {
                        time_begin_for_bots = time(NULL);
                        s = -1;
                        e = -1;
                    }
                }
            }
        }
//--------------------------//
        if(s == -1 && e == -1 && final_flag == 0 && final_flag_important == 0) {
            SDL_Event event;
            if (click(event) == 1) {
                start = is_valid_start(mps[the_chosen_map]);
                end = is_valid_end(mps[the_chosen_map], start);
                end_backup = end;

                if (start != -1 && end != -1 && start != end) {
//                printf("its valid\n");
//                printf("x0 =%d  y0 =%d\n",x0_click,y0_click);
//                printf("x1 =%d  y1 =%d\n",x1_click,y1_click);

                    final_flag = 1;
                    final_flag_important = 1;
                }
            }
        }
// sending soldiers from start to end tile//
        if (final_flag == 1 && final_flag_important == 1 && s == -1 && e == -1) {
            //printf("tooye click\n");
            int *final__flag = &final_flag;
            map *c = &mps[the_chosen_map];
            int* on_potion_pointer = &on_potion;
            int* using_potion_pointer = &using_potion;
            time_t* power_start_pointer = &power_start;
            float* soldiers_speed_team1_pointer = &soldiers_speed_team1;
            float* soldiers_speed_team2_pointer = &soldiers_speed_team2;
            float* soldiers_speed_team3_pointer = &soldiers_speed_team3;
            float* soldiers_speed_team4_pointer = &soldiers_speed_team4;

            send_soldiers(c, start, end, sdlRenderer, x_soldiers, y_soldiers, final__flag,on_potion,tile0,tile1,on_potion_pointer,using_potion_pointer,power_start_pointer,soldiers_speed_team1_pointer,soldiers_speed_team2_pointer,soldiers_speed_team3_pointer,soldiers_speed_team4_pointer,power_num,who_is_using_potion_pointer);

            if(on_potion)
                if(potion_check(x_soldiers,y_soldiers,mps[the_chosen_map].tiles[tile0],mps[the_chosen_map].tiles[tile1])){
                    if(power_num == 4){
                        if(mps[the_chosen_map].tiles[start].team == 1) {
                            who_is_using_potion = 1;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 2) {
                            who_is_using_potion = 2;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 3) {
                            who_is_using_potion = 3;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 4) {
                            who_is_using_potion = 4;
                        }
                    }
                    if(power_num == 2){
                        if(mps[the_chosen_map].tiles[start].team == 1) {
                            who_is_using_potion = 1;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 2) {
                            who_is_using_potion = 2;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 3) {
                            who_is_using_potion = 3;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 4) {
                            who_is_using_potion = 4;
                        }
                    }
                    if(power_num == 3){
                        if(mps[the_chosen_map].tiles[start].team == 1) {
                            soldiers_speed_team1 *= 2.5;
                            who_is_using_potion = 1;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 2) {
                            soldiers_speed_team2 *= 2.5;
                            who_is_using_potion = 2;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 3) {
                            soldiers_speed_team3 *= 2.5;
                            who_is_using_potion = 3;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 4) {
                            soldiers_speed_team4 *= 2.5;
                            who_is_using_potion = 4;
                        }
                    }
                    if(power_num == 1){
                        if(mps[the_chosen_map].tiles[start].team == 1){
                            soldiers_speed_team2 *= 0.3;
                            soldiers_speed_team3 *= 0.3;
                            soldiers_speed_team4 *= 0.3;
                            who_is_using_potion = 1;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 2){
                            soldiers_speed_team1 *= 0.3;
                            soldiers_speed_team3 *= 0.3;
                            soldiers_speed_team4 *= 0.3;
                            who_is_using_potion = 2;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 3){
                            soldiers_speed_team1 *= 0.3;
                            soldiers_speed_team2 *= 0.3;
                            soldiers_speed_team4 *= 0.3;
                            who_is_using_potion = 3;
                        }
                        if(mps[the_chosen_map].tiles[start].team == 4){
                            soldiers_speed_team1 *= 0.3;
                            soldiers_speed_team2 *= 0.3;
                            soldiers_speed_team3 *= 0.3;
                            who_is_using_potion = 4;
                        }
                    }
                    on_potion = 0;
                    using_potion = 1;
                    power_start = time(NULL);
                }

            if(final_flag == 0)
                final_flag_important = 0;
        }
        //printf("final_flag=%d  imp=%d\n",final_flag,final_flag_important);
//----------------------------------------//

//        winner = who_is_winner(mps);
//        if(winner != -1)
//            break;

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }

    }
    //printf("\nwinner is = %d",winner);

    if(winner == 1){
//we won
        FILE *fptr1 = fopen(name,"r");
        if(!fptr1){
            FILE *fptr2 = fopen(name,"w");
            fputc('2',fptr2);
            fputc('0',fptr2);
        }
        else {
            char buff[10];
            char c = fgetc(fptr1);
            int buff_counter = 0;
            while (c != EOF){
                buff[buff_counter] = c;
                buff[buff_counter + 1] = '\0';
                c = fgetc(fptr1);
                buff_counter++;
            }
            fptr1 = fopen(name,"w");
            int n = atoi(buff);
            n += 20;
            char text[10];
            sprintf(text, "%d", n);
            text[strlen(text)] = '\0';
            int i = 0;
            while(text[i] != '\0'){
                fputc((int)text[i],fptr1);
                i++;
            }
        }
    }
    if(winner != 1 && winner != -1){
//bots won
        FILE *fptr1 = fopen(name,"r");
        if(!fptr1){
            FILE *fptr2 = fopen(name,"w");
            fputc('0',fptr2);
        }
        else {
            char buff[10];
            char c = fgetc(fptr1);
            int buff_counter = 0;
            while (c != EOF) {
                buff[buff_counter] = c;
                buff[buff_counter + 1] = '\0';
                c = fgetc(fptr1);
                buff_counter++;
            }
            fptr1 = fopen(name,"w");
            int n = atoi(buff);
            n -= 20;
            if (n <= 0)
                fputc('0', fptr1);
            else {
                char text[10];
                sprintf(text, "%d", n);
                text[strlen(text)] = '\0';
                int i = 0;
                while (text[i] != '\0') {
                    fputc((int) text[i], fptr1);
                    i++;
                }
            }
        }

    }

    SDL_DestroyWindow(sdlWindow);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}