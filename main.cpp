#include "splashkit.h"

#include "audio.h"
#include "constants.h"
#include "game-controller.hpp"
#include "view.hpp"

int main()
{
    game_controller game;
    unsigned long clock = 0;

    load_sounds();
    open_window("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!quit_requested())
    {
        game.update();
        draw_game(game, clock++ % 12 <= 4);

        refresh_screen(60);
    }

    return 0;
}