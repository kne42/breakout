#include "splashkit.h"

#include "draw-digit.hpp"

void draw_top_line(color colour, int x, int y, bool overlap_start = true, bool overlap_end = true)
{
    if (!overlap_start)
        x += LINE_WIDTH;

    int overlaps = !overlap_start + !overlap_end;

    fill_rectangle(colour, x, y, DIGIT_WIDTH - overlaps * LINE_WIDTH, LINE_HEIGHT);
}

void draw_bottom_line(color colour, int x, int y, bool overlap_start = true, bool overlap_end = true)
{
    y += DIGIT_HEIGHT;
    y -= LINE_HEIGHT;

    if (!overlap_start)
        x += LINE_WIDTH;

    int overlaps = !overlap_start + !overlap_end;

    fill_rectangle(colour, x, y, DIGIT_WIDTH - overlaps * LINE_WIDTH, LINE_HEIGHT);
}

void draw_middle_line(color colour, int x, int y, bool overlap_start = true, bool overlap_end = true)
{
    y += DIGIT_HEIGHT / 2;
    y -= LINE_HEIGHT / 2;

    if (!overlap_start)
        x += LINE_WIDTH;

    int overlaps = !overlap_start + !overlap_end;

    fill_rectangle(colour, x, y, DIGIT_WIDTH - overlaps * LINE_WIDTH, LINE_HEIGHT);
}

void draw_left_line(color colour, int x, int y, bool overlap_start = true, bool overlap_end = true)
{
    if (!overlap_start)
        y += LINE_HEIGHT;

    int overlaps = !overlap_start + !overlap_end;

    fill_rectangle(colour, x, y, LINE_WIDTH, DIGIT_HEIGHT - overlaps * LINE_HEIGHT);
}

void draw_right_line(color colour, int x, int y, bool overlap_start = true, bool overlap_end = true)
{
    x += DIGIT_WIDTH;
    x -= LINE_WIDTH;

    if (!overlap_start)
        y += LINE_HEIGHT;

    int overlaps = !overlap_start + !overlap_end;

    fill_rectangle(colour, x, y, LINE_WIDTH, DIGIT_HEIGHT - overlaps * LINE_HEIGHT);
}

void draw_top_left_connector(color colour, int x, int y, bool overlap = true)
{
    int height = DIGIT_HEIGHT / 2;
    height -= LINE_HEIGHT / 2;

    if (!overlap)
    {
        y += LINE_HEIGHT;
        height -= LINE_HEIGHT;
    }

    fill_rectangle(colour, x, y, LINE_WIDTH, height);
}

void draw_top_right_connector(color colour, int x, int y, bool overlap = true)
{
    int height = DIGIT_HEIGHT / 2;
    height -= LINE_HEIGHT / 2;

    if (!overlap)
    {
        y += LINE_HEIGHT;
        height -= LINE_HEIGHT;
    }

    x += DIGIT_WIDTH;
    x -= LINE_WIDTH;

    fill_rectangle(colour, x, y, LINE_WIDTH, height);
}

void draw_bottom_left_connector(color colour, int x, int y, bool overlap = true)
{
    int height = DIGIT_HEIGHT / 2;
    height -= LINE_HEIGHT / 2;

    y += DIGIT_HEIGHT / 2;
    y += LINE_HEIGHT / 2;

    if (!overlap)
    {
        height -= LINE_HEIGHT;
    }

    fill_rectangle(colour, x, y, LINE_WIDTH, height);
}

void draw_bottom_right_connector(color colour, int x, int y, bool overlap = true)
{
    int height = DIGIT_HEIGHT / 2;
    height -= LINE_HEIGHT / 2;

    y += DIGIT_HEIGHT / 2;
    y += LINE_HEIGHT / 2;

    if (!overlap)
    {
        height -= LINE_HEIGHT;
    }

    x += DIGIT_WIDTH;
    x -= LINE_WIDTH;

    fill_rectangle(colour, x, y, LINE_WIDTH, height);
}

void draw_zero(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_bottom_line(colour, x, y);
    draw_left_line(colour, x, y, false, false);
    draw_right_line(colour, x, y, false, false);
}

void draw_one(color colour, int x, int y)
{
    draw_right_line(colour, x, y);
}

void draw_two(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_middle_line(colour, x, y);
    draw_bottom_line(colour, x, y);
    draw_top_right_connector(colour, x, y, false);
    draw_bottom_left_connector(colour, x, y, false);
}

void draw_three(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_bottom_line(colour, x, y);
    draw_middle_line(colour, x, y, true, false);
    draw_right_line(colour, x, y, false, false);
}

void draw_four(color colour, int x, int y)
{
    draw_top_left_connector(colour, x, y);
    draw_middle_line(colour, x, y, true, false);
    draw_right_line(colour, x, y);
}

void draw_five(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_middle_line(colour, x, y);
    draw_bottom_line(colour, x, y);
    draw_top_left_connector(colour, x, y, false);
    draw_bottom_right_connector(colour, x, y, false);
}

void draw_six(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_middle_line(colour, x, y, false);
    draw_left_line(colour, x, y, false);
    draw_bottom_right_connector(colour, x, y, false);
    draw_bottom_line(colour, x, y, false);
}

void draw_seven(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_right_line(colour, x, y, false);
}

void draw_eight(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_bottom_line(colour, x, y);
    draw_middle_line(colour, x, y, false, false);
    draw_left_line(colour, x, y, false, false);
    draw_right_line(colour, x, y, false, false);
}

void draw_nine(color colour, int x, int y)
{
    draw_top_line(colour, x, y);
    draw_middle_line(colour, x, y, true, false);
    draw_right_line(colour, x, y, false, true);
    draw_top_left_connector(colour, x, y, false);
}

void draw_digit(digit d, color colour, int x, int y)
{
    switch (d)
    {
    case ZERO:
        draw_zero(colour, x, y);
        break;
    case ONE:
        draw_one(colour, x, y);
        break;
    case TWO:
        draw_two(colour, x, y);
        break;
    case THREE:
        draw_three(colour, x, y);
        break;
    case FOUR:
        draw_four(colour, x, y);
        break;
    case FIVE:
        draw_five(colour, x, y);
        break;
    case SIX:
        draw_six(colour, x, y);
        break;
    case SEVEN:
        draw_seven(colour, x, y);
        break;
    case EIGHT:
        draw_eight(colour, x, y);
        break;
    case NINE:
        draw_nine(colour, x, y);
        break;
    }
}