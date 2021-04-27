# pragma once
# include "CMNFUNCTION.h"
static int get_high_score(string file_path){
 ifstream file(file_path.c_str());
 int a;
 file>>a;
 file.close();
 return a;
}

static void save_high_score(string file_path,int a){
 ofstream file(file_path.c_str());
 file<<a;
 file.close();
}
