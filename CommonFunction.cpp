#include"CommonFunction.h"



SDL_Surface*LoadImg(string path,SDL_Surface* gScreen){
    SDL_Surface* loadedImg=NULL;
    SDL_Surface* optimizedImg=NULL;
    loadedImg=IMG_Load(path.c_str());
    if(loadedImg!=NULL){
        optimizedImg=SDL_ConvertSurface(loadedImg,gScreen->format,0);
        SDL_FreeSurface(loadedImg);
        Uint32 colorkey=SDL_MapRGB(optimizedImg->format,0,0xFF,0xFF);
        SDL_SetColorKey(optimizedImg,SDL_TRUE,colorkey);
    }
    return optimizedImg;
}

void ApplySurface(SDL_Surface* src,SDL_Surface* des, double x,double y){
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(src,NULL,des,&offset);
}


