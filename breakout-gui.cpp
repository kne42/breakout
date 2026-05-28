#include "breakout-core.hpp"

void brick_data::draw(color colour) const
{
    if (!broken)
    {
        unit::draw(colour);
    }
}