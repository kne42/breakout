#include "breakout-core.hpp"

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

ball_data::ball_data(int x, int y, int speed, int direction)
{
    set_width(BALL_SIZE);
    set_height(BALL_SIZE);
    // velocity = vector based on speed and direction
    set_x(x);
    set_y(y);
    phasing = false;
}

paddle_data::paddle_data()
{
    set_width(PADDLE_WIDTH);
    set_height(PADDLE_HEIGHT);
    set_y(PADDLE_Y);
    speed = PADDLE_SPEED;
    reset();
}

void paddle_data::reset()
{
    set_x(PADDLE_STARTING_X);
    shrunken = false;
}

int paddle_data::get_width()
{
    if (shrunken)
        return unit::get_width() / 2;
    return unit::get_width();
}