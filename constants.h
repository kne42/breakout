#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "splashkit.h"

enum speed_thresholds
{
    NONE = 3,
    FOUR_HITS = 6,
    TWELVE_HITS = 12,
    ORANGE_ROW = 16,
    RED_ROW = 32,
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1100;

const int BRICK_AREA_WIDTH = SCREEN_WIDTH;
const int BRICK_AREA_HEIGHT = 600;

const int NUM_BRICK_COLS = 14;
const int NUM_BRICK_ROWS = 8;

const int BRICK_OFFSET = 0;
const int BRICK_GAP = 10;
const int BRICK_WIDTH = (BRICK_AREA_WIDTH - ((NUM_BRICK_COLS - 1) * BRICK_GAP)) * NUM_BRICK_COLS;
const int BRICK_HEIGHT = (BRICK_AREA_HEIGHT - ((NUM_BRICK_ROWS - 1) * BRICK_GAP)) * NUM_BRICK_ROWS;

// bricks in order of: red, orange, green, yellow
constexpr std::array<int, 4> BRICK_POINTS = {7, 5, 3, 1};
constexpr std::array<color, 4> BRICK_COLOURS = {color(160 / 255, 0, 0), color(200 / 255, 130 / 255, 0), color(0, 130 / 255, 42 / 255), color(200 / 255, 200 / 255, 30 / 255)};

const int BALL_SIZE = 30;

const int PADDLE_SPEED = 10;
const int PADDLE_HEIGHT = 100;
const int PADDLE_WIDTH = BRICK_WIDTH;
const int PADDLE_Y = SCREEN_HEIGHT - 300;
const int PADDLE_STARTING_X = SCREEN_WIDTH / 2;

const color PADDLE_COLOUR = color(0, 130 / 255, 200 / 255);
const color BACKGROUND_COLOUR = COLOR_BLACK;
const color OTHER_COLOURS = color(0, 0, 0, 210 / 255);

#endif