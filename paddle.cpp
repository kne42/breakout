#include "constants.h"
#include "paddle.hpp"

paddle_data::paddle_data()
{
    set_width(PADDLE_WIDTH);
    set_height(PADDLE_HEIGHT);
    set_y(PADDLE_Y);
    speed = PADDLE_SPEED;
    set_idle(false);
    reset();
}

void paddle_data::set_shrunken(bool shrunken)
{
    this->shrunken = shrunken;
}

void paddle_data::set_idle(bool idle)
{
    this->idle = idle;
}

void paddle_data::reset()
{
    set_x(PADDLE_STARTING_X);
    set_shrunken(false);
}

double paddle_data::get_x() const
{
    if (idle)
        return 0;
    return unit::get_x();
}

int paddle_data::get_width() const
{
    if (idle)
        return SCREEN_WIDTH;
    if (shrunken)
        return unit::get_width() / 2;
    return unit::get_width();
}

paddle_section paddle_data::section_hit(const unit &u)
{
    int section = SECTION_NONE;

    // first determine if in possible paddle area
    const bool right_in = u.get_right() >= get_left() && u.get_right() <= get_right();
    const bool left_in = u.get_left() >= get_left() && u.get_left() <= get_right();
    const bool in_horizontal_space = left_in || right_in;
    // no need to check top overlap since ball can only come from the top
    const bool in_vertical_space = u.get_bottom() >= get_top() && u.get_bottom() <= get_bottom();

    if (in_vertical_space && in_horizontal_space)
    {
        const int unit_middle = u.get_middle().x;
        // check if middle of unit within bounds
        if (unit_middle >= get_left() && unit_middle <= get_right())
        {
            // can calculate which segment hit by unit middle
            const int paddle_middle = get_middle().x;
            bool right_hit = unit_middle > paddle_middle;
            bool inner_hit = unit_middle > paddle_middle - get_width() / 4 && unit_middle < paddle_middle + get_width() / 4;
            section = right_hit ? RIGHT : LEFT;
            section &= inner_hit ? INNER : OUTER;
        }
        // only the edge of unit in bounds
        else
        {
            // if right edge of unit in, it hit on the left side, and vice versa
            section = right_in ? LEFT : RIGHT;
            // since the middle isn't in bounds, it must have hit an outer edge
            section &= OUTER;
        }
    }

    return (paddle_section)section;
}
