#include "constants.h"
#include "paddle.hpp"

paddle_data::paddle_data()
{
    set_width(PADDLE_WIDTH);
    set_height(PADDLE_HEIGHT);
    set_y(PADDLE_Y);
    speed = PADDLE_SPEED;
    reset();
}

void paddle_data::set_shrunken(bool shrunken)
{
    this->shrunken = shrunken;
}

void paddle_data::reset()
{
    set_x(PADDLE_STARTING_X);
    set_shrunken(false);
}

int paddle_data::get_width()
{
    if (shrunken)
        return unit::get_width() / 2;
    return unit::get_width();
}