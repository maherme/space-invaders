#include "bullet.h"

struct bullet_instance_t {
    sprite_t sprite;
};

static const char bulletImage[BULLET_HEIGHT][BULLET_WIDTH][4] = {
    {W},
    {W},
    {W},
    {W}
};

bullet_t
bulletCreate(int x, int y){
    bullet_t inst = utilsCalloc(1, sizeof(struct bullet_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = BULLET_WIDTH;
    inst->sprite.height = BULLET_HEIGHT;
    inst->sprite.image = (const char *)bulletImage;
    inst->sprite.pixels_to_move = 1;
    inst->sprite.time_to_move = 2;
    graphCreateImage(&inst->sprite);

    return inst;
}
