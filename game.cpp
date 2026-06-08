#include "splashkit.h"

#include "constants.h"
#include "game.hpp"

void game_data::bricks_map(int player, brick_func func)
{
    for (int row = 0; row < NUM_BRICK_ROWS; row++)
    {
        for (int col = 0; col < NUM_BRICK_COLS; col++)
        {
            func(bricks[player][row][col], row, col);
        }
    }
}

void game_data::bricks_map(int player, const_brick_func func) const
{
    for (int row = 0; row < NUM_BRICK_ROWS; row++)
    {
        for (int col = 0; col < NUM_BRICK_COLS; col++)
        {
            func(bricks[player][row][col], row, col);
        }
    }
}

void init_brick(brick_data &brick, int row, int col)
{
    brick = brick_data(row, col);
}

void reset_brick(brick_data &brick, int row, int col)
{
    brick.reset();
}

game_data::game_data() : game_data(3) {}

game_data::game_data(int max_serves)
{
    this->max_serves = max_serves;
    bricks_map(0, init_brick);
    bricks_map(1, init_brick);

    new_game(false);
}

void game_data::new_game(bool two_players)
{
    this->two_players = two_players;
    active_player = 0;

    int num_players = two_players ? 2 : 1;

    ball.respawn(rnd(BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_RIGHT), rnd(BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_BOTTOM));
    paddle.reset();

    score[0] = 0;
    score[1] = 0;

    for (int player = 0; player < num_players; player++)
    {
        level_two[player] = false;
        current_serve[player] = 1;

        bricks_map(player, reset_brick);
    }
}

void game_data::update()
{
    // detect wall collisions
    if (ball.get_left() <= 0 || ball.get_right() >= SCREEN_WIDTH)
    {
        ball.reflect_x();
    }

    if (ball.get_top() <= DIVIDER_END || ball.get_bottom() >= SCREEN_HEIGHT)
    {
        ball.reflect_y();
    }

    // handle ball move
    ball.move_next_pos();
}

void game_data::reset()
{
}

int game_data::get_active_player() const
{
    return active_player;
}

int game_data::get_serve() const
{
    return current_serve[active_player];
}

int game_data::get_score(int player) const
{
    return score[player];
}

paddle_data game_data::get_paddle() const
{
    return paddle;
}

ball_data game_data::get_ball() const
{
    return ball;
}