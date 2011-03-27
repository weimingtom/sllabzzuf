#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED
#include "map.h"
#include "camera.h"

class Stage{
private:
    Map map;
    Camera camera;
    int gravity;
public:
    Stage();
    Stage(std::string filename);
    ~Stage();
    void display_terrain(SDL_Surface *screen);
    void newMap(std::string mapname);
    int get_camera_x();
    int get_camera_y();
    int get_camera_w();
    int get_camera_h();
    void set_camera_x(int x);
    void set_camera_y(int y);
    int get_mapHeightpx();
    int get_mapWidthpx();
    int get_theme();
    int get_gravity();
    void center_camera(int player_x, int player_y, int player_w, int player_h);
    bool object_hitTest(int direction, int x, int y);

};

#endif // STAGE_H_INCLUDED
