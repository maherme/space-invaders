#include "graph.h"

#define SCALE_IMAGE     2

void
graphCreateImage(sprite_t *sprite) {
    if(!sprite) {
        return;
    }

    sprite->scale = SCALE_IMAGE;

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

    int dx = sprite->scale * sprite->width;
    int dy = sprite->scale * sprite->height;

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(sprite->x, sprite->y);
    glTexCoord2f(1.0, 1.0); glVertex2i(sprite->x + dx, sprite->y);
    glTexCoord2f(1.0, 0.0); glVertex2i(sprite->x + dx, sprite->y + dy);
    glTexCoord2f(0.0, 0.0); glVertex2i(sprite->x, sprite->y + dy);
    glEnd();
}
