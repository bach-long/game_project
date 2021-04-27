# pragma once
# include "Pipe.cpp"
# include "CMNFUNCTION.h"
static void refresh(Pipe* colm ,int n){
    for(int k=0;k<n;k++){
        colm[k].set_above_x(1308+k*(304.5));
        colm[k].set_below_x(1308+k*(304.5));
        colm[k].set_speed(-5);
        colm[k].set_point_check(point_check);
        colm[k].set_hit(hit);
        colm[k].set_die(die);
        colm[k].set_below_y(rand()%(550-270+1)+270);
        colm[k].set_blank(rand()%(280-150+1)+150);
        colm[k].set_above_y(colm[k].get_below_y()-800-colm[k].get_blank());
       }
}
