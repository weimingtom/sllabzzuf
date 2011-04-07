#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED
#include "Map.h"
#include "Camera.h"
#include "Player.h"

class Stage{
private:
    Map map;
    Camera camera;
    Player player;
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
    void rotate(int direction);
    void center_camera(int player_x, int player_y, int player_w, int player_h);
    bool object_hitTest(int direction, int x, int y);
    bool is_done(int x, int y);
    void finish_map();
    void display_objects(SDL_Surface *screen);
    void update_blocks();
};

#endif // STAGE_H_INCLUDED
