#include <stdio.h>
//#include <string.h>
#include "raylib.h"
#include "resizability.h"

//Updating the variables for the window size. All texts, boxes etc. sizes have to be updated after this function and setWindowSize() has to be called.
void updateWindowSizeVars(int w, int h){
    width  = w;
    height = h;
    center_screenX = width*1/2;
    center_screenY = height*1/2;
}