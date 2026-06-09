#include "splashkit.h"

#include "constants.h"
#include "debug.h"
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

/**
 * Brick map helpers.
 */

void init_brick(brick_data &brick, int row, int col)
{
    brick = brick_data(row, col);
}

void reset_brick(brick_data &brick, int row, int col)
{
    brick.reset();
}

void game_data::reset_bricks(int player)
{
    bricks_map(player, reset_brick);
}

game_data::game_data() : game_data(3) {}

game_data::game_data(int max_serves)
{
    this->max_serves = max_serves;
    bricks_map(0, init_brick);
    bricks_map(1, init_brick);

    spawn_ball();
    set_idle(true);
}

void game_data::set_current_score(int score)
{
    this->score[active_player] = score;
}

int game_data::get_current_score() const
{
    return score[active_player];
}

void game_data::set_idle(bool idle)
{
    this->idle = idle;
    paddle.set_idle(idle);
}

bool game_data::is_idle() const
{
    return idle;
}

void game_data::spawn_ball()
{
    ball.respawn(rnd(BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_RIGHT), rnd(BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_BOTTOM));
}

void game_data::new_game()
{
    reset_ball_state();

    active_player = 0;

    score[0] = 0;
    score[1] = 0;
    current_serve = 1;

    waiting_for_serve = true;

    for (int player = 0; player < num_players(); player++)
    {
        reset_bricks(player);
    }
}

void game_data::end_round()
{
    reset_ball_state();

    if (!two_players || active_player == 1)
        current_serve++;

    if (!DEBUG_INFINITE_LIVES && get_serve() > max_serves)
    {
        end_game();
    }

    if (two_players)
    {
        swap_players();
    }
}

void game_data::start_round()
{
    spawn_ball();
    waiting_for_serve = false;
    set_idle(false);
}

void game_data::end_game()
{
    waiting_for_serve = false;
    spawn_ball();
    set_idle(true);
}

void game_data::reset_ball_state()
{
    waiting_for_serve = true;
    vslow = true;
    ball_phasing = false;
    volley_counter = 0;
    high_value_brick_hit = false;
    paddle.set_shrunken(false);
}

int game_data::get_active_player() const
{
    return active_player;
}

int game_data::get_serve() const
{
    return current_serve;
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

int game_data::score_points(int points)
{
    int &current_score = score[active_player];

    // orange or red brick hit
    if (points >= BRICK_POINTS[1])
        high_value_brick_hit = true;

    current_score += points;
    return current_score;
}

void game_data::increment_volley_counter()
{
    if (volley_counter < 12)
        volley_counter++;
}

void game_data::set_ball_y_speed()
{
    if (high_value_brick_hit)
    {
        vslow = false;
        ball.set_y_fast();
    }
    else
    {
        if (volley_counter < 4)
        {
            ball.set_y_slow();
        }
        else if (volley_counter < 8)
        {
            ball.set_y_med();
        }
        else if (volley_counter < 12)
        {
            ball.set_y_slow();
        }
        else
        {
            ball.set_y_med();
        }

        if (volley_counter >= 8)
            vslow = false;
    }
}

bool game_data::is_waiting_for_serve() const
{
    return waiting_for_serve;
}

int game_data::num_players() const
{
    return two_players ? 2 : 1;
}

void game_data::swap_players()
{
    active_player = active_player == 0 ? 1 : 0;
}