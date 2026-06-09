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

/**
 * Brick-finder helpers.
 */

int get_brick_row_by_y_from_top(int y)
{
    int start = BRICK_AREA_Y_START;
    int end;

    for (int i = 0; i < NUM_BRICK_ROWS; i++)
    {
        end = start + BRICK_HEIGHT + BRICK_GAP_Y;
        if (y >= start && y <= end)
            return i;
        start = end;
    }

    return -1;
}

int get_brick_row_by_y_from_bottom(int y)
{
    int start = BRICK_AREA_Y_END;
    int end;

    for (int i = NUM_BRICK_ROWS - 1; i >= 0; i--)
    {
        end = start - BRICK_HEIGHT - BRICK_GAP_Y;
        if (y <= start && y >= end)
            return i;
        start = end;
    }

    return -1;
}

int get_brick_col_by_x_from_left(int left, int right)
{
    int start = 0;
    int end;

    for (int i = 0; i < NUM_BRICK_COLS; i++)
    {
        end = start + BRICK_WIDTH + BRICK_GAP_X;
        if ((left >= start && left <= end) || (right >= start && right <= end))
            return i;
        start = end;
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
        end = start - BRICK_WIDTH - BRICK_GAP_X;
        if ((left <= start && left >= end) || (right <= start && right >= end))
            return i;
        start = end;
    }

    return -1;
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

bool game_data::get_idle() const
{
    return idle;
}

void game_data::spawn_ball()
{
    ball.respawn(rnd(BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_RIGHT), rnd(BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_BOTTOM));
}

void game_data::new_game(bool two_players)
{
    reset();

    this->two_players = two_players;

    int num_players = two_players ? 2 : 1;

    active_player = 0;

    score[0] = 0;
    score[1] = 0;

    waiting_for_serve = true;

    for (int player = 0; player < num_players; player++)
    {
        current_serve[player] = 1;
        bricks_map(player, reset_brick);
    }
}

void game_data::handle_wall_collision()
{
    // check if moving towards wall so ball doesn't get infinitely stuck on the wall
    const bool left = ball.is_moving_left() && ball.get_left() <= 0;
    const bool right = ball.is_moving_right() && ball.get_right() >= SCREEN_WIDTH;

    // left and right walls
    if (left || right)
    {
        // out of bounds area below paddle
        if (ball.get_top() < paddle.get_bottom())
            ball.reflect_x();
    }

    // top wall
    if (ball.is_moving_up() && ball.get_top() <= DIVIDER_END)
    {
        ball.reflect_y();
        ball_phasing = false;
        if (!idle)
            paddle.set_shrunken(true);
    }
}

void game_data::handle_paddle_collision()
{
    paddle_section section = paddle.section_hit(ball);
    if (section)
    {
        increment_volley_counter();
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
}

void game_data::handle_brick_collision()
{
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
                        score_points(BRICK_POINTS[row / 2]);

                        // hit brick from top
                        if (ball.is_moving_down())
                            increment_volley_counter();

                        if (get_current_score() == MAX_POINTS_PER_SCREEN)
                            bricks_map(active_player, reset_brick);
                    }
                    ball.reflect_y();
                    ball_phasing = true;
                }
            }
        }
    }
}

void game_data::handle_ball_out_of_bounds()
{
    if (ball.get_top() > SCREEN_HEIGHT || ball.get_right() < 0 || ball.get_left() > SCREEN_WIDTH)
        end_round();
}

void game_data::handle_paddle_input()
{
    if (key_down(LEFT_KEY))
    {
        paddle.move_left();
    }
    if (key_down(RIGHT_KEY))
    {
        paddle.move_right();
    }
}

void game_data::handle_serve_start()
{
    if (key_released(SPACE_KEY))
        start_round();
}

void game_data::update()
{
    handle_wall_collision();
    if (ball.is_moving_down())
        handle_paddle_collision();
    handle_brick_collision();

    if (!waiting_for_serve && !idle)
        handle_ball_out_of_bounds();

    process_events();

    // handle ball move
    if (!waiting_for_serve)
    {
        ball.move_next_pos();
        set_ball_y_speed();
    }
    // handle player input
    else
        handle_serve_start();

    if (!idle)
        handle_paddle_input();
    else
        handle_mode_start();
}

void game_data::handle_mode_start()
{
    if (key_released(SPACE_KEY))
    {
        new_game(false);
        set_idle(false);
    }
}

void game_data::end_round()
{
    reset();

    current_serve[active_player]++;

    if (get_serve() > max_serves)
    {
        end_game();
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

void game_data::reset()
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