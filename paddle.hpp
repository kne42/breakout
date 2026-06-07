#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "unit.hpp"

class paddle_data : public unit
{
    int speed;
    bool shrunken;

public:
    paddle_data();
    int get_width();
    void set_shrunken(bool shrunken);
    void reset();
};

#endif