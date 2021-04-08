#pragma once
#include"CMNFUNCTION.h"
class founder{
   protected:
    SDL_Texture* prime_object;
    SDL_Rect rect;

   public:
   founder(){
    prime_object=NULL;
    rect.x=0;
    rect.y=0;
    rect.w=0;
    rect.h=0;};
   ~founder(){
       SDL_DestroyTexture(prime_object);
       prime_object=NULL;
       rect.x=0;
       rect.y=0;
       rect.w=0;
       rect.h=0;
   };
   void setRect(double x,double y){rect.x=x;rect.y=y;};
   SDL_Rect getRect(){return rect;};
   SDL_Texture* getTexture(){return prime_object;};

   bool LoadImg(string path,SDL_Renderer* screen){
    SDL_Texture* new_texture=NULL;
    SDL_Surface* loadedSur=IMG_Load(path.c_str());
    if(loadedSur==NULL){
        cout<<"can't upload img "<<SDL_GetError();
    }
    else{
        SDL_SetColorKey(loadedSur,SDL_TRUE,SDL_MapRGB(loadedSur->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture=SDL_CreateTextureFromSurface(screen,loadedSur);
        if(new_texture!=NULL){
            rect.w=loadedSur->w;
            rect.h=loadedSur->h;

        }
        SDL_FreeSurface(loadedSur);
       }
    prime_object=new_texture;

    return prime_object!=NULL;
    };
   void render(SDL_Renderer* des, SDL_Rect* zone=NULL){
    SDL_Rect render_zone={rect.x,rect.y,rect.w,rect.h};
    SDL_RenderCopy(des,prime_object,zone,&render_zone);
   };
};
