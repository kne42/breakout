#ifndef VIEW_HPP
#define VIEW_HPP

#include <array>

#include "splashkit.h"

#include "draw-digit.hpp"
#include "game.hpp"

const std::array<color, 4> BRICK_COLOURS = {rgb_color(160, 0, 0), rgb_color(200, 130, 0), rgb_color(0, 130, 42), rgb_color(200, 200, 30)};

const color PADDLE_COLOUR = rgb_color(0, 130, 200);
const color BACKGROUND_COLOUR = COLOR_BLACK;
const color OTHER_COLOURS = rgba_color(255, 255, 255, 210);

const int MARGIN = 2;
const int DIGIT_SPACING = 7;

const int PLAYER_LINE = DIVIDER_END + MARGIN;
const int PLAYER_MARGIN = WALL_WIDTH + MARGIN;

const int SERVE_MARGIN = SCREEN_WIDTH - 145 - DIGIT_WIDTH;

const int SCORE_LINE = PLAYER_LINE + DIGIT_HEIGHT + DIGIT_SPACING;
const int SCORE_MARGIN_1 = PLAYER_MARGIN + DIGIT_WIDTH + DIGIT_SPACING;
const int SCORE_MARGIN_2 = SERVE_MARGIN + DIGIT_WIDTH + DIGIT_SPACING;

void draw_game(const game_data &game);

#endif