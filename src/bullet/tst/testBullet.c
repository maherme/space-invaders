#include "testBullet.h"
#include "bullet.h"

void
testBulletCreate(void **status) {
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);

    bullet_t bullet = bulletCreate(x_pos, y_pos);
    sprite_t *sprite = graphGetSprite((base_t *)bullet);

    assert_int_equal(sprite->x, x_pos);
    assert_int_equal(sprite->y, y_pos);
}
 
