#include "splashkit.h"

#include "view.hpp"
#include "game.hpp"
#include "unit.hpp"
#include "draw-digit.hpp"
#include "debug.h"

void draw_player(const game_data &game, bool blink)
{
    if (game.is_idle() && blink)
        return;

    int player = game.num_players();
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
    const int digit_2 = (score % 100) / 10;
    const int digit_3 = score % 10;

    draw_digit((digit)digit_1, OTHER_COLOURS, x, y);
    x += DIGIT_WIDTH + DIGIT_SPACING;
    draw_digit((digit)digit_2, OTHER_COLOURS, x, y);
    x += DIGIT_WIDTH + DIGIT_SPACING;
    draw_digit((digit)digit_3, OTHER_COLOURS, x, y);
}

void draw_scores(const game_data &game, bool blink)
{
    const bool blinking = !game.is_idle() && blink;
    if (!(blinking && game.get_active_player() == 0))
        draw_score(game.get_score(0), SCORE_MARGIN_1, SCORE_LINE);
    if (!(blinking && game.get_active_player() == 1))
        draw_score(game.get_score(1), SCORE_MARGIN_2, SCORE_LINE);
}

void draw_unit(const unit &u, color colour)
{
    fill_rectangle(colour, u.get_x(), u.get_y(), u.get_width(), u.get_height());
}

void draw_ball(const game_data &game, color colour)
{
    if (!game.is_waiting_for_serve())
        draw_unit(game.get_ball(), colour);
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

void draw_game(const game_data &game, bool blink)
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
            draw_ball(game, colour);
            ball_rendered = true;
        }

        y_start += height;
    }

    // blue streak in walls
    draw_vertical_walls(PADDLE_COLOUR, BLUE_STREAK_START, BLUE_STREAK_END - BLUE_STREAK_START);

    // horizontal wall
    fill_rectangle(OTHER_COLOURS, WALL_WIDTH, DIVIDER_START, SCREEN_WIDTH - 2 * WALL_WIDTH, WALL_HEIGHT);

    draw_player(game, blink);
    draw_serve_count(game);
    draw_scores(game, blink);

    game.bricks_map(game.get_active_player(), draw_brick);
    draw_unit(game.get_paddle(), PADDLE_COLOUR);
    if (!ball_rendered)
    {
        const int ball_bot = game.get_ball().get_bottom();
        if (ball_bot >= BLUE_STREAK_START && ball_bot <= BLUE_STREAK_END)
            draw_ball(game, PADDLE_COLOUR);
        else
            draw_ball(game, OTHER_COLOURS);
    }

    if (DEBUG_SHOW_SPAWN_AREA)
    {
        // show ball spawn area
        draw_rectangle(COLOR_RED, BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_RIGHT - BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_BOTTOM - BALL_SPAWN_BOUNDS_TOP);
    }
}