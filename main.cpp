#include "splashkit.h"

#include "constants.h"
#include "game.hpp"

const bool DEBUG = false;

int main()
{
    game_data game;

    open_window("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!quit_requested())
    {
        game.update();
        game.draw();

        if (DEBUG)
        {
            // show ball spawn area
            draw_rectangle(COLOR_RED, BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_TOP, BALL_SPAWN_BOUNDS_RIGHT - BALL_SPAWN_BOUNDS_LEFT, BALL_SPAWN_BOUNDS_BOTTOM - BALL_SPAWN_BOUNDS_TOP);
        }

        refresh_screen(30);
        delay(5000);
    }

    return 0;
}