#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED
#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

SDL_Surface* LoadImg(string path,SDL_Surface* gScreen);
void ApplySurface(SDL_Surface* src,SDL_Surface* des, double x,double y);
void close();

#endif // COMMONFUNCTION_H_INCLUDED
