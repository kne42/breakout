#include "splashkit.h"
#include "unit.hpp"

void unit::draw(color colour) const
{
    draw_rectangle(colour, get_x(), get_y(), get_width(), get_height());
}
