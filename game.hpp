#ifndef GAME_HPP
#define GAME_HPP

#include "unit.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "constants.h"

using brick_func = void (*)(brick_data &brick, int row, int col);
using const_brick_func = void (*)(const brick_data &brick, int row, int col);

class game_data
{
    int active_player;
    bool two_players;
    bool level_two[2];
    int score[2];
    unsigned short current_serve[2];
    int max_serves;

    bool vslow = true;

    brick_data bricks[2][NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle;

    void bricks_map(int player, brick_func func);

public:
    game_data();
    game_data(int max_serves);
    void new_game(bool two_players);
    void update();
    void reset();
    int swap_players();
    void new_round();

    int get_active_player() const;
    paddle_data get_paddle() const;
    ball_data get_ball() const;
    int get_serve() const;
    int get_score(int player) const;

    void bricks_map(int player, const_brick_func func) const;
};

#endif