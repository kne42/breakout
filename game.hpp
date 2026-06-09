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
    int active_player = 0;
    bool two_players = false;
    int score[2] = {0, 0};
    unsigned short current_serve = 1;
    int max_serves;

    bool high_value_brick_hit;
    int volley_counter;

    bool idle;
    bool vslow = true;
    bool waiting_for_serve = false;
    bool ball_phasing = false;

    brick_data bricks[2][NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle;

    void set_idle(bool idle);
    void bricks_map(int player, brick_func func);
    void spawn_ball();
    void set_current_score(int score);
    int score_points(int points);
    void increment_volley_counter();

public:
    game_data();
    game_data(int max_serves);
    void new_game();
    void reset();
    void swap_players();
    void start_round();
    void end_round();
    void end_game();

    int get_active_player() const;
    paddle_data get_paddle() const;
    ball_data get_ball() const;
    int get_serve() const;
    int get_score(int player) const;
    int get_current_score() const;
    bool is_idle() const;
    bool is_waiting_for_serve() const;
    int num_players() const;

    void bricks_map(int player, const_brick_func func) const;

    void handle_wall_collision();
    void handle_paddle_collision();
    void handle_brick_collision();
    void handle_ball_out_of_bounds();

    void set_ball_y_speed();

    void handle_serve_start();
    void handle_paddle_input();
    void handle_mode_start();

    void update();
};

#endif