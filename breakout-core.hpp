#ifndef BREAKOUT_CORE_HPP
#define BREAKOUT_CORE_HPP

#include "splashkit.h"

// TODO: separate classes and consts into different header files

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

const int BALL_SIZE = 30;

const int PADDLE_SPEED = 10;
const int PADDLE_HEIGHT = 100;
const int PADDLE_WIDTH = 300;
const int PADDLE_Y = SCREEN_HEIGHT - 300;
const int PADDLE_STARTING_X = SCREEN_WIDTH / 2;

enum edge
{
    EDGE_LEFT = 0b1000,
    EDGE_RIGHT = 0b0100,
    EDGE_TOP = 0b0010,
    EDGE_BOTTOM = 0b0001,
    EDGE_TOP_LEFT = EDGE_TOP | EDGE_LEFT,
    EDGE_TOP_RIGHT = EDGE_TOP | EDGE_RIGHT,
    EDGE_BOTTOM_LEFT = EDGE_BOTTOM | EDGE_LEFT,
    EDGE_BOTTOM_RIGHT = EDGE_BOTTOM | EDGE_RIGHT,
};

struct coordinates
{
    double x;
    double y;
};

class unit
{
    coordinates pos;
    int width;
    int height;

protected:
    void set_pos(const coordinates &pos);
    void set_x(const double &x);
    void set_y(const double &y);
    void set_width(const int &width);
    void set_height(const int &height);

public:
    int get_width() const;
    int get_height() const;
    coordinates get_pos() const;
    double get_x() const;
    double get_y() const;
    coordinates calculate_edge(edge edges) const;
    void draw(color colour) const;
};

class brick_data : unit
{
    bool broken;
    int row;
    int col;

public:
    brick_data(int row, int col);

    bool is_broken() const;
    void draw(color colour) const;
    void reset();
};

class ball_data : unit
{
    coordinates velocity;
    float velocity_multiplier;
    bool phasing;

public:
    ball_data(int x, int y, int speed, int direction);
};

class paddle_data : unit
{
    int speed;
    bool shrunken;

public:
    paddle_data();
    int get_width();
    void reset();
};

class game_data
{
    bool coop_mode;
    bool level_two;
    brick_data bricks[NUM_BRICK_ROWS][NUM_BRICK_COLS];
    ball_data ball;
    paddle_data paddle_p1;
    paddle_data paddle_p2;
    int score;
    unsigned short lives;

public:
    game_data();
    bool is_coop_mode();
    void new_game(bool coop_mode);
    void update();
    void draw();
};

#endif