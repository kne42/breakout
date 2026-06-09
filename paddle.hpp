#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "unit.hpp"

enum paddle_section
{
    SECTION_NONE = 0b0000,
    INNER = 0b0110,
    OUTER = 0b1001,
    LEFT = 0b1100,
    RIGHT = 0b0011,
    A = LEFT & OUTER,
    B = LEFT & INNER,
    C = RIGHT & INNER,
    D = RIGHT & OUTER,
};

class paddle_data : public unit
{
    int speed;
    bool shrunken;
    bool idle;

public:
    paddle_data();

    double get_x() const override;
    int get_width() const override;

    void set_shrunken(bool shrunken);
    void set_idle(bool idle);

    void move_left();
    void move_right();
    void move_center();

    paddle_section section_hit(const unit &u);
};

#endif