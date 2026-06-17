#include <algorithm>

#include "splashkit.h"

#include "audio.h"
#include "constants.h"
#include "debug.h"
#include "game-controller.hpp"

/**
 * Helpers
 */

int calc_brick_row(int y)
{
    return (y - BRICK_AREA_Y_START) / (BRICK_HEIGHT + BRICK_GAP_Y);
}

int calc_brick_col(int x)
{
    return x / (BRICK_WIDTH + BRICK_GAP_X);
}

/**
 * Collision
 */

void game_controller::handle_wall_collision()
{
    // check if moving towards wall so ball doesn't get infinitely stuck on the wall
    const bool left = ball.is_moving_left() && ball.get_left() <= 0;
    const bool right = ball.is_moving_right() && ball.get_right() >= SCREEN_WIDTH;

    // left and right walls
    if (left || right)
    {
        // do not reflect if in out of bounds area
        if (DEBUG_NO_OUT_OF_BOUNDS || ball.get_top() < WALL_BOUNDS_END)
        {
            ball.reflect_x();
            if (!idle)
                play_wall_hit();
        }
    }

    // top wall
    if (ball.is_moving_up() && ball.get_top() <= DIVIDER_END)
    {
        ball.reflect_y();
        ball_phasing = false;
        if (!idle)
        {
            play_wall_hit();
            paddle.set_shrunken(true);
            max_speed = true;
        }
    }

    // bottom wall
    if (DEBUG_NO_OUT_OF_BOUNDS && ball.get_bottom() >= SCREEN_HEIGHT)
    {
        ball.reflect_y();
        ball_phasing = false;
    }
}

void game_controller::handle_paddle_collision()
{
    paddle_section section = paddle.section_hit(ball);
    if (section)
    {
        increment_volley_counter();
        ball.reflect_y();
        ball_phasing = false;

        if (!idle)
        {
            play_paddle_hit();

            if (!x_slow)
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

void game_controller::handle_brick_collision()
{
    if (!ball_phasing)
    {
        const int row_bottom = calc_brick_row(ball.get_bottom());
        const int row_top = calc_brick_row(ball.get_top());

        const int col_left = calc_brick_col(ball.get_left());
        const int col_right = calc_brick_col(ball.get_right());

        int min_row = std::max(0, std::min(row_top, row_bottom));
        int max_row = std::min(NUM_BRICK_ROWS - 1, std::max(row_top, row_bottom));

        int min_col = std::max(0, std::min(col_left, col_right));
        int max_col = std::min(NUM_BRICK_COLS - 1, std::max(col_left, col_right));

        if (min_row > max_row || min_col > max_col)
            return;

        // only perform check in possible brick overlap areas
        for (int row = max_row; row >= min_row; row--)
        {
            for (int col = max_col; col >= min_col; col--)
            {
                brick_data &brick = bricks[active_player][row][col];
                if (!brick.is_broken() && brick.check_collision(ball))
                {
                    if (!idle && !waiting_for_serve)
                    {
                        brick.set_broken(true);
                        brick_points points = BRICK_POINTS[row / 2];
                        score_points(points);
                        play_brick_hit(points);

                        // hit brick from top
                        if (ball.is_moving_down())
                            increment_volley_counter();

                        if (get_current_score() == MAX_POINTS_PER_SCREEN)
                        {
                            reset_bricks(active_player);
                            waiting_for_serve = true;
                        }
                    }
                    ball.reflect_y();
                    ball_phasing = true;
                    return;
                }
            }
        }
    }
}

void game_controller::handle_ball_out_of_bounds()
{
    if (ball.get_top() > SCREEN_HEIGHT || ball.get_right() < 0 || ball.get_left() > SCREEN_WIDTH)
        end_round();
}

/**
 * Player input
 */

void game_controller::handle_paddle_input()
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

void game_controller::handle_serve_start()
{
    if (key_released(SPACE_KEY))
        start_round();
}

void game_controller::handle_mode_start()
{
    if (key_released(SPACE_KEY))
    {
        new_game();
        set_idle(false);
        paddle.move_center();
    }
    if (key_down(LEFT_KEY))
        two_players = false;
    else if (key_down(RIGHT_KEY))
        two_players = true;
}

/**
 * Game loop
 */

void game_controller::update()
{
    process_events();

    // handle paddle movement
    if (!idle)
        handle_paddle_input();

    // check for collisions
    handle_wall_collision();
    if (ball.is_moving_down())
        handle_paddle_collision();
    handle_brick_collision();

    if (!waiting_for_serve && !idle)
        handle_ball_out_of_bounds();

    // handle serve
    if (waiting_for_serve)
        handle_serve_start();
    else
    {
        // handle ball move
        ball.move_next_pos();
        set_ball_y_speed();
    }

    // handle mode
    if (idle)
        handle_mode_start();
}