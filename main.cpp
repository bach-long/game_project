
#include"CommonFunction.h"
#include"pipe.cpp"
const int SCREEN_WIDTH=1308;
const int SCREEN_HEIGH=736;
int point=0;
double speed=-0.7;

static SDL_Window* gWindow=NULL;
static SDL_Surface* gScreen=NULL;
SDL_Surface* Start=NULL;
SDL_Surface* Gameover=NULL;
SDL_Surface* gBackground=NULL;
SDL_Surface* gCharacter=NULL;

using namespace std;
void close(){
    SDL_DestroyWindow(gWindow);
    SDL_FreeSurface(gScreen);
    SDL_FreeSurface(gBackground);
    SDL_FreeSurface(gCharacter);
}

//SDL_Surface* gCharacter=NULL;

bool Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        return false;
    }
    else{
        gWindow=SDL_CreateWindow("game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGH,SDL_WINDOW_SHOWN);
        gScreen=SDL_GetWindowSurface(gWindow);
        if(gScreen==NULL)
            return false;
        else
        return true;
        }
}

int main(int argc, char* argv[]){
    srand(time(0));
    if(Init()==false){
        cout<<"failed to initialize: "<< SDL_GetError();
    }
    else{
        Start=LoadImg("start.png",gScreen);
        gBackground=LoadImg("4622688.png",gScreen);
        gCharacter=LoadImg("151328547_3620854374657174_3351164430039052146_n.png",gScreen);

        if(gBackground==NULL||gCharacter==NULL||Start==NULL){
            cout<<"fail to upload background: "<<SDL_GetError();
        }
        else{
        double a=(SCREEN_WIDTH-72)/6,b=(SCREEN_HEIGH-50)/2,v0=0;
        SDL_Event e;
        bool quit=false;
        bool start_menu=false;
          list<Pipe>Obs;
          Pipe Obs_test[5];
          for(int i=0;i<5;i++){
            Obs_test[i].x=1308+i*(304.5);
            Obs_test[i].x2=Obs_test[i].x;
            Obs_test[i].y=rand()%(650-400+1)+400;
            Obs_test[i].blank=rand()%(270-155+1)+155;
            Obs_test[i].y2=Obs_test[i].y-Obs_test[i].blank-600;
            Obs_test[i].Below_column=LoadImg("pipelong.png",gScreen);
            Obs_test[i].Above_column=LoadImg("pipelong_reversed.png",gScreen);
            Obs.push_back(Obs_test[i]);
        }
       while(!start_menu){
            SDL_BlitSurface(gBackground,NULL,gScreen,NULL);
            ApplySurface(Start,gScreen,254,267.5);
            while(SDL_PollEvent(&e)!=0){
            if(e.type==SDL_MOUSEBUTTONDOWN){
            start_menu=true;
            break;
            }
            else if(e.key.keysym.sym==SDLK_ESCAPE){
            close();
            SDL_Quit();
            }
            }
            SDL_UpdateWindowSurface(gWindow);
        }
        SDL_FreeSurface(Start);
        while(!quit){
            SDL_BlitSurface(gBackground,NULL,gScreen,NULL);
            while(SDL_PollEvent(&e)!=0){
                if(e.type==SDL_QUIT){
                    quit=true;
                    break;
                    }
            }
            ApplySurface(gCharacter,gScreen,a,b);
            if(e.type==SDL_MOUSEBUTTONDOWN){
               v0=-0.875;
               b+=v0+0.01*0.5;
            }
            else if(e.type==SDL_MOUSEBUTTONUP||e.type==SDL_MOUSEMOTION){
             v0+=0.0125;
             b+=v0+0.005*0.5;
            }

            for(list<Pipe>::iterator i=Obs.begin();i!=Obs.end();i++)
            {
              (*i).reset();

              (*i).x+=speed ;
              (*i).x2+=speed ;

               ApplySurface((*i).Below_column,gScreen,(*i).x,(*i).y);
               ApplySurface((*i).Above_column,gScreen,(*i).x2,(*i).y2);

                if((*i).lose(a,b)){
                  quit=true;
               }
               else if((*i).get_point(a,b)){
                  point++;
               }

            }


            ApplySurface(gCharacter,gScreen,a,b);
             SDL_UpdateWindowSurface(gWindow);


        }
        cout<<point;
        }

    }

    close();
    SDL_Quit();
    return 0;
}
