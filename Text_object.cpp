#pragma once
#include"CMNFUNCTION.h"
using namespace std;
class Text_object{
private:
    string text_var;
    SDL_Color text_col;
    SDL_Texture* texture;
    int width;
    int height;
public:
    Text_object(){
        text_col.r=0;
        text_col.g=0;
        text_col.b=0;
        texture=NULL;
    }
    ~Text_object(){
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
    void set_text_var(string str){
        this->text_var=str;
    }
    int getwidth()const{
        return width;
    }
    int getheight(){
        return height;
    }


    bool LoadFromText(TTF_Font* font, SDL_Renderer* screen){
        SDL_Surface* text_sur= TTF_RenderText_Solid(font,text_var.c_str(),text_col);
            if(text_sur!=NULL){
                texture=SDL_CreateTextureFromSurface(screen,text_sur);
                width= text_sur->w;
                height= text_sur->h;
            }
    return texture!=NULL;
    }

    void SetColor(Uint8 red,Uint8 green, Uint8 blue){
        text_col.r=red;
        text_col.g=green;
        text_col.b=blue;
    }
    void RenderText(SDL_Renderer* screen,int x, int y, SDL_Rect* crop, double angle, SDL_Point* center, SDL_RendererFlip flip){
              SDL_Rect render_zone={x,y,width,height};
              if(crop!=NULL){
                render_zone.w=crop->w;
                render_zone.h=crop->h;
              }

              SDL_RenderCopyEx(screen,texture,crop,&render_zone,angle,center,flip);


    }


};
