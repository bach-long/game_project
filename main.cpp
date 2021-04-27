#include"CMNFUNCTION.h"
#include"Main_object.cpp"
#include"Character.cpp"
#include"Pipe.cpp"
#include"Text_object.cpp"
#include"File_interact.cpp"
#include"refresh_pipe.cpp"
founder Background;//khai bao man hinh chinh
Character Bird;//khai bao nhan vat
Pipe col[5];//khai bao cac Pipe
founder scene[2];
Pipe* pointer=col;
founder Start;//man hinh bat dau

int hightscore=get_high_score("Highest_scores.txt");
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
       bool check=Background.LoadImg("Lsg8aD3.png",gScreen);
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
       Start.LoadImg("start.png",gScreen);
       Start.setRect(254,150);
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
            Close();
            return 0;
            }
        }

        Background.render(gScreen,NULL);
        instruct.RenderText(gScreen,218,400,NULL,0.0,NULL,SDL_FLIP_NONE);
        exit.RenderText(gScreen,450,460,NULL,0.0,NULL,SDL_FLIP_NONE);
        Start.render(gScreen,NULL);

        SDL_RenderPresent(gScreen);
       }

       for(int i=0;i<2;i++){
        scene[i].LoadImg("Lsg8aD3.png",gScreen);
        scene[i].speed_set(-1);
       }
       scene[0].setRect(0,0);
       scene[1].setRect(1308,0);
       for(int i=0;i<5;i++){
        col[i].set_above_x(1308+i*(304.5));
        col[i].set_below_x(1308+i*(304.5));
        col[i].LoadBelow("pipelong.png",gScreen);
        col[i].LoadAbove("pipelong_reversed.png",gScreen);
        col[i].set_speed(-5);
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
       for(int i=0;i<2;i++){
        scene[i].render(gScreen,NULL);
        scene[i].move_scene();
        scene[i].reset_scene();
       }
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
            int a;
            if(Point>hightscore){
                save_high_score("Highest_scores.txt",Point);
                game_over.set_text_var("NEW RECORD: "+to_string(Point));
                a=275;
            }
            else{
                game_over.set_text_var("Total:"+to_string(Point));
                a=400;
            }
            suggest.set_text_var(" y: Try again    n: Exit ");

            game_over.LoadFromText(menu_end,gScreen);
            suggest.LoadFromText(font,gScreen);
            game_over.RenderText(gScreen,a,200,NULL,0.0,NULL,SDL_FLIP_NONE);
            suggest.RenderText(gScreen,270,350,NULL,0.0,NULL,SDL_FLIP_NONE);
            if(e.key.keysym.sym==SDLK_y){
            Stop_movement=false;
            refresh(col,5);
            Bird.set_x((SCREEN_WIDTH-72)/6);
            Bird.set_y(100);
            Bird.set_v0(-15);
            Point=0;
            e.key.keysym.sym=SDLK_a;
            }
            if(e.key.keysym.sym==SDLK_n||e.type==SDL_QUIT||e.key.keysym.sym==SDLK_ESCAPE){
            quit=true;
            }
        }

        else if(Stop_movement==false){
        col[i].movement();
          if(Point>15&&Point<=25){
        if(i%2!=0)
        col[i].fluctuate();
        }
        //thiet lap level
          if(Point>25&&Point<=35){
        col[i].set_speed(-6);
        if(i%2==0)
        col[i].collid();
        }
          if(Point>35&&Point<=45){
        if(i%2!=0)
        col[i].fluctuate();
        }
        //
        col[i].check_point(a,Point);
        col[i].reset();
        }
       }
       time_record.RenderText(gScreen,30,20,NULL,0.0,NULL,SDL_FLIP_NONE);
       present_Point.RenderText(gScreen,30,55,NULL,0.0,NULL,SDL_FLIP_NONE);
       time_var="Time:";
       point="Point:";
       SDL_RenderPresent(gScreen);
       SDL_Delay((int)1000/FPS);
     }

     Close();
   }

  return 0;
}

