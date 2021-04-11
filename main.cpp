#include"CMNFUNCTION.h"
#include"Main_object.cpp"
#include"Character.cpp"
#include"Pipe.cpp"
#include"Text_object.cpp"

founder Background;//khai bao man hinh chinh
Character Bird;//khai bao nhan vat
Pipe col[5];//khai bao cac Pipe
founder Start;//man hinh bat dau
int Point=0;
TTF_Font* font_time=NULL;
Mix_Chunk* point_check=NULL;
Mix_Chunk* die=NULL;
Mix_Chunk* hit=NULL;
Mix_Chunk* swoosh=NULL;
Mix_Chunk* swing=NULL;

using namespace std;

bool Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        return false;
    }
    else{
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
        gWindow=SDL_CreateWindow("game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGH,SDL_WINDOW_SHOWN);
        gScreen=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
        if(gScreen==NULL||gWindow==NULL)
            return false;
        else{
        SDL_SetRenderDrawColor(gScreen,255,255,255,255);
        int IMG=IMG_INIT_PNG;
        if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
            return false;
        }
        return true;
    }
  }

  bool LoadBackground(){
       bool check=Background.LoadImg("background.png",gScreen);
       if(check==false)
        return false;
       else{
        return true;
       }
  }

  int main(int argc,char* argv[]){
   if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
   }
   if(!Init()||!LoadBackground()){
    cout<<"Can't initialize"<<endl;
   }
   else{

       bool quit=false,start_menu=false;
       while(!start_menu){
        Background.render(gScreen,NULL);
        Start.LoadImg("start.png",gScreen);
        Start.setRect(254,267.5);
        Start.render(gScreen,NULL);
        SDL_RenderPresent(gScreen);
        die=Mix_LoadWAV("die.wav");
        hit=Mix_LoadWAV("hit.wav");
        point_check = Mix_LoadWAV("point.wav");
        swoosh=Mix_LoadWAV("swoosh.wav");
        swing=Mix_LoadWAV("wing.wav");
        while(SDL_PollEvent(&e)!=0){
            if(e.type==SDL_MOUSEBUTTONDOWN){
            start_menu=true;
            }
            else if(e.key.keysym.sym==SDLK_ESCAPE||e.type==SDL_QUIT){
            SDL_Quit();
            }
            }
       }
       for(int i=0;i<5;i++){
        col[i].set_above_x(1308+i*(304.5));
        col[i].set_below_x(1308+i*(304.5));
        col[i].LoadBelow("pipelong.png",gScreen);
        col[i].LoadAbove("pipelong_reversed.png",gScreen);
        col[i].set_speed(-7);
        col[i].set_point_check(point_check);
        col[i].set_hit(hit);
        col[i].set_die(die);
        //col[i].set_angle(60);
       }
        Bird.set_swoosh(swoosh);
        Bird.set_swing(swing);
        font_time=TTF_OpenFont("dlxfont.ttf",15);
        Text_object time_record;
        //time_record.SetColor(255,0,0);
     while(!quit){
       while(SDL_PollEvent(&e)!=0){
          if(e.type==SDL_QUIT)
            quit=true;
       }
       SDL_RenderClear(gScreen);
       Bird.LoadCharacter("bird.png",gScreen);
       Background.render(gScreen,NULL);
       Bird.render_character(gScreen,NULL,e);


       string time_var="Time: ";
       int time_now= SDL_GetTicks()/1000;
       int h,m,s;
       s=time_now%60;
       m=(time_now/60)%60;
       h=(time_now/60)/60;
       h<10 ? time_var+="0"+to_string(h)=":" : time_var+=to_string(h)+":";
       m<10 ? time_var+="0"+to_string(m)=":" : time_var+=to_string(m)+":";
       s<10 ? time_var+="0"+to_string(s) : time_var+=to_string(s);
       time_record.set_text_var("Time");
       time_record.LoadFromText(font_time, gScreen);
       time_record.RenderText(gScreen, 15, 15, NULL, 0.0, NULL, SDL_FLIP_NONE);


       for(int i=0;i<5;i++){
        col[i].render_above(gScreen);
        col[i].render_below(gScreen);
        col[i].movement();
        if(Point>20){
        col[i].set_speed(-8);
        }
        if(Point>30){
        if(i%2!=0)
        col[i].fluctuate();
        }
        if(Point>50){
        col[i].set_speed(-9);
        if(i%2==0)
        col[i].fluctuate();
        }
        if(Point>70){
            col[i].fluctuate();
        }
        double a=Bird.get_x();
        double b=Bird.get_y();
        if(col[i].lose(a,b)){
           for(int i=0;i<5;i++){
               col[i].set_speed(0);
               col[i].free_audio();
           }
        }
        col[i].check_point(a,Point);
        col[i].reset();
       }

       SDL_RenderPresent(gScreen);
       SDL_Delay((int)1000/FPS);
     }
   }


  return 0;
}
