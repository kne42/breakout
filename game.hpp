#ifndef GAME_HPP
#define GAME_HPP

#include <array>

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

    bool idle;
    bool vslow;
    bool serve_wait;
    bool ball_phasing;

    brick_data bricks[2][NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle;

    void set_idle(bool idle);
    void bricks_map(int player, brick_func func);

public:
    game_data();
    game_data(int max_serves);
    void new_game(bool two_players);
    void reset();
    int swap_players();
    void new_round();

    int get_active_player() const;
    paddle_data get_paddle() const;
    ball_data get_ball() const;
    int get_serve() const;
    int get_score(int player) const;

    void bricks_map(int player, const_brick_func func) const;

    void handle_wall_collision();
    void handle_paddle_collision();
    void handle_brick_collision();

    void handle_paddle_input();

    void update();
};

#endif