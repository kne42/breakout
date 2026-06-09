#include "brick.hpp"
#include "constants.h"

/**
 * Constructors
 */

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

/**
 * Getters
 */

bool brick_data::is_broken() const
{
    return broken;
}

/**
 * Setters
 */

void brick_data::set_broken(bool broken)
{
    this->broken = broken;
}

/**
 * Helpers
 */

void brick_data::reset()
{
    set_broken(false);
}