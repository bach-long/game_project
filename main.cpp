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
TTF_Font* font=NULL;
TTF_Font* menu_end=NULL;
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
        if( !( IMG_Init(IMG) & IMG ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    return false;
                }
        if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
            return false;
        if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
        else{
            font=TTF_OpenFont("dlxfont.ttf",30);
            menu_end=TTF_OpenFont("dlxfont.ttf",60);
            }

        return true;
        }
    }
  }
  void Close(){
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gScreen);
    Mix_FreeChunk(point_check);
    Mix_FreeChunk(swoosh);
    Mix_FreeChunk(swing);
    Mix_FreeChunk(hit);
    Mix_FreeChunk(die);
    TTF_CloseFont(font);
    TTF_CloseFont(menu_end);
    gWindow=NULL;
    gScreen=NULL;
    swoosh=NULL;
    swing=NULL;
    hit=NULL;
    die=NULL;
    font=NULL;
    menu_end=NULL;
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    IMG_Quit();
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
    srand(time(NULL));
   if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
   }
   if(!Init()||!LoadBackground()){
    cout<<"Can't initialize"<<endl;
   }
   else{
       bool quit=false,start_menu=false;
       Text_object instruct;
       Text_object exit;
       Text_object time_record;
       Text_object present_Point;
       Text_object suggest;
       Text_object game_over;

       instruct.SetColor(255,255,255);
       exit.SetColor(255,255,255);
       time_record.SetColor(255,0,0);
       present_Point.SetColor(255,0,0);
       suggest.SetColor(255,0,0);
       game_over.SetColor(255,0,0);

       die=Mix_LoadWAV("Oof -10%.wav");
       hit=Mix_LoadWAV("hit.wav");
       point_check = Mix_LoadWAV("point.wav");
       swoosh=Mix_LoadWAV("swoosh.wav");
       swing=Mix_LoadWAV("wing.wav");

       Bird.set_swoosh(swoosh);
       Bird.set_swing(swing);

       instruct.set_text_var("Click anywhere to get started");
       exit.set_text_var("Esc to exit");
       instruct.LoadFromText(font,gScreen);
       exit.LoadFromText(font,gScreen);

       while(!start_menu){
        while(SDL_PollEvent(&e)!=0){
            if(e.type==SDL_MOUSEBUTTONDOWN){
            start_menu=true;
            }
            else if(e.key.keysym.sym==SDLK_ESCAPE||e.type==SDL_QUIT){
            break;
            }
        }

        Background.render(gScreen,NULL);
        Start.LoadImg("start.png",gScreen);
        Start.setRect(254,150);
        Start.render(gScreen,NULL);
        instruct.RenderText(gScreen,218,400,NULL,0.0,NULL,SDL_FLIP_NONE);
        exit.RenderText(gScreen,450,460,NULL,0.0,NULL,SDL_FLIP_NONE);

        SDL_RenderPresent(gScreen);
        SDL_Delay(1000/FPS);
       }

        if(start_menu==false){
            Close();
        }

       for(int i=0;i<5;i++){
        col[i].set_above_x(1308+i*(304.5));
        col[i].set_below_x(1308+i*(304.5));
        col[i].LoadBelow("pipelong.png",gScreen);
        col[i].LoadAbove("pipelong_reversed.png",gScreen);
        col[i].set_speed(-6);
        col[i].set_point_check(point_check);
        col[i].set_hit(hit);
        col[i].set_die(die);
       }

        bool Stop_movement=false;

        string point="Point:";
        string time_var="Time:";
     while(!quit){
       while(SDL_PollEvent(&e)!=0){
          if(e.type==SDL_QUIT)
            quit=true;
       }
       SDL_RenderClear(gScreen);
       Bird.LoadCharacter("bird.png",gScreen);
       Background.render(gScreen,NULL);
       if(Stop_movement==false){
       Bird.vertical_move();
       }
       else if(Stop_movement==true){
        Bird.make_die();
       }
       Bird.render_character(gScreen,NULL,e);

       int time_now= SDL_GetTicks()/1000;
       int h,m,s;
       s=time_now%60;
       m=(time_now/60)%60;
       h=(time_now/60)/60;
       h<10 ? time_var+="0"+to_string(h)+":" : time_var+=to_string(h)+":";
       m<10 ? time_var+="0"+to_string(m)+":" : time_var+=to_string(m)+":";
       s<10 ? time_var+="0"+to_string(s) : time_var+=to_string(s);
       time_record.set_text_var(time_var);
       time_record.LoadFromText(font,gScreen);

       point+=to_string(Point);
       present_Point.set_text_var(point);
       present_Point.LoadFromText(font,gScreen);

       for(int i=0;i<5;i++){
        double a=Bird.get_x();
        double b=Bird.get_y();

        col[i].render_above(gScreen);
        col[i].render_below(gScreen);

        if(col[i].lose(a,b)){
           for(int j=0;j<5;j++){
               col[j].set_speed(0);
               col[j].free_audio();
           }
               Stop_movement=true;
        }

        if(Stop_movement==true){
            suggest.set_text_var(" y: try again    n: exit ");
            game_over.set_text_var("GAMEOVER");
            game_over.LoadFromText(menu_end,gScreen);
            suggest.LoadFromText(font,gScreen);
            game_over.RenderText(gScreen,410,200,NULL,0.0,NULL,SDL_FLIP_NONE);
            suggest.RenderText(gScreen,278,350,NULL,0.0,NULL,SDL_FLIP_NONE);

            if(e.key.keysym.sym==SDLK_y){
            Stop_movement=false;
            for(int k=0;k<5;k++){
        col[k].set_above_x(1308+k*(304.5));
        col[k].set_below_x(1308+k*(304.5));
        col[k].set_speed(-6);
        col[k].set_point_check(point_check);
        col[k].set_hit(hit);
        col[k].set_die(die);
       }
            Bird.set_x((SCREEN_WIDTH-72)/6);
            Bird.set_y(100);
            Bird.set_v0(-12);
            Point=0;
            }
            else if(e.key.keysym.sym==SDLK_n||e.type==SDL_QUIT||e.key.keysym.sym==SDLK_ESCAPE){
            quit=true;
            }
        }

        else if(Stop_movement==false){
        col[i].movement();
          if(Point>5){
        col[i].set_speed(-7);
        }
          if(Point>10&&Point<=15){
        if(i%2!=0)
        col[i].fluctuate();
        }
          if(Point>15&&Point<=20){
        col[i].set_speed(-8);
        if(i%2==0)
        col[i].fluctuate();
        }

        col[i].check_point(a,Point);
        col[i].reset();
        }
       }
       time_record.RenderText(gScreen,30,20,NULL,0.0,NULL,SDL_FLIP_NONE);
       present_Point.RenderText(gScreen,30,55,NULL,0.0,NULL,SDL_FLIP_NONE);
       time_var="Time ";
       point="Point ";
       SDL_RenderPresent(gScreen);
       SDL_Delay((int)1000/FPS);
     }

     Close();
   }

  return 0;
}

