#include "brick.hpp"
#include "constants.h"

brick_data::brick_data(int row, int col)
{
    this->row = row;
    this->col = col;
    set_width(BRICK_WIDTH);
    set_height(BRICK_HEIGHT);
    set_x(BRICK_OFFSET + col * (get_width() + BRICK_GAP));
    reset();
}

bool brick_data::is_broken() const
{
    return broken;
}

void brick_data::reset()
{
    broken = false;
}