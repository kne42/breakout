#ifndef DRAW_DIGIT_HPP
#define DRAW_DIGIT_HPP

#include "splashkit.h"

const int LINE_HEIGHT = 4;
const int LINE_WIDTH = 6;

const int DIGIT_WIDTH = 18;
const int DIGIT_HEIGHT = 30;

enum digit
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
};

void draw_zero(color colour, int x, int y);
void draw_one(color colour, int x, int y);
void draw_two(color colour, int x, int y);
void draw_three(color colour, int x, int y);
void draw_four(color colour, int x, int y);
void draw_five(color colour, int x, int y);
void draw_six(color colour, int x, int y);
void draw_seven(color colour, int x, int y);
void draw_eight(color colour, int x, int y);
void draw_nine(color colour, int x, int y);

void draw_digit(digit d, color colour, int x, int y);

#endif