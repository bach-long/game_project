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
        if(!IMG_Init(IMG))
            return false;
        }
        return true;
        if(TTF_Init()!=-1)
        font_time=TTF_OpenFont("dlxfont.ttf",15);
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
       }
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
        col[i].reset();
        col[i].movement();
        double a=Bird.get_x();
        double b=Bird.get_y();
        if(col[i].lose(a,b))
            SDL_Quit();

       }
       SDL_RenderPresent(gScreen);
       SDL_Delay((int)1000/FPS);
     }
   }


  return 0;
}
