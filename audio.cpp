#include "splashkit.h"

#include "audio.h"

void load_sounds()
{
    load_sound_effect("paddle", "sounds/paddle.wav");
    load_sound_effect("wall", "sounds/wall.wav");
    load_sound_effect("paddle", "sounds/paddle.wav");
    load_sound_effect("brick-yellow", "sounds/brick_1pt.wav");
    load_sound_effect("brick-green", "sounds/brick_3pt.wav");
    load_sound_effect("brick-orange", "sounds/brick_5pt.wav");
    load_sound_effect("brick-red", "sounds/brick_7pt.wav");
}

void play_brick_hit(brick_points points)
{
    switch (points)
    {
    case POINTS_RED:
        play_sound_effect("brick-red");
        break;

    case POINTS_ORANGE:
        play_sound_effect("brick-orange");
        break;

    case POINTS_GREEN:
        play_sound_effect("brick-green");
        break;

    case POINTS_YELLOW:
        play_sound_effect("brick-yellow");
        break;
    }
}

void play_paddle_hit()
{
    play_sound_effect("paddle");
}

void play_wall_hit()
{
    play_sound_effect("wall");
}