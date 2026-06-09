#include "unit.hpp"

/**
 * Getters
 */

int unit::get_width() const
{
    return width;
}

int unit::get_height() const
{
    return height;
}

coordinates unit::get_pos() const
{
    return pos;
}

int unit::get_x() const
{
    return pos.x;
}

int unit::get_y() const
{
    return pos.y;
}

int unit::get_left() const
{
    return get_x();
}

int unit::get_right() const
{
    return get_x() + get_width();
}

int unit::get_top() const
{
    return get_y();
}

int unit::get_bottom() const
{
    return get_y() + get_height();
}

coordinates unit::get_middle() const
{
    coordinates middle;
    middle.x = get_x() + get_width() / 2;
    middle.y = get_y() + get_height() / 2;
    return middle;
}

/**
 * Setters
 */

void unit::set_pos(const coordinates &pos)
{
    this->pos = pos;
}

void unit::set_x(const int &x)
{
    pos.x = x;
}
void unit::set_y(const int &y)
{
    pos.y = y;
}
void unit::set_width(const int &width)
{
    this->width = width;
}
void unit::set_height(const int &height)
{
    this->height = height;
}