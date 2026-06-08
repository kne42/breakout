#include "ball.hpp"
#include "constants.h"

ball_data::ball_data() : ball_data(0, 0, 0, 0) {}

ball_data::ball_data(int x, int y, int speed, int direction)
{
    set_width(BALL_WIDTH);
    set_height(BALL_HEIGHT);
    set_velocity(speed, direction);
    set_x(x);
    set_y(y);
    phasing = false;
    velocity_multiplier = 1;
}

void ball_data::set_velocity(int speed, int direction)
{
}