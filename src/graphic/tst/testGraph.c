#include "testGraph.h"

void
__wrap_glGenTextures(GLsizei n, GLuint *textures){
    (void)textures;
    check_expected(n);
    function_called();
}

void
__wrap_glBindTexture(GLenum target, GLuint texture) {
    (void)texture;
    check_expected(target);
    function_called();
}

void
__wrap_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
                    GLint border, GLenum format, GLenum type, const void * data) {
    check_expected(target);
    check_expected(level);
    check_expected(internalformat);
    check_expected(width);
    check_expected(height);
    check_expected(border);
    check_expected(format);
    check_expected(type);
    check_expected(data);
    function_called();
}

void
__wrap_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    check_expected(target);
    check_expected(pname);
    check_expected(param);
    function_called();
}

void
__wrap_glBegin(GLenum mode) {
    check_expected(mode);
    function_called();
}

void
__wrap_glTexCoord2f(GLfloat s, GLfloat t) {
    check_expected(s);
    check_expected(t);
    function_called();
}

void
__wrap_glVertex2i(GLint x, GLint y) {
    check_expected(x);
    check_expected(y);
    function_called();
}

void
__wrap_glEnd(void) {
    function_called();
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

    expect_value(__wrap_glGenTextures, n, 1);
    expect_function_call(__wrap_glGenTextures);

    expect_value(__wrap_glBindTexture, target, GL_TEXTURE_2D);
    expect_function_call(__wrap_glBindTexture);

    expect_value(__wrap_glTexImage2D, target, GL_TEXTURE_2D);
    expect_value(__wrap_glTexImage2D, level, 0);
    expect_value(__wrap_glTexImage2D, internalformat, GL_RGBA);
    expect_value(__wrap_glTexImage2D, width, sprite.width);
    expect_value(__wrap_glTexImage2D, height, sprite.height);
    expect_value(__wrap_glTexImage2D, border, 0);
    expect_value(__wrap_glTexImage2D, format, GL_RGBA);
    expect_value(__wrap_glTexImage2D, type, GL_UNSIGNED_BYTE);
    expect_value(__wrap_glTexImage2D, data, sprite.image);
    expect_function_call(__wrap_glTexImage2D);

    expect_value(__wrap_glTexParameteri, target, GL_TEXTURE_2D);
    expect_value(__wrap_glTexParameteri, pname, GL_TEXTURE_MIN_FILTER);
    expect_value(__wrap_glTexParameteri, param, GL_NEAREST);
    expect_function_call(__wrap_glTexParameteri);

    expect_value(__wrap_glTexParameteri, target, GL_TEXTURE_2D);
    expect_value(__wrap_glTexParameteri, pname, GL_TEXTURE_MAG_FILTER);
    expect_value(__wrap_glTexParameteri, param, GL_NEAREST);
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

    expect_value(__wrap_glBegin, mode, GL_QUADS);
    expect_function_call(__wrap_glBegin);

    expect_value(__wrap_glTexCoord2f, s, 0.0);
    expect_value(__wrap_glTexCoord2f, t, 1.0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_value(__wrap_glVertex2i, x, sprite.x);
    expect_value(__wrap_glVertex2i, y, sprite.y);
    expect_function_call(__wrap_glVertex2i);

    expect_value(__wrap_glTexCoord2f, s, 1.0);
    expect_value(__wrap_glTexCoord2f, t, 1.0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_value(__wrap_glVertex2i, x, sprite.x + sprite.scale * sprite.width);
    expect_value(__wrap_glVertex2i, y, sprite.y);
    expect_function_call(__wrap_glVertex2i);

    expect_value(__wrap_glTexCoord2f, s, 1.0);
    expect_value(__wrap_glTexCoord2f, t, 0.0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_value(__wrap_glVertex2i, x, sprite.x + sprite.scale * sprite.width);
    expect_value(__wrap_glVertex2i, y, sprite.y + sprite.scale * sprite.height);
    expect_function_call(__wrap_glVertex2i);

    expect_value(__wrap_glTexCoord2f, s, 0.0);
    expect_value(__wrap_glTexCoord2f, t, 0.0);
    expect_function_call(__wrap_glTexCoord2f);

    expect_value(__wrap_glVertex2i, x, sprite.x);
    expect_value(__wrap_glVertex2i, y, sprite.y + sprite.scale * sprite.height);
    expect_function_call(__wrap_glVertex2i);

    expect_function_call(__wrap_glEnd);

    graphPrintImage(&sprite);
}
