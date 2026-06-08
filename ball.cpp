#include "ball.hpp"
#include "constants.h"

ball_data::ball_data()
{
    set_width(BALL_WIDTH);
    set_height(BALL_HEIGHT);

    respawn(0, 0);
}

void ball_data::set_x_slow()
{
    speed.x = SPEED_SLOW;
}

void ball_data::set_x_med()
{
    speed.x = SPEED_MEDIUM;
}

void ball_data::set_x_fast()
{
    speed.x = SPEED_FAST;
}

void ball_data::set_y_slow()
{
    speed.y = SPEED_SLOW;
}

void ball_data::set_y_med()
{
    speed.y = SPEED_MEDIUM;
}

void ball_data::set_y_fast()
{
    speed.y = SPEED_FAST;
}

void ball_data::reflect_x()
{
    x_mod *= -1;
}

void ball_data::reflect_y()
{
    y_mod *= -1;
}

void ball_data::respawn(int x, int y)
{
    set_x(x);
    set_y(y);

    x_mod = 1;
    y_mod = 1;

    set_x_slow();
    set_y_slow();
}

coordinates ball_data::calc_next_pos() const
{
    coordinates pos = get_pos();
    pos.x += x_mod * speed.x;
    pos.y += y_mod * speed.y;
    return pos;
}

void ball_data::move_next_pos()
{
    set_pos(calc_next_pos());
}