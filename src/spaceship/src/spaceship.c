#include "spaceship.h"

struct spaceship_instance_t {
    sprite_t sprite;
};

static const char spaceshipImage[SPACESHIP_HEIGHT][SPACESHIP_WIDTH][4] = {
    {B, B, B, B, B, B, G, B, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

static void
createImage(sprite_t *sprite) {
    glGenTextures(1, &sprite->textureId);
    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

spaceship_t
spaceshipCreate(int x, int y){
    spaceship_t inst = utilsCalloc(1, sizeof(struct spaceship_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = SPACESHIP_WIDTH;
    inst->sprite.height = SPACESHIP_HEIGHT;
    inst->sprite.image = (char *)spaceshipImage;
    createImage(&inst->sprite);

    return inst;
}

sprite_t *
spaceshipGetSprite(const spaceship_t this) {
    if(!this) {
        return NULL;
    }
    return &this->sprite;
}

void
spaceshipPrint(void) {
//    glBindTexture(GL_TEXTURE_2D);
}
