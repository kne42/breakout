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

    int get_x_speed() const;
    int get_y_speed() const;

    int get_x_velocity() const;
    int get_y_velocity() const;

    void set_x_slow();
    void set_x_med();
    void set_x_fast();

    void set_y_slow();
    void set_y_med();
    void set_y_fast();

    void reflect_x();
    void reflect_y();

    bool is_moving_up() const;
    bool is_moving_left() const;

    void set_moving_up();
    void set_moving_down();
    void set_moving_left();
    void set_moving_right();

    void respawn(int x, int y);

    coordinates calc_next_pos() const;
    void move_next_pos();
};

#endif