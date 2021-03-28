#ifndef MAIN_OBJECT_H_INCLUDED
#define MAIN_OBJECT_H_INCLUDED
#include"CMNFUNCTION.h"
class founder{
   protected:
    SDL_Texture* prime_object;
    SDL_Rect rect;

   public:
   founder(){};
   ~founder(){};
   void setRect(int& x,int& y){rect.x=x;rect.y=y;};
   SDL_Rect getRect(){return rect;};
   SDL_Texture* getTexture(){return prime_object;};

   bool LoadImg(string path,SDL_Renderer* screen);
   void render(SDL_Renderer* des, SDL_Rect* clip=NULL);
};

#endif // MAIN_OBJECT_H_INCLUDED
