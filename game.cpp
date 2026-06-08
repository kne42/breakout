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

int get_brick_row_by_y_from_top(int y)
{
    int start = BRICK_AREA_Y_START;
    int end;

    for (int i = 0; i < NUM_BRICK_ROWS; i++)
    {
        end = start + BRICK_HEIGHT;
        if (y >= start && y <= end)
            return i;
        start = end + BRICK_GAP_Y;
    }

    return -1;
}

int get_brick_row_by_y_from_bottom(int y)
{
    int start = BRICK_AREA_Y_END;
    int end;

    for (int i = NUM_BRICK_ROWS - 1; i >= 0; i--)
    {
        end = start - BRICK_HEIGHT;
        if (y <= start && y >= end)
            return i;
        start = end - BRICK_GAP_Y;
    }

    return -1;
}

int get_brick_col_by_x_from_left(int left, int right)
{
    int start = 0;
    int end;

    for (int i = 0; i < NUM_BRICK_COLS; i++)
    {
        end = start + BRICK_WIDTH;
        if ((left >= start && left <= end) || (right >= start && right <= end))
            return i;
        start = end + BRICK_GAP_X;
    }

    return -1;
}

int get_brick_col_by_x_from_right(int left, int right)
{
    // this can be optimized by having a counterpart that searches right-to-left for when the ball is approaching from the right
    int start = SCREEN_WIDTH;
    int end;

    for (int i = NUM_BRICK_COLS - 1; i >= 0; i--)
    {
        end = start - BRICK_WIDTH;
        if ((left <= start && left >= end) || (right <= start && right >= end))
            return i;
        start = end - BRICK_GAP_X;
    }

    return -1;
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

    set_idle(true);
}

void game_data::set_idle(bool idle)
{
    this->idle = idle;
    paddle.set_idle(idle);
}

void game_data::new_game(bool two_players)
{
    reset();

    this->two_players = two_players;
    active_player = 0;

    int num_players = two_players ? 2 : 1;

    active_player = 0;

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
    // left and right walls
    if (ball.get_left() <= 0 || ball.get_right() >= SCREEN_WIDTH)
    {
        // reflect only if in idle mode or within wall bounds (anything above blue part)
        if (idle || ball.get_top() <= WALL_BOUNDS_END)
            ball.reflect_x();
    }

    if (ball.get_top() <= DIVIDER_END)
    {
        ball.reflect_y();
        ball_phasing = false;
    }

    // detect paddle collision
    paddle_section section = paddle.section_hit(ball);
    if (section)
    {
        ball.reflect_y();
        ball_phasing = false;

        if (!idle)
        {
            if (!vslow)
                ball.set_x_fast();
            else if (section & INNER)
                ball.set_x_slow();
            else
                ball.set_x_fast();

            if (section & LEFT)
                ball.set_moving_left();
            else
                ball.set_moving_right();
        }
    }

    // detect brick collision
    if (!ball_phasing)
    {
        int row = -1;
        int col = -1;
        // ball moving upwards so only need to check with top hitbox and vice versa
        if (ball.is_moving_up())
        {
            const int y_edge = ball.get_top();
            if (y_edge <= BRICK_AREA_Y_END && y_edge >= BRICK_AREA_Y_START)
                row = get_brick_row_by_y_from_bottom(y_edge);
        }
        else
        {
            const int y_edge = ball.get_bottom();
            if (y_edge <= BRICK_AREA_Y_END && y_edge >= BRICK_AREA_Y_START)
                row = get_brick_row_by_y_from_top(y_edge);
        }

        // in brick area
        if (row != -1)
        {
            // ball moving left so only check first from right and vice versa
            if (ball.is_moving_left())
            {
                col = get_brick_col_by_x_from_right(ball.get_left(), ball.get_right());
            }
            else
            {
                col = get_brick_col_by_x_from_left(ball.get_left(), ball.get_right());
            }

            // brick hit
            if (col != -1)
            {
                brick_data &brick = bricks[active_player][row][col];
                if (!brick.is_broken())
                {
                    if (!idle)
                    {
                        brick.set_broken(true);
                        ball_phasing = true;
                    }
                    ball.reflect_y();
                }
            }
        }
    }

    // handle ball move
    ball.move_next_pos();
}

void game_data::reset()
{
    vslow = true;
    ball.respawn(rnd(BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_RIGHT), rnd(BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_BOTTOM));
    paddle.reset();
    ball_phasing = false;
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