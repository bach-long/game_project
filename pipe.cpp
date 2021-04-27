#pragma once
#include "CMNFUNCTION.h"
#include "Main_object.cpp"
class Pipe{
   protected:
    int a,b;
    SDL_Rect above;
    SDL_Rect below;
    int blank;//khoang trong 2 cot
    double speed;//toc do
    SDL_Texture* Below_column=NULL;
    SDL_Texture* Above_column=NULL;
    bool check_height;
    bool skid;
    bool point;
    double angle;
    SDL_RendererFlip flip;
    Mix_Chunk* point_check;
    Mix_Chunk* die;
    Mix_Chunk* hit;

   public:
    Pipe(){
    check_height=false;
    skid=true;
    point=false;
    below.y=rand()%(550-300+1)+300;
    below.w=90;
    below.h=800;

    blank=rand()%(280-155+1)+155;

    above.y=below.y-800-blank;
    above.w=90;
    above.h=800;

    a=0;
    b=0;
    angle=0;
    flip=SDL_FLIP_NONE;
    Below_column=NULL;
    Above_column=NULL;
    Mix_Chunk* point_check=NULL;
    Mix_Chunk* die=NULL;
    Mix_Chunk* hit=NULL;
    }
    ~Pipe(){
      SDL_DestroyTexture(Below_column);
      SDL_DestroyTexture(Above_column);
      Below_column=NULL;
      Above_column=NULL;
      free_audio();
      Mix_FreeChunk(point_check);
      Mix_FreeChunk(hit);
      Mix_FreeChunk(die);
      Mix_Chunk* point_check=NULL;
      Mix_Chunk* die=NULL;
      Mix_Chunk* hit=NULL;
    };

   void free_audio(){
      point_check=NULL;
      hit=NULL;
      die=NULL;
   }
   void set_point_check(Mix_Chunk* sample){
       point_check=sample;
   }
   void set_hit(Mix_Chunk* sample){
       hit=sample;
   }
   void set_die(Mix_Chunk* sample){
       die=sample;
   }
   void set_speed(double speed){
       this->speed=speed;
   }
   void set_angle(double angle){
       this->angle=angle;
   }
   void set_flip(SDL_RendererFlip flip){
       this->flip=flip;
   }
   void set_blank(double blank){
       this->blank=blank;
   }
   void set_above_x(double x){
       this->above.x=x;
   }
   void set_below_x(double x){
       this->below.x=x;
   }
   void set_below_y(double y){
       this->below.y=y;
   }
   void set_above_y(double y){
       this->above.y=y;
   }
   double get_blank(){
       return blank;
   }
   double get_above_y(){
       return above.y;
   }
   double get_below_y(){
       return below.y;
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
            this->below.y=rand()%(550-300+1)+300;
            this->blank=rand()%(280-155+1)+155;
            this->above.y=this->below.y-this->blank-800;
            this->point=false;
            point_check = Mix_LoadWAV("point.wav");
            die=Mix_LoadWAV("Oof -10%.wav");
            hit=Mix_LoadWAV("hit.wav");
	}
	    else
            return;
   }



	void movement(){
	    below.x+=speed;
	    above.x+=speed;
	}



	void fluctuate(){
	    if(Point<=35){
            a=3;
            b=-3;
	    }
	    else if(Point>35&&Point<=45){
            a=3;
            b=speed-1;
	    }
        if(below.y<=280)
            check_height=true;
        else if(below.y>=580)
            check_height=false;
        if(check_height){
            below.y+=a;
            above.y+=a;}
        else{
            below.y+=b;
            above.y+=b;}
	}

    void collid(){
       if(below.y<=above.y+800+130)
       skid=true;
       else if(below.y>above.y+800+400){
        skid=false;
       }
       if(skid){
        below.y+=4;
        above.y-=4;
       }
       else{
        below.y+=speed+1;
        above.y-=speed+1;
       }
    }


	void render_above(SDL_Renderer* des, SDL_Rect* zone=NULL){
    SDL_Rect render_zone={above.x,above.y,above.w,above.h};
    //SDL_Point center={90/2,-1*above.y};
    SDL_RenderCopyEx(des,Above_column,zone,&render_zone,angle,NULL,flip);
   }



   void render_below(SDL_Renderer* des, SDL_Rect* zone=NULL){
    SDL_Rect render_zone={below.x,below.y,below.w,below.h};
    //SDL_Point center={90/2,800-(736-below.y)};
    SDL_RenderCopyEx(des,Below_column,zone,&render_zone,angle*-1,NULL,flip);
   }



    bool lose(double& a,double& b){
        if(b+40>736){
            Mix_PlayChannel(-1,die,0);
            return true;
        }
        else if(a<=below.x*cos(angle)&&a+58>=below.x*cos(angle)&&(b<(above.y+800)*cos(angle)||b+40>below.y/cos(angle))){
            Mix_PlayChannel(-1,hit,0);
            return true;
        }
        else if(a<=(this->below.x+90)*cos(angle)&&a+58>=(below.x+90)*cos(angle)&&(b<(above.y+800)*cos(angle)||b+40>below.y/cos(angle))){
            Mix_PlayChannel(-1,hit,0);
            return true;
        }
        else if(a>below.x*cos(angle)&&a+58<(below.x+90)*cos(angle)&&(b<(above.y+800)*cos(angle)||b+40>below.y/cos(angle))){
            Mix_PlayChannel(-1,hit,0);
            return true;
        }
        else
            return false;
    }



    void check_point(double& a,int& Point){
        if(a>this->below.x+90&&a<this->below.x+90-speed+1){
            this->point=true;
            Mix_PlayChannel(-1,point_check,0);


        }
        if(this->point==true){
            Point++;
            this->point=false;
        }

    }




};
