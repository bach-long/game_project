
#include"CommonFunction.h"

class Pipe{
public:
    int cnt=0;
    double x;//hoanh do cot duoi
    double y;//tung do cot duoi
    double x2;//hoanh do cot tren
    double y2;//tung do cot tren
    int blank;//khoang trong 2 cot
    double speed;//toc do
    SDL_Surface* Below_column;
    SDL_Surface* Above_column;
    Pipe(){
    }
    void reset(){
        if(this->x+90<0){
            this->x=1432.5;
            this->x2=this->x;
            this->y=rand()%(650-400+1)+400;
            this->blank=rand()%(270-155+1)+155;
            this->y2=this->y-this->blank-600;
        }
    }
    bool lose(double& a,double& b){
        if(b+40>736)
            return true;
        else if(a<=this->x&&a+58>=this->x&&(b<this->y2+600||b+40>this->y))
            return true;
        else if(a<=this->x+90&&a+58>=this->x+90&&(b<this->y2+600||b+40>this->y))
            return true;
        else
            return false;
    }
    bool get_point(double& a,double& b){
        if(b+40<=this->y&&b>=this->y-this->blank&&a+58<this->x+90.11&&a+58>this->x+89.99)
            return true;
        else
            return false;
    }


};
