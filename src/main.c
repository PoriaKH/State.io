#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "math.h"
#define MIN_X 50
#define MIN_Y 70


#ifdef main
#undef main
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
const int NUM_OF_MAPS = 3;
const int min_of_map_tiles_counter = 5;
const int min_width_of_tile = 70;
const int min_height_of_tile = 70;
const int cubes_r = 20;

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
    }
}
void second_check(tile* c)
{
    if(c->y2 > SCREEN_WIDTH)
        c->y2 = SCREEN_WIDTH;

    if(c->x2 > SCREEN_HEIGHT)
        c->x2 = SCREEN_HEIGHT;

}
int main()
{
    // <----> Height

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
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
                if(tls[counter].height >=min_height_of_tile && tls[counter].width >= min_width_of_tile)
                {
                    tile* c = &tls[counter];
                    second_check(c);
                    mps[k].tiles[map_tiles_counter]= tls[counter];
                    map_tiles_counter++;
                }
                counter++;
            }
            base_height = 0;
            base_width = y[i];

        }
        if(map_tiles_counter < min_of_map_tiles_counter)
        {
            //printf("map_tiles_counter=%d\n",map_tiles_counter);
            map* c = &mps[k];
            clean(c,map_tiles_counter);
            k--;
            map_tiles_counter = 0;
            continue;
        }
        //printf("k=%d  map_count=%d\n",k,map_tiles_counter);
    }



    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

//// error handling
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {

        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        Uint32 color1 = 0xff000000;
        Uint32 color2 = 0xf1ff0000;
        Uint32 color3 = 0xffffff02;
        Uint32 color4 = 0xfff0f000;

        for (int i = 0; i < 5; i++)
        {
                boxColor(sdlRenderer, mps[0].tiles[i].x1, mps[0].tiles[i].y1, mps[0].tiles[i].x2, mps[0].tiles[i].y2, color4);
                //printf("x1=%d  x2=%d  y1=%d  y2=%d\n",mps[0].tiles[i].x1,mps[0].tiles[i].x2,mps[0].tiles[i].y1,mps[0].tiles[i].y2);

                Uint32 color21 = 0xff0000ff;
                Sint16 x = 480, y = 240;
                filledCircleColor(sdlRenderer,avg(mps[0].tiles[i].x1,mps[0].tiles[i].x2),avg(mps[0].tiles[i].y1,mps[0].tiles[i].y2), cubes_r, color21);
        }

        SDL_RenderPresent(sdlRenderer);


        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }


    }
    SDL_Delay(20000 / FPS);
    SDL_DestroyWindow(sdlWindow);

    SDL_Quit();
    return 0;
}