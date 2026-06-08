#include "splashkit.h"

#include "view.hpp"
#include "game.hpp"
#include "unit.hpp"
#include "draw-digit.hpp"

void draw_player(const game_data &game)
{
    int player = game.get_active_player() + 1;
    draw_digit((digit)player, OTHER_COLOURS, PLAYER_MARGIN, PLAYER_LINE);
}

void draw_serve_count(const game_data &game)
{
    int serve = game.get_serve() % 10;
    draw_digit((digit)serve, OTHER_COLOURS, SERVE_MARGIN, PLAYER_LINE);
}

void draw_score(int score, int x, int y)
{
    const int digit_1 = score / 100;
    const int digit_2 = score % 100;
    const int digit_3 = score % 10;

    draw_digit((digit)digit_1, OTHER_COLOURS, x, y);
    x += DIGIT_WIDTH + DIGIT_SPACING;
    draw_digit((digit)digit_2, OTHER_COLOURS, x, y);
    x += DIGIT_WIDTH + DIGIT_SPACING;
    draw_digit((digit)digit_3, OTHER_COLOURS, x, y);
}

void draw_scores(const game_data &game)
{
    draw_score(game.get_score(0), SCORE_MARGIN_1, SCORE_LINE);
    draw_score(game.get_score(1), SCORE_MARGIN_2, SCORE_LINE);
}

void draw_unit(const unit &u, color colour)
{
    fill_rectangle(colour, u.get_x(), u.get_y(), u.get_width(), u.get_height());
}

void draw_brick(const brick_data &brick, int row, int col)
{
    if (!brick.is_broken())
    {
        draw_unit(brick, BRICK_COLOURS[row / ROWS_PER_GROUP]);
    }
}

void draw_vertical_walls(color colour, int y, int height)
{
    fill_rectangle(colour, 0, y, WALL_WIDTH, height);
    fill_rectangle(colour, SCREEN_WIDTH - WALL_WIDTH, y, WALL_WIDTH, height);
}

void draw_game(const game_data &game)
{
    clear_screen(BACKGROUND_COLOUR);

    // base walls
    draw_vertical_walls(OTHER_COLOURS, 0, SCREEN_HEIGHT);

    // brick colours
    int y_start = BRICK_AREA_Y_START - BRICK_GAP_Y / 2;
    int height = 2 * (BRICK_HEIGHT + BRICK_GAP_Y);

    bool ball_rendered = false;

    for (int group = 0; group < NUM_BRICK_GROUPS; group++)
    {
        const color colour = BRICK_COLOURS[group];
        draw_vertical_walls(colour, y_start, height);

        const int ball_y = game.get_ball().get_y();

        // colour the ball if in brick area
        if (!ball_rendered && ball_y >= y_start && ball_y < y_start + height)
        {
            draw_unit(game.get_ball(), colour);
            ball_rendered = true;
        }

        y_start += height;
    }

    // blue streak in walls
    draw_vertical_walls(PADDLE_COLOUR, WALL_BOUNDS_END, 3 * PADDLE_HEIGHT - 2 * BRICK_GAP_Y);

    // horizontal wall
    fill_rectangle(OTHER_COLOURS, WALL_WIDTH, DIVIDER_START, SCREEN_WIDTH - 2 * WALL_WIDTH, WALL_HEIGHT);

    draw_player(game);
    draw_serve_count(game);
    draw_scores(game);

    game.bricks_map(game.get_active_player(), draw_brick);
    draw_unit(game.get_paddle(), PADDLE_COLOUR);
    if (!ball_rendered)
        draw_unit(game.get_ball(), OTHER_COLOURS);
}