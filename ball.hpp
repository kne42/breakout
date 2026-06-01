#ifndef BALL_HPP
#define BALL_HPP

#include "unit.hpp"

class ball_data : unit
{
    coordinates velocity;
    float velocity_multiplier;
    bool phasing;

public:
    ball_data(int x, int y, int speed, int direction);
};

#endif