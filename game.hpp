#ifndef GAME_HPP
#define GAME_HPP

#include "splashkit.h"

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
    unsigned short lives[2];

    brick_data bricks[2][NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle;

    void bricks_map(int player, brick_func func);
    void bricks_map(int player, const_brick_func func) const;
    static void draw_brick(const brick_data &brick, int row, int col);
    static void init_brick(brick_data &brick, int row, int col);
    void draw_walls(color colour, int y, int height) const;

public:
    game_data();
    game_data(bool two_players);
    void new_game(bool two_players);
    void update();
    void draw() const;
    int lose_life();
    void reset_difficulty();
    int swap_players();
    void new_round();
};

#endif