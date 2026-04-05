#ifndef __HUD_H__
#define __HUD_H__

void
hudInit(void);

void
onLivesChanged(void *data);

#ifdef UNIT_TESTING
struct fonts;
typedef struct fonts fonts_handler_t;

fonts_handler_t *
helperUT_hudGetLivesCounterPointer(void);
#endif /* UNIT_TESTING */

#endif /* __HUD_H__ */
