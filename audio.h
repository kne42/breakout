#ifndef BREAKOUT_AUDIO_H
#define BREAKOUT_AUDIO_H

#include "constants.h"

void load_sounds();
void play_brick_hit(brick_points points);
void play_paddle_hit();
void play_wall_hit();

#endif