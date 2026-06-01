#include "unit.hpp"

void unit::set_pos(const coordinates &pos)
{
    this->pos = pos;
}

void unit::set_x(const double &x)
{
    pos.x = x;
}
void unit::set_y(const double &y)
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

double unit::get_x() const
{
    return pos.x;
}

double unit::get_y() const
{
    return pos.y;
}

coordinates unit::calculate_edge(edge edges) const
{
    // TODO: implement me
    return pos;
}