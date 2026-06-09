#include "splashkit.h"

#include "constants.h"
#include "game.hpp"
#include "view.hpp"

const bool DEBUG_MODE = false;

int main()
{
    game_data game;
    unsigned long clock = 0;

    open_window("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!quit_requested())
    {
        game.update();
        draw_game(game, clock++ % 12 <= 4);

        if (DEBUG_MODE)
        {
            // show ball spawn area
            draw_rectangle(COLOR_RED, BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_RIGHT - BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_BOTTOM - BALL_SPAWN_BOUNDS_TOP);
        }

        refresh_screen(60);
    }

    return 0;
}