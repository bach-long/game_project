#pragma once
#include "CMNFUNCTION.h"
#include "Main_object.cpp"
class Pipe{
   protected:
    SDL_Rect above;
    SDL_Rect below;
    int blank;//khoang trong 2 cot
    double speed;//toc do
    SDL_Texture* Below_column;
    SDL_Texture* Above_column;
    bool check_height;
    bool point;
    double angle;
    SDL_RendererFlip flip;



   public:
    Pipe(){
    check_height=false;
    point=false;
    below.y=rand()%(600-400+1)+400;
    below.w=90;
    below.h=800;

    blank=rand()%(300-155+1)+155;

    above.y=below.y-800-blank;
    above.w=90;
    above.h=800;
    angle=0;
    flip=SDL_FLIP_NONE;
    Below_column=NULL;
    Above_column=NULL;
    }
    ~Pipe(){
      SDL_DestroyTexture(Below_column);
      SDL_DestroyTexture(Above_column);
    };



   void set_speed(double speed){
       this->speed=speed;
   }
   void set_angle(double angle){
       this->angle=angle;
   }
   void set_flip(SDL_RendererFlip flip){
       this->flip=flip;
   }
   void set_above_x(double x){
       this->above.x=x;
   }
   void set_below_x(double x){
       this->below.x=x;
   }
   SDL_Rect get_above(){
       return above;
   };
   SDL_Rect get_below(){
       return below;
   };




   bool LoadAbove(string path,SDL_Renderer* screen){
    SDL_Texture* new_texture=NULL;
    SDL_Surface* loadedSur=IMG_Load(path.c_str());
    if(loadedSur==NULL){
        cout<<"can't upload img "<<SDL_GetError();
    }
    else{
        SDL_SetColorKey(loadedSur,SDL_TRUE,SDL_MapRGB(loadedSur->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture=SDL_CreateTextureFromSurface(screen,loadedSur);
        if(new_texture!=NULL){
            above.w=loadedSur->w;
            above.h=loadedSur->h;

        }
        SDL_FreeSurface(loadedSur);
       }
    Above_column=new_texture;

    return Above_column!=NULL;
    };



    bool LoadBelow(string path,SDL_Renderer* screen){
    SDL_Texture* new_texture=NULL;
    SDL_Surface* loadedSur=IMG_Load(path.c_str());
    if(loadedSur==NULL){
        cout<<"can't upload img "<<SDL_GetError();
    }
    else{
        SDL_SetColorKey(loadedSur,SDL_TRUE,SDL_MapRGB(loadedSur->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture=SDL_CreateTextureFromSurface(screen,loadedSur);
        if(new_texture!=NULL){
            below.w=loadedSur->w;
            below.h=loadedSur->h;

        }
        SDL_FreeSurface(loadedSur);
       }
    Below_column=new_texture;

    return Below_column!=NULL;
    };



   void reset(){
        if(below.x+90<0){
            this->below.x=1432.5;
            this->above.x=this->below.x;
            this->below.y=rand()%(600-400+1)+400;
            this->blank=rand()%(300-155+1)+155;
            this->above.y=this->below.y-this->blank-800;
            this->point=false;

	}
	    else
            return;
   }



	void movement(){
	    below.x+=speed;
	    above.x+=speed;
	}



	void fluctuate(){
        if(below.y<=300)
            check_height=true;
        if(below.y>=600)
            check_height=false;
        if(check_height){
            below.y+=3;
            above.y+=3;}
        else{
            below.y-=3;
            above.y-=3;}
	}



	void render_above(SDL_Renderer* des, SDL_Rect* zone=NULL){
    SDL_Rect render_zone={above.x,above.y,above.w,above.h};
    SDL_RenderCopyEx(des,Above_column,zone,&render_zone,angle,NULL,flip);
   }



   void render_below(SDL_Renderer* des, SDL_Rect* zone=NULL){
    SDL_Rect render_zone={below.x,below.y,below.w,below.h};
    SDL_RenderCopyEx(des,Below_column,zone,&render_zone,angle,NULL,flip);
   }



    bool lose(double& a,double& b){
        if(b+35>=736)
            return true;
        else if(a<=this->below.x&&a+48>=this->below.x&&(b<this->above.y+800||b+37>this->below.y))
            return true;
        else if(a<=this->below.x+90&&a+48>=this->below.x+90&&(b<this->above.y+800||b+37>this->below.y))
            return true;
        else
            return false;
    }



    void check_point(double& a,int& Point){
        if(a>this->below.x+90&&a<this->below.x+90+8){
            this->point=true;
        }
        if(this->point==true){
            Point++;
            cout<<Point<<endl;
            this->point=false;
        }

    }




};
