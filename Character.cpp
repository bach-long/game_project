#pragma once
#include"CMNFUNCTION.h"
class Character{
protected:
    double v0;
    SDL_Texture* character;
    SDL_Rect rect;
    Mix_Chunk* swoosh;
    Mix_Chunk* swing;
public:
    Character(){
        rect.x=(SCREEN_WIDTH-72)/6;
        rect.y=(SCREEN_HEIGH-50)/2;
        v0=0;
        character=NULL;
        Mix_Chunk* swoosh=NULL;
        Mix_Chunk* swing=NULL;
    }
    ~Character(){
        SDL_DestroyTexture(character);
    }
    void set_swoosh(Mix_Chunk* sample){
        swoosh=sample;
    }
    void set_swing(Mix_Chunk* sample){
        swing=sample;
    }
    int get_x(){
        return rect.x;
    }
    int get_y(){
        return rect.y;
    }
    bool LoadCharacter(string path,SDL_Renderer* screen){
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
    character=new_texture;

    return character!=NULL;
    }

    void render_character(SDL_Renderer* des,SDL_Rect* zone,SDL_Event e){
    if(e.type==SDL_MOUSEBUTTONDOWN&& e.key.repeat==0){
               Mix_PlayChannel(-1,swing,0);
               v0=-10;
               rect.y+=v0+0.5*1.5;
               //LoadCharacter("bird_up.png",gScreen);
               //cout<<"x: "<<rect.x<<" y: "<<rect.y<<endl;

            }
    else if(e.type==SDL_MOUSEBUTTONUP||e.type==SDL_MOUSEMOTION){
             //Mix_PlayChannel(-1,swoosh,0);
             v0+=1.5;
             rect.y+=v0+1.5*0.5;
             //LoadCharacter("bird_down.png",gScreen);
             //cout<<"x: "<<rect.x<<" y: "<<rect.y<<endl;
            }
    SDL_Rect render_zone={rect.x,rect.y,rect.w,rect.h};
    SDL_RenderCopy(des,character,zone,&render_zone);

   }


};

