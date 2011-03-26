#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED
#include "map.h"
#include "camera.h"

class Stage{
private:
    Map map;
    Camera camera;
public:
    Stage();
    Stage(std::string filename);
    ~Stage();
    void display_terrain(SDL_Surface *screen);
    void newMap();
    int get_camera_x();
    int get_camera_y();
    int get_camera_w();
    int get_camera_h();
    void set_camera_x(int x);
    void set_camera_y(int y);
    int get_mapHeightpx();
    int get_mapWidthpx();

};

#endif // STAGE_H_INCLUDED
