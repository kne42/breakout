#ifndef GAME_HPP
#define GAME_HPP

#include "unit.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "constants.h"

class game_data
{
    bool coop_mode;
    bool level_two;
    brick_data bricks[NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle_p1;
    paddle_data paddle_p2;
    int score;
    unsigned short lives;

public:
    game_data();
    bool is_coop_mode();
    void new_game(bool coop_mode);
    void update();
    void draw();
};

#endif