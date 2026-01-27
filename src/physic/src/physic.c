#include "physic.h"

void
physicMoveSprite(sprite_t *sprite, direction_t direction) {
    if(!sprite) {
        return;
    }

    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    float delta_time = (current_time.tv_sec - sprite->last_update.tv_sec) * 1000.0f +
                      (current_time.tv_usec - sprite->last_update.tv_usec) / 1000.0f;
    if(delta_time < sprite->time_to_move) {
        return;
    }

    switch(direction) {
        case RIGHT:
            if(sprite->x + sprite->pixels_to_move >= WINDOW_WIDTH - sprite->scaled_width) {
                sprite->x = WINDOW_WIDTH - sprite->scaled_width;
                return;
            }
            sprite->x += sprite->pixels_to_move;
            break;
        case LEFT:
            if(sprite->x - sprite->pixels_to_move < 0) {
                sprite->x = 0;
                return;
            }
            sprite->x -= sprite->pixels_to_move;
            break;
        case UP:
            if(sprite->y + sprite->pixels_to_move  >= WINDOW_HEIGHT - sprite->scaled_height) {
                sprite->y = WINDOW_HEIGHT - sprite->scaled_height;
                return;
            }
            sprite->y += sprite->pixels_to_move;
            break;
        default:
            break;
    }

    sprite->last_update = current_time;
}

bool
physicCheckCeillingCollision(const sprite_t * const sprite)
{
    if(!sprite)
        return false;

    if(sprite->y + sprite->scaled_height >= WINDOW_HEIGHT)
        return true;
    return false;
}

