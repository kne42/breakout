#include "ball.hpp"
#include "constants.h"

/**
 * Constructor
 */

ball_data::ball_data()
{
    set_width(BALL_WIDTH);
    set_height(BALL_HEIGHT);

    respawn(0, 0);
}

/**
 * Getters
 */

int ball_data::get_x_speed() const
{
    return speed.x;
}

int ball_data::get_y_speed() const
{
    return speed.y;
}

int ball_data::get_x_velocity() const
{
    return x_mod * get_x_speed();
}

int ball_data::get_y_velocity() const
{
    return y_mod * get_y_speed();
}

bool ball_data::is_moving_up() const
{
    return y_mod < 0;
}

bool ball_data::is_moving_down() const
{
    return y_mod > 0;
}

bool ball_data::is_moving_left() const
{
    return x_mod < 0;
}
bool ball_data::is_moving_right() const
{
    return x_mod > 0;
}

/**
 * Setters
 */

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

void ball_data::set_moving_up()
{
    y_mod = -1;
}

void ball_data::set_moving_down()
{
    y_mod = 1;
}

void ball_data::set_moving_left()
{
    x_mod = -1;
}

void ball_data::set_moving_right()
{
    x_mod = 1;
}

/**
 * Helpers
 */

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
    pos.x += get_x_velocity();
    pos.y += get_y_velocity();
    return pos;
}

void ball_data::move_next_pos()
{
    set_pos(calc_next_pos());
}