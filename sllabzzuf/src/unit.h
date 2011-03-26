#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include "object.h"

class Unit: public Object{
    private:
    int weight, max_hp, hp;
    public:
    Unit();
    Unit(int new_x, int new_y, int new_max_hp);
    void move_x(int x_speed);
    void move_y(int y_speed);
    int get_weight();
    int get_current_hp();
    bool is_alive();
};

#endif // UNIT_H_INCLUDED
