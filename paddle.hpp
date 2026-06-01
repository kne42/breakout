#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "unit.hpp"

class paddle_data : unit
{
    int speed;
    bool shrunken;

public:
    paddle_data();
    int get_width();
    void reset();
};

#endif