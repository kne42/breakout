#ifndef BALL_HPP
#define BALL_HPP

#include "unit.hpp"

enum speed
{
    SPEED_SLOW = 1,
    SPEED_MEDIUM = 2,
    SPEED_FAST = 3,
};

class ball_data : public unit
{
    coordinates speed;
    short x_mod;
    short y_mod;

public:
    ball_data();

    void set_x_slow();
    void set_x_med();
    void set_x_fast();

    void set_y_slow();
    void set_y_med();
    void set_y_fast();

    void reflect_x();
    void reflect_y();

    void respawn(int x, int y);

    coordinates calc_next_pos() const;
};

#endif