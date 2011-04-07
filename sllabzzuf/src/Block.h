#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "object.h"
#include "Tile.h"

class Block: public Object{
private:
    int x_velocity;
    int y_velocity;
    int x_acceleration;
    int y_acceleration;
public:
    Block(int startx, int starty);
    ~Block();
    void update_block();
    SDL_Rect get_bounds();
    SDL_Rect getScreenCoord(SDL_Rect* camera);
    bool move_y(int amount, int current_x, int current_y, std::vector<Tile*> tiles, int mapwidthpx, int mapheightpx);
    void update(int gravity, std::vector<Tile* > tiles, int mapwidthpx, int mapheightpx);
    void draw(SDL_Surface *screen, SDL_Rect *camera);
    bool test_spot(int type, int tile_x, int tile_y);
    void load_sprite();
};

#endif // BLOCK_H_INCLUDED
