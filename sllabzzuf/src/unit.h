#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include "object.h"

class Unit: public Object{
    protected:
    int weight, max_hp, hp;
    public:
    Unit();
    Unit(int new_x, int new_y, int new_max_hp);
    void add_hp(int amount);
    int get_weight();
    int get_hp();
    bool is_alive();
};

#endif // UNIT_H_INCLUDED
