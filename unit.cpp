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
    coordinates edge;
    if (edges & EDGE_TOP)
    {
        edge.y = get_y();
    }
    else if (edges & EDGE_BOTTOM)
    {
        edge.y = get_y() + get_height();
    }
    else
    {
        edge.y = get_y() + get_height() / 2;
    }

    if (edges & EDGE_LEFT)
    {
        edge.x = get_x();
    }
    else if (edges & EDGE_RIGHT)
    {
        edge.x = get_x() + get_width();
    }
    else
    {
        edge.x = get_x() + get_width() / 2;
    }

    return edge;
}

double unit::get_left() const
{
    return get_x();
}

double unit::get_right() const
{
    return get_x() + get_width();
}

double unit::get_top() const
{
    return get_y();
}

double unit::get_bottom() const
{
    return get_y() + get_height();
}