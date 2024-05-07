#include "testSpaceship.h"
#include "spaceship.h"

void
__wrap_glGenTextures(GLsizei n, GLuint *textures){
    (void)n, (void)textures;
    function_called();
}

void
__wrap_glBindTexture(GLenum target, GLuint texture) {
    (void)target, (void)texture;
    function_called();
}

void
__wrap_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
                    GLint border, GLenum format, GLenum type, const void * data) {
    (void)target, (void)level, (void)internalformat, (void)width, (void)height, (void)border,
    (void)format, (void)type, (void)data;
    function_called();
}

void
__wrap_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    (void)target, (void)pname, (void)param;
    function_called();
}

void
testSpaceshipCreate(void **status) {
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_glGenTextures);
    expect_function_call(__wrap_glBindTexture);
    expect_function_call(__wrap_glTexImage2D);
    expect_function_call(__wrap_glTexParameteri);
    expect_function_call(__wrap_glTexParameteri);

    spaceship_t spaceship = spaceshipCreate(10, 10);
    sprite_t *sprite = spaceshipGetSprite(spaceship);

    assert_int_equal(sprite->x, 10);
    assert_int_equal(sprite->y, 10);
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

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_glGenTextures);
    expect_function_call(__wrap_glBindTexture);
    expect_function_call(__wrap_glTexImage2D);
    expect_function_call(__wrap_glTexParameteri);
    expect_function_call(__wrap_glTexParameteri);

    spaceship_t spaceship = spaceshipCreate(10, 10);

    assert_non_null(spaceshipGetSprite(spaceship));
}

void
testSpaceshipPrintFail(void **status) {
    (void)status;

//    expect_function_call(__wrap_glBindTexture);

    spaceshipPrint();
}
