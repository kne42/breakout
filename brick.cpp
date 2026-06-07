#include "splashkit.h"

#include "brick.hpp"
#include "constants.h"

brick_data::brick_data()
{
    broken = true;
}

brick_data::brick_data(int row, int col)
{
    this->row = row;
    this->col = col;
    set_width(BRICK_WIDTH);
    set_height(BRICK_HEIGHT);
    set_x(col * (get_width() + BRICK_GAP_X));
    set_y(BRICK_AREA_Y_START + row * (get_height() + BRICK_GAP_Y));
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

// GUI

void brick_data::draw(color colour) const
{
    if (!broken)
    {
        unit::draw(colour);
    }
}