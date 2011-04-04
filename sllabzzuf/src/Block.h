#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "object.h"

class Block: public Object{
private:

public:
Block(int startx, int starty);
~Block();
void update_block();
};

#endif // BLOCK_H_INCLUDED
