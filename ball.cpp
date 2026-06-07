#include "ball.hpp"
#include "constants.h"

ball_data::ball_data(int x, int y, int speed, int direction)
{
    set_width(BALL_SIZE);
    set_height(BALL_SIZE);
    set_velocity(speed, direction);
    set_x(x);
    set_y(y);
    phasing = false;
}