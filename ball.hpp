#ifndef BALL_HPP
#define BALL_HPP

#include "unit.hpp"

class ball_data : public unit
{
    coordinates velocity_vector;
    float velocity_multiplier;
    bool phasing;

public:
    ball_data();
    ball_data(int x, int y, int speed, int direction);
    void set_velocity(int speed, int direction);
};

#endif