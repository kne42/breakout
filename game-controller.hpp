#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "game.hpp"

class game_controller : public game_data
{
    void handle_wall_collision();
    void handle_paddle_collision();
    void handle_brick_collision();
    void handle_ball_out_of_bounds();

    void handle_serve_start();
    void handle_paddle_input();
    void handle_mode_start();

public:
    void update();
};

#endif