#include "testSpaceship.h"
#include "spaceship.h"

void
testSpaceshipCreate(void **status) {
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);

    spaceship_t spaceship = spaceshipCreate(x_pos, y_pos);
    sprite_t *sprite = spaceshipGetSprite(spaceship);

    assert_int_equal(sprite->x, x_pos);
    assert_int_equal(sprite->y, y_pos);
    assert_int_equal(sprite->width, SPACESHIP_WIDTH);
    assert_int_equal(sprite->height, SPACESHIP_HEIGHT);
}

void
testSpaceshipGetSpriteFail(void **status) {
    (void)status;

    assert_null(spaceshipGetSprite(NULL));
}

void
testSpaceshipGetSpriteSuccess(void **status) {
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);

    spaceship_t spaceship = spaceshipCreate(x_pos, y_pos);

    assert_non_null(spaceshipGetSprite(spaceship));
}
