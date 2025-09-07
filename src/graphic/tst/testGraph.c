#include "testGraph.h"

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
                    GLint border, GLenum format, GLenum type, const void * data) {
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

int
__wrap_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz) {
    if(tv) {
        tv->tv_sec = mock_type(time_t);
        tv->tv_usec = mock_type(suseconds_t);
    }
    check_expected_ptr(tz);
    function_called();
    return 0;
}

void
testGraphCreateImageFail(void ** status) {
    (void)status;

    graphCreateImage(NULL);
}

void
testGraphCreateImageSuccess(void ** status) {
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
testGraphPrintImageFail(void ** status) {
    (void)status;

    graphPrintImage(NULL);
}

void
testGraphPrintImageSuccess(void ** status) {
    (void)status;
    sprite_t sprite = {
        .width = 10,
        .height = 20,
    };

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
testGraphMoveImageFail(void ** status) {
    (void)status;

    graphMoveImage(NULL, RIGHT);
}

void
testGraphMoveImageWrongDirection(void ** status) {
    (void)status;
    sprite_t sprite = {
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
    };

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, 0xFF);
}

void
testGraphMoveImageRight(void ** status) {
    (void)status;
    sprite_t sprite = {
        .x = 100,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, RIGHT);
    assert_int_equal(sprite.x, old_sprite.x + sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testGraphMoveImageRightMax(void ** status) {
    (void)status;
    sprite_t sprite = {
        .x = 432,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, RIGHT);
    assert_int_equal(sprite.x, WINDOW_WIDTH - sprite.scaled_width);
}

void
testGraphMoveImageLeft(void ** status) {
    (void)status;
    sprite_t sprite = {
        .x = 100,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x - sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testGraphMoveImageLeftMax(void ** status) {
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, LEFT);
    assert_int_equal(sprite.x, 0);
}

void
testGraphMoveImageTooEarlyToMove(void ** status) {
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 10000,
        .pixels_to_move = 10,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    graphMoveImage(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y);
}
