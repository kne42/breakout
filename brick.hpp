#ifndef BRICK_HPP
#define BRICK_HPP

#include "unit.hpp"

class brick_data : public unit
{
    bool broken;
    int row;
    int col;

public:
    brick_data();
    brick_data(int row, int col);

    bool is_broken() const;
    void reset();
};

#endif