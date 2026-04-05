#include "hud.h"
#include "fonts.h"
#include "lives.h"

#define LIVES_COUNTER_NUM_DIGIT 2
#define LIVES_COUNTER_X_POS 5
#define LIVES_COUNTER_Y_POS 5

static fonts_handler_t *lives_counter;

void
hudInit(void)
{
    lives_counter = fontsCreateFontsHandler(LIVES_COUNTER_NUM_DIGIT);
    fontsInitLayout(lives_counter, LIVES_COUNTER_X_POS, LIVES_COUNTER_Y_POS);
    fontsRegisterSprites(lives_counter);
    livesCreate(16, 5);
}

void
onLivesChanged(void *data)
{
    int lives = *(int *)data;
    fontsDrawNumber(lives, lives_counter);
}

#ifdef UNIT_TESTING
fonts_handler_t *
helperUT_hudGetLivesCounterPointer(void)
{
    return lives_counter;
}
#endif /* UNIT_TESTING */
