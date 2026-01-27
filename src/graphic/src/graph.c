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

sprite_t *
graphGetSprite(base_t *b) {
    if(!b) {
        return NULL;
    }
    return &b->sprite;
}

void
graphPrintImage(const sprite_t * const sprite) {
    if(!sprite) {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(sprite->x, sprite->y);
    glTexCoord2f(1.0, 1.0); glVertex2i(sprite->x + sprite->scaled_width, sprite->y);
    glTexCoord2f(1.0, 0.0); glVertex2i(sprite->x + sprite->scaled_width, sprite->y + sprite->scaled_height);
    glTexCoord2f(0.0, 0.0); glVertex2i(sprite->x, sprite->y + sprite->scaled_height);
    glEnd();
}

void
graphDestroyObject(base_t **b) {
   if(!b || !*b)
        return;

    glDeleteTextures(1, &((*b)->sprite.textureId));
    utilsFree((void**)b);
}
