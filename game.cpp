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

    ball = ball_data(rnd(50, SCREEN_WIDTH - 50), rnd(BRICK_AREA_Y_END, PADDLE_Y - 50), DIFFICULTY_NONE, rnd(210, 330));
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