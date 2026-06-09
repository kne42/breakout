#include "splashkit.h"

#include "constants.h"
#include "game.hpp"
#include "view.hpp"

int main()
{
    game_data game;
    unsigned long clock = 0;

    open_window("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!quit_requested())
    {
        game.update();
        draw_game(game, clock++ % 12 <= 4);

        refresh_screen(60);
    }

    return 0;
}