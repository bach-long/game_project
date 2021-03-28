
#include"Main_object.cpp"
#include"Character.cpp"
#include"Pipe.cpp"
founder Background;//khai bao man hinh chinh
Character Bird;//khai bao nhan vat
Pipe col[5];//khai bao cac Pipe
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
       bool quit=false;
       for(int i=0;i<5;i++){
        col[i].set_above_x(1308+i*(304.5));
        col[i].set_below_x(1308+i*(304.5));
        col[i].LoadBelow("pipelong.png",gScreen);
        col[i].LoadAbove("pipelong_reversed.png",gScreen);
        col[i].set_speed(-5);
       }
     while(!quit){
       while(SDL_PollEvent(&e)!=0){
          if(e.type==SDL_QUIT)
            quit=true;
       }
       SDL_RenderClear(gScreen);
       Bird.LoadCharacter("bird.png",gScreen);
       Background.render(gScreen,NULL);
       Bird.render_character(gScreen,NULL,e);

       for(int i=0;i<5;i++){
        col[i].render_above(gScreen);
        col[i].render_below(gScreen);
        col[i].reset();
        col[i].movement();
       }
       SDL_RenderPresent(gScreen);
     }
   }


  return 0;
}
