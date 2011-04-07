#include "camera.h"

Camera::Camera(){
     bounds.x =0;
     bounds.y =0;
     bounds.w = SCREEN_WIDTH;
     bounds.h = SCREEN_HEIGHT;
}

SDL_Rect *Camera::get_bounds(){
    return &bounds;
}

int Camera::get_x(){
    return bounds.x;
}

int Camera::get_y(){
    return bounds.y;
}

int Camera::get_w(){
    return bounds.w;
}

int Camera::get_h(){
    return bounds.h;
}

void Camera::set_x(int x){
    bounds.x = x;
}

void Camera::set_y(int y){
    bounds.y = y;
}
