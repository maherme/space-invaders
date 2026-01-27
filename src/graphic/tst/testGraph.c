#include "testGraph.h"
#include <stdio.h>

void
__wrap_glGenTextures(GLsizei n, GLuint *textures){
    (void)textures;
    check_expected_int(n);
    function_called();
}

void
__wrap_glBindTexture(GLenum target, GLuint texture) {
    (void)texture;
    check_expected_uint(target);
    function_called();
}

void
__wrap_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
                    GLint border, GLenum format, GLenum type, const void *data) {
    check_expected_uint(target);
    check_expected_int(level);
    check_expected_int(internalformat);
    check_expected_int(width);
    check_expected_int(height);
    check_expected_int(border);
    check_expected_uint(format);
    check_expected_uint(type);
    check_expected_ptr(data);
    function_called();
}

void
__wrap_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    check_expected_uint(target);
    check_expected_uint(pname);
    check_expected_int(param);
    function_called();
}

void
__wrap_glBegin(GLenum mode) {
    check_expected_uint(mode);
    function_called();
}

void
__wrap_glTexCoord2f(GLfloat s, GLfloat t) {
    check_expected_float(s);
    check_expected_float(t);
    function_called();
}

void
__wrap_glVertex2i(GLint x, GLint y) {
    check_expected_int(x);
    check_expected_int(y);
    function_called();
}

void
__wrap_glEnd(void) {
    function_called();
}

void
__wrap_glDeleteTextures(GLsizei n, const GLuint *textures) {
    check_expected_int(n);
    check_expected_ptr(textures);
    function_called();
}

void
__wrap_utilsFree(void **ptr) {
    check_expected_ptr(ptr);
    function_called();
    free(*ptr);
}

void
testGraphCreateImageFail(void **status) {
    (void)status;

    graphCreateImage(NULL);
}

void
testGraphCreateImageSuccess(void **status) {
    (void)status;
    sprite_t sprite = {0};

    expect_int_value(__wrap_glGenTextures, n, 1);
    expect_function_call(__wrap_glGenTextures);

    expect_uint_value(__wrap_glBindTexture, target, GL_TEXTURE_2D);
    expect_function_call(__wrap_glBindTexture);

    expect_uint_value(__wrap_glTexImage2D, target, GL_TEXTURE_2D);
    expect_int_value(__wrap_glTexImage2D, level, 0);
    expect_int_value(__wrap_glTexImage2D, internalformat, GL_RGBA);
    expect_int_value(__wrap_glTexImage2D, width, sprite.width);
    expect_int_value(__wrap_glTexImage2D, height, sprite.height);
    expect_int_value(__wrap_glTexImage2D, border, 0);
    expect_uint_value(__wrap_glTexImage2D, format, GL_RGBA);
    expect_uint_value(__wrap_glTexImage2D, type, GL_UNSIGNED_BYTE);
    expect_uint_value(__wrap_glTexImage2D, data, (uintptr_t)sprite.image);
    expect_function_call(__wrap_glTexImage2D);

    expect_uint_value(__wrap_glTexParameteri, target, GL_TEXTURE_2D);
    expect_uint_value(__wrap_glTexParameteri, pname, GL_TEXTURE_MIN_FILTER);
    expect_int_value(__wrap_glTexParameteri, param, GL_NEAREST);
    expect_function_call(__wrap_glTexParameteri);

    expect_uint_value(__wrap_glTexParameteri, target, GL_TEXTURE_2D);
    expect_uint_value(__wrap_glTexParameteri, pname, GL_TEXTURE_MAG_FILTER);
    expect_int_value(__wrap_glTexParameteri, param, GL_NEAREST);
    expect_function_call(__wrap_glTexParameteri);

    graphCreateImage(&sprite);
} 

void
testGraphGetSpriteFail(void **status) {
    (void)status;

    assert_null(graphGetSprite(NULL));
}

void
testGraphGetSpriteSuccess(void **status) {
    (void)status;
    base_t base = {0};
    sprite_t *sprite = graphGetSprite(&base);

    assert_ptr_equal((void *)&base.sprite, (void *)sprite);
}

void
testGraphPrintImageFail(void **status) {
    (void)status;

    graphPrintImage(NULL);
}

void
testGraphPrintImageSuccess(void **status) {
    (void)status;
    sprite_t sprite = {
        .width = 10,
        .height = 20,
    };

    expect_uint_value(__wrap_glBindTexture, target, GL_TEXTURE_2D);
    expect_function_call(__wrap_glBindTexture);

    expect_uint_value(__wrap_glTexImage2D, target, GL_TEXTURE_2D);
    expect_int_value(__wrap_glTexImage2D, level, 0);
    expect_int_value(__wrap_glTexImage2D, internalformat, GL_RGBA);
    expect_int_value(__wrap_glTexImage2D, width, sprite.width);
    expect_int_value(__wrap_glTexImage2D, height, sprite.height);
    expect_int_value(__wrap_glTexImage2D, border, 0);
    expect_uint_value(__wrap_glTexImage2D, format, GL_RGBA);
    expect_uint_value(__wrap_glTexImage2D, type, GL_UNSIGNED_BYTE);
    expect_uint_value(__wrap_glTexImage2D, data, (uintptr_t)sprite.image);
    expect_function_call(__wrap_glTexImage2D);

    expect_uint_value(__wrap_glBegin, mode, GL_QUADS);
    expect_function_call(__wrap_glBegin);

    expect_float(__wrap_glTexCoord2f, s, 0.0, 0);
    expect_float(__wrap_glTexCoord2f, t, 1.0, 0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_int_value(__wrap_glVertex2i, x, sprite.x);
    expect_int_value(__wrap_glVertex2i, y, sprite.y);
    expect_function_call(__wrap_glVertex2i);

    expect_float(__wrap_glTexCoord2f, s, 1.0, 0);
    expect_float(__wrap_glTexCoord2f, t, 1.0, 0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_int_value(__wrap_glVertex2i, x, sprite.x + sprite.scale * sprite.width);
    expect_int_value(__wrap_glVertex2i, y, sprite.y);
    expect_function_call(__wrap_glVertex2i);

    expect_float(__wrap_glTexCoord2f, s, 1.0, 0);
    expect_float(__wrap_glTexCoord2f, t, 0.0, 0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_int_value(__wrap_glVertex2i, x, sprite.x + sprite.scale * sprite.width);
    expect_int_value(__wrap_glVertex2i, y, sprite.y + sprite.scale * sprite.height);
    expect_function_call(__wrap_glVertex2i);

    expect_float(__wrap_glTexCoord2f, s, 0.0, 0);
    expect_float(__wrap_glTexCoord2f, t, 0.0, 0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_int_value(__wrap_glVertex2i, x, sprite.x);
    expect_int_value(__wrap_glVertex2i, y, sprite.y + sprite.scale * sprite.height);
    expect_function_call(__wrap_glVertex2i);

    expect_function_call(__wrap_glEnd);

    graphPrintImage(&sprite);
}

void
testGraphDestroyObjectNullParameter(void **status) {
    (void)status;
    base_t *ptr = NULL;

    graphDestroyObject(NULL);
    graphDestroyObject(&ptr);
}

void
testGraphDestroyObjectSuccess(void **status) {
    (void)status;
    base_t *object = calloc(1, sizeof(base_t));;

    expect_int_value(__wrap_glDeleteTextures, n, 1);
    expect_uint_value(__wrap_glDeleteTextures, textures, (uintptr_t)&(object->sprite.textureId));
    expect_function_call(__wrap_glDeleteTextures);

    expect_uint_value(__wrap_utilsFree, ptr, (uintptr_t)&object);
    expect_function_call(__wrap_utilsFree);

    graphDestroyObject(&object);
}
