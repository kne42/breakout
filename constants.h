#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "splashkit.h"

enum speed_thresholds
{
    DIFFICULTY_NONE = 3,
    DIFFICULTY_FOUR_HITS = 6,
    DIFFICULTY_TWELVE_HITS = 12,
    DIFFICULTY_ORANGE_ROW = 16,
    DIFFICULTY_RED_ROW = 32,
};

const int NUM_BRICK_COLS = 14;
const int NUM_BRICK_ROWS = 8;

const int BRICK_GAP_X = 4;
const int BRICK_GAP_Y = 3;
const int BRICK_WIDTH = 24;
const int BRICK_HEIGHT = 6;

const int BRICK_AREA_WIDTH = NUM_BRICK_COLS * BRICK_WIDTH + (NUM_BRICK_COLS - 1) * BRICK_GAP_X;
const int BRICK_AREA_HEIGHT = NUM_BRICK_ROWS * BRICK_HEIGHT + (NUM_BRICK_ROWS - 1) * BRICK_GAP_Y;
const int BRICK_AREA_Y_START = 150;
const int BRICK_AREA_Y_END = BRICK_AREA_Y_START + BRICK_AREA_HEIGHT;

const int SCREEN_WIDTH = BRICK_AREA_WIDTH;
const int SCREEN_HEIGHT = SCREEN_WIDTH * 1.45;

const int NUM_BRICK_GROUPS = 4;
const int ROWS_PER_GROUP = 2;

// brick groups in order of: red, orange, green, yellow
const std::array<int, 4> BRICK_POINTS = {7, 5, 3, 1};
const std::array<color, 4> BRICK_COLOURS = {rgb_color(160, 0, 0), rgb_color(200, 130, 0), rgb_color(0, 130, 42), rgb_color(200, 200, 30)};

const int PADDLE_SPEED = 10;
const int PADDLE_HEIGHT = 8;
const int PADDLE_WIDTH = BRICK_WIDTH;
const int PADDLE_Y = SCREEN_HEIGHT - 70;
const int PADDLE_STARTING_X = SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2;

const int BALL_SIZE = 5;
const int BALL_SPAWN_OFFSET = 50;

const int BALL_SPAWN_BOUNDS_LEFT = BALL_SPAWN_OFFSET;
const int BALL_SPAWN_BOUNDS_RIGHT = SCREEN_WIDTH - BALL_SPAWN_OFFSET;
const int BALL_SPAWN_BOUNDS_TOP = BRICK_AREA_Y_END + BALL_SPAWN_OFFSET;
const int BALL_SPAWN_BOUNDS_BOTTOM = PADDLE_Y - BALL_SPAWN_OFFSET;

const int BALL_STARTING_ANGLE_MIN = 210;
const int BALL_STARTING_ANGLE_MAX = 330;

const color PADDLE_COLOUR = rgb_color(0, 130, 200);
const color BACKGROUND_COLOUR = COLOR_BLACK;
const color OTHER_COLOURS = rgba_color(255, 255, 255, 210);

const int WALL_THICKNESS = 5;

const int STARTING_LIVES = 3;

#endif