#pragma once
#include"CMNFUNCTION.h"
class Character{
protected:
    double v0;
    SDL_Texture* character;
    SDL_Rect rect;
    Mix_Chunk* swoosh;
    Mix_Chunk* swing;
    SDL_RendererFlip flip;
    double angle;
    bool press;
public:
    Character(){
        rect.x=(SCREEN_WIDTH-72)/6;
        rect.y=(SCREEN_HEIGH-50)/4;
        v0=0;
        character=NULL;
        Mix_Chunk* swoosh=NULL;
        Mix_Chunk* swing=NULL;
        flip=SDL_FLIP_NONE;
        angle=0.0;
        press=false;
    }
    ~Character(){
        SDL_DestroyTexture(character);
        audio_delete();
    }
    void audio_delete(){
        Mix_FreeChunk(swoosh);
        Mix_FreeChunk(swing);
        swoosh=NULL;
        swing=NULL;
    }
    void set_swoosh(Mix_Chunk* sample){
        swoosh=sample;
    }
    void set_swing(Mix_Chunk* sample){
        swing=sample;
    }
    void set_v0(int v){
        this->v0=v;
    }
    void set_x(int x){
    this->rect.x=x;
    }
    void set_y(int y){
    this->rect.y=y;
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

    void vertical_move(){
        if(e.type==SDL_MOUSEBUTTONDOWN){
            if(press==false){
               Mix_PlayChannel(-1,swing,0);
               v0=-11;
               rect.y+=v0+0.5*1.5;
               angle-=27;
               if(angle<=-45){
                angle+=27;
               }
               press=true;
            }
             else{
             v0+=1.25;
             rect.y+=v0+1.25*0.5;
             angle+=1.5;
             if(angle>=20){
                angle-=1.5;
             }
             }
            }

             else{
             v0+=1.25;
             rect.y+=v0+1.25*0.5;
             angle+=1.5;
             if(angle>=20){
                angle-=1.5;
             }
             press=false;
             }
    }


    void render_character(SDL_Renderer* des,SDL_Rect* zone,SDL_Event e){

    SDL_Rect render_zone={rect.x,rect.y,rect.w,rect.h};
    SDL_RenderCopyEx(des,character,zone,&render_zone,angle,NULL,flip);

   }
   void make_die(){
             v0+=1.5;
             rect.y+=v0+1.5*0.5;
             angle+=1.5;
             if(angle>=25){
                angle-=1.5;
             }
   }


};

