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

void game_data::init_brick(brick_data &brick, int row, int col)
{
    brick = brick_data(row, col);
}

game_data::game_data() : game_data(false) {}

game_data::game_data(bool two_players)
{
    new_game(two_players);
}

void game_data::new_game(bool two_players)
{
    this->two_players = two_players;
    active_player = 0;

    int num_players = two_players ? 2 : 1;

    ball = ball_data(rnd(BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_RIGHT), rnd(BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_BOTTOM), DIFFICULTY_NONE, rnd(BALL_STARTING_ANGLE_MIN, BALL_STARTING_ANGLE_MAX));
    paddle.reset();

    for (int player = 0; player < num_players; player++)
    {
        score[player] = 0;
        level_two[player] = false;
        lives[player] = STARTING_LIVES;

        bricks_map(player, init_brick);
    }
}

void game_data::update()
{
}

int game_data::lose_life()
{
    reset_difficulty();
    return --lives[active_player];
}

void game_data::reset_difficulty()
{
}

// GUI

void game_data::draw_brick(const brick_data &brick, int row, int col)
{
    brick.draw(BRICK_COLOURS[row / ROWS_PER_GROUP]);
}

void game_data::draw_walls(color colour, int y, int height) const
{
    fill_rectangle(colour, 0, y, WALL_THICKNESS, height);
    fill_rectangle(colour, SCREEN_WIDTH - WALL_THICKNESS, y, WALL_THICKNESS, height);
}

void game_data::draw() const
{
    clear_screen(BACKGROUND_COLOUR);

    // base walls
    draw_walls(OTHER_COLOURS, 0, SCREEN_HEIGHT);

    // brick colours
    int y_start = BRICK_AREA_Y_START - BRICK_GAP_Y / 2;
    int height = 2 * (BRICK_HEIGHT + BRICK_GAP_Y);

    for (int group = 0; group < NUM_BRICK_GROUPS; group++)
    {
        draw_walls(BRICK_COLOURS[group], y_start, height);
        y_start += height;
    }

    // blue streak in walls
    draw_walls(PADDLE_COLOUR, PADDLE_Y - PADDLE_HEIGHT + BRICK_GAP_Y, 3 * PADDLE_HEIGHT - 2 * BRICK_GAP_Y);

    bricks_map(active_player, draw_brick);
    paddle.draw(PADDLE_COLOUR);
    ball.draw(OTHER_COLOURS);
}