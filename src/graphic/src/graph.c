#include "graph.h"

#define SCALE_IMAGE     2

void
graphCreateImage(sprite_t *sprite) {
    if(!sprite) {
        return;
    }

    sprite->scale = SCALE_IMAGE;
    sprite->scaled_height = sprite->height * SCALE_IMAGE;
    sprite->scaled_width = sprite->width * SCALE_IMAGE;
    sprite->pixels_to_move = sprite->pixels_to_move * SCALE_IMAGE;

    glGenTextures(1, &sprite->textureId);
    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void
graphPrintImage(const sprite_t * const sprite) {
    if(!sprite) {
        return;
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(sprite->x, sprite->y);
    glTexCoord2f(1.0, 1.0); glVertex2i(sprite->x + sprite->scaled_width, sprite->y);
    glTexCoord2f(1.0, 0.0); glVertex2i(sprite->x + sprite->scaled_width, sprite->y + sprite->scaled_height);
    glTexCoord2f(0.0, 0.0); glVertex2i(sprite->x, sprite->y + sprite->scaled_height);
    glEnd();
}

void
graphMoveImage(sprite_t *sprite, direction_t direction) {
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
        default:
            break;
    }

    sprite->last_update = current_time;
}
