#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
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
const int soldiers_speed = 2;
const int NUM_OF_PLAYERS = 3;
const int FIRST_NUM_OF_SOLDIERS = 10;
const int FIRST_NUM_OF_SOLDIERS_TEAM_0 = 11;

int NUM_OF_SOLDIERS = 30;
int NUM_OF_TILES_FOR_EACH_MAP;

Uint32 b_color1 = 0xaa800000;             //blue
Uint32 c_color1 = 0xFFA50011;

Uint32 b_color2 = 0xff000099;             //red
Uint32 c_color2 = 0xff0000ff;

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


        c->tiles[n2].team = 1;
        c->tiles[n2].b_color = b_color1;
        c->tiles[n2].c_color = c_color1;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;

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

        c->tiles[n4].team = 2;
        c->tiles[n4].b_color = b_color2;
        c->tiles[n4].c_color = c_color2;
        c->tiles[n4].soldiers = FIRST_NUM_OF_SOLDIERS;

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

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
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

        c->tiles[n2].team = 2;
        c->tiles[n2].b_color = b_color2;
        c->tiles[n2].c_color = c_color2;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;

        c->tiles[n3].team = 3;
        c->tiles[n3].b_color = b_color3;
        c->tiles[n3].c_color = c_color3;
        c->tiles[n3].soldiers = FIRST_NUM_OF_SOLDIERS;

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

        c->tiles[n5].team = 0;
        c->tiles[n5].b_color = b_color_team_0;
        c->tiles[n5].c_color = c_color_team_0;
        c->tiles[n5].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
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

        c->tiles[n2].team = 2;
        c->tiles[n2].b_color = b_color2;
        c->tiles[n2].c_color = c_color2;
        c->tiles[n2].soldiers = FIRST_NUM_OF_SOLDIERS;

        c->tiles[n3].team = 3;
        c->tiles[n3].b_color = b_color3;
        c->tiles[n3].c_color = c_color3;
        c->tiles[n3].soldiers = FIRST_NUM_OF_SOLDIERS;

        c->tiles[n4].team = 4;
        c->tiles[n4].b_color = b_color4;
        c->tiles[n4].c_color = c_color4;
        c->tiles[n4].soldiers = FIRST_NUM_OF_SOLDIERS;

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

        c->tiles[n6].team = 0;
        c->tiles[n6].b_color = b_color_team_0;
        c->tiles[n6].c_color = c_color_team_0;
        c->tiles[n6].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;

        c->tiles[n7].team = 0;
        c->tiles[n7].b_color = b_color_team_0;
        c->tiles[n7].c_color = c_color_team_0;
        c->tiles[n7].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;

        c->tiles[n8].team = 0;
        c->tiles[n8].b_color = b_color_team_0;
        c->tiles[n8].c_color = c_color_team_0;
        c->tiles[n8].soldiers = FIRST_NUM_OF_SOLDIERS_TEAM_0;
    }
}
int main()
{
    // <----> Height

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

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
        int x_lines = 5; //ofoghi
        int y_lines = 3; //amoodi

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


    map* c = &mps[0];
    initialize_teams(c);



    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    int final_flag = 0;
    int final_flag2 = 0;
    int final_flag3 = 1;
    int arrived_flag = 0;
    int j_backup = 0;
    int end_backup = -1;
    int delta = 0;

    double x_soldiers[NUM_OF_SOLDIERS];
    double y_soldiers[NUM_OF_SOLDIERS];

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {

        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);


        Uint32 color1 = 0xff000000;
        Uint32 color2 = 0xf1ff0000;
        Uint32 color3 = 0xffffff02;
        Uint32 color4 = 0xfff0f000;


            for (int i = 1; i < NUM_OF_TILES_FOR_EACH_MAP; i++) {
                boxColor(sdlRenderer, mps[0].tiles[i].x1, mps[0].tiles[i].y1, mps[0].tiles[i].x2, mps[0].tiles[i].y2,mps[0].tiles[i].b_color);

                filledCircleColor(sdlRenderer, mps[0].tiles[i].x_o, mps[0].tiles[i].y_o, cubes_r, mps[0].tiles[i].c_color);
                char text[10];
                sprintf(text, "%d", mps[0].tiles[i].soldiers);

                if(arrived_flag == 0) {
                    if (counter(mps[0].tiles[i].soldiers) == 0 || counter(mps[0].tiles[i].soldiers) == 1)
                        stringColor(sdlRenderer, mps[0].tiles[i].x_o - 3, mps[0].tiles[i].y_o - 3, text, 0xff000000);

                    if (counter(mps[0].tiles[i].soldiers) == 2)
                        stringColor(sdlRenderer, mps[0].tiles[i].x_o - 8, mps[0].tiles[i].y_o - 3, text, 0xff000000);
                }
                else if(i != end_backup){
                    if (counter(mps[0].tiles[i].soldiers) == 0 || counter(mps[0].tiles[i].soldiers) == 1)
                        stringColor(sdlRenderer, mps[0].tiles[i].x_o - 3, mps[0].tiles[i].y_o - 3, text, 0xff000000);

                    if (counter(mps[0].tiles[i].soldiers) == 2)
                        stringColor(sdlRenderer, mps[0].tiles[i].x_o - 8, mps[0].tiles[i].y_o - 3, text, 0xff000000);
                }
            }

        if(final_flag == 0)
            SDL_RenderPresent(sdlRenderer);
        //SDL_Delay(1000 / FPS);


        int start,end;

        SDL_Event event;
        if(click(event) == 1) {
            start = is_valid_start(mps[0]);
            end = is_valid_end(mps[0]);
            end_backup = end;

            if (start != -1 && end != -1 && start != end) {
//                printf("its valid\n");
//                printf("x0 =%d  y0 =%d\n",x0_click,y0_click);
//                printf("x1 =%d  y1 =%d\n",x1_click,y1_click);

// send soldiers from start to end tile
                final_flag = 1;
            }
        }
        if(final_flag == 1){
            if(final_flag2 == 0) {
                final_flag2 = 1;

                NUM_OF_SOLDIERS = mps[0].tiles[start].soldiers / 2;

                if(mps[0].tiles[start].soldiers % 2 == 1)
                    delta = 1;

                if(delta)
                    NUM_OF_SOLDIERS = mps[0].tiles[start].soldiers / 2 + 1;

                for(int i = 0; i < NUM_OF_SOLDIERS ; i++) {
                    x_soldiers[i] = mps[0].tiles[start].x_o;
                    y_soldiers[i] = mps[0].tiles[start].y_o;
                }
            }

            double len = len_cal(mps[0].tiles[start].x_o,mps[0].tiles[end].x_o,mps[0].tiles[start].y_o,mps[0].tiles[end].y_o);
            double V_x = (double)soldiers_speed * (mps[0].tiles[end].x_o - mps[0].tiles[start].x_o) / len;
            double V_y = (double)soldiers_speed * (mps[0].tiles[end].y_o - mps[0].tiles[start].y_o) / len;

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
                        bool arrived_0 = is_arrived(x_soldiers[j],y_soldiers[j],mps[0].tiles[end]);

                        if(arrived_0) {
                            j_backup = j + 1;
                            arrived_flag = 1;
// friend -> 1 , enemy -> -1
                            int friend_or_enemy = color_check(mps[0].tiles[start],mps[0].tiles[end]);

                            if(friend_or_enemy == 1)
                                mps[0].tiles[end].soldiers += 2;

                            else if(friend_or_enemy == -1) {
                                if(mps[0].tiles[end].soldiers - 2 >= 0)
                                    mps[0].tiles[end].soldiers -= 2;

                                else{
                                    mps[0].tiles[end].c_color = mps[0].tiles[start].c_color;
                                    mps[0].tiles[end].b_color = mps[0].tiles[start].b_color;
                                    mps[0].tiles[end].team = mps[0].tiles[start].team;
                                }
                            }


                            char text[10];
                            sprintf(text, "%d", mps[0].tiles[end].soldiers);
                            if (counter(mps[0].tiles[end].soldiers) == 0 || counter(mps[0].tiles[end].soldiers) == 1)
                                stringColor(sdlRenderer, mps[0].tiles[end].x_o - 3, mps[0].tiles[end].y_o - 3, text, 0xff000000);

                            if (counter(mps[0].tiles[end].soldiers) == 2)
                                stringColor(sdlRenderer, mps[0].tiles[end].x_o - 8, mps[0].tiles[end].y_o - 3, text, 0xff000000);
                        }

                        if(!arrived_0){
                            filledCircleColor(sdlRenderer, x_soldiers[j], y_soldiers[j], soldiers_r, mps[0].tiles[start].c_color);
                        }
                    }
                    mps[0].tiles[start].soldiers = 0;
                    SDL_RenderPresent(sdlRenderer);

                    if (i == NUM_OF_SOLDIERS - 1)
                        final_flag3 = 0;
                }
            }

            if(final_flag3 == 0) {
                for (int j = j_backup; j < NUM_OF_SOLDIERS; j++) {
                    x_soldiers[j] += V_x;
                    y_soldiers[j] += V_y;

                    bool arrived = is_arrived(x_soldiers[j],y_soldiers[j],mps[0].tiles[end]);
                    if(arrived) {
                        j_backup = j + 1;
                        arrived_flag = 1;
                        int friend_or_enemy = color_check(mps[0].tiles[start], mps[0].tiles[end]);
                        int damage = 2;

                        if(j == NUM_OF_SOLDIERS - 1){
                            if(delta == 1){
                                damage = 1;
                            }
                        }

                        if (friend_or_enemy == 1)
                            mps[0].tiles[end].soldiers += damage;

                        else if (friend_or_enemy == -1) {
                            if (mps[0].tiles[end].soldiers - damage >= 0)
                                mps[0].tiles[end].soldiers -= damage;

                            else {
                                mps[0].tiles[end].c_color = mps[0].tiles[start].c_color;
                                mps[0].tiles[end].b_color = mps[0].tiles[start].b_color;
                                mps[0].tiles[end].team = mps[0].tiles[start].team;

                                mps[0].tiles[end].soldiers = damage - mps[0].tiles[end].soldiers - 1;
                            }
                        }
                        printf("soldiers=%d\n",mps[0].tiles[end].soldiers);

                        char text[10];
                        sprintf(text, "%d", mps[0].tiles[end].soldiers);
                        if (counter(mps[0].tiles[end].soldiers) == 0 || counter(mps[0].tiles[end].soldiers) == 1)
                            stringColor(sdlRenderer, mps[0].tiles[end].x_o - 3, mps[0].tiles[end].y_o - 3, text, 0xff000000);

                        if (counter(mps[0].tiles[end].soldiers) == 2)
                            stringColor(sdlRenderer, mps[0].tiles[end].x_o - 8, mps[0].tiles[end].y_o - 3, text, 0xff000000);
                    }

                    if(!arrived)
                        filledCircleColor(sdlRenderer, x_soldiers[j], y_soldiers[j], soldiers_r, mps[0].tiles[start].c_color);

                    else if(j == NUM_OF_SOLDIERS - 1){
                        final_flag = 0;
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


        //SDL_RenderPresent(sdlRenderer);
        //SDL_Delay(1000 / FPS);


        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
        //SDL_RenderPresent(sdlRenderer);
    }

    SDL_DestroyWindow(sdlWindow);

    SDL_Quit();
    return 0;
}