#ifndef CMNFUNCTION_H_INCLUDED
#define CMNFUNCTION_H_INCLUDED
#include <bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

using namespace std;
static SDL_Window* gWindow=NULL;
static SDL_Renderer*gScreen=NULL;
static SDL_Event e;

//Screen
const int SCREEN_WIDTH=1308;
const int SCREEN_HEIGH=736;
const int SCREEN_BPP=32;
const int FPS=50;

const int COLOR_KEY_R=0;
const int COLOR_KEY_G=0xFF;
const int COLOR_KEY_B=0xFF;


#endif // CMNFUNCTION_H_INCLUDED
