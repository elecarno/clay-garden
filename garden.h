#ifndef GARDEN_H
#define GARDEN_H

#include "includes/clay.h"

// FONTS
static const int FONT_ID_BODY = 0;
static const int FONT_ID_MONO = 1;
static const int FONT_SIZE_BODY = 18;


// COLOURS
static const Clay_Color COL_WHITE = { 245, 245, 245, 255 };
static const Clay_Color COL_BLACK = {  15,  15,  15, 255 };

static const Clay_Color COL_BUTTON_BG      = { 60, 60, 60, 255 };


// FUNCTION
typedef void (*ButtonCallback)(void);
Clay_String gDynamicClayString(char *string);


// COMPONENTS
void gBUTTON(char *label, ButtonCallback callback);

#endif // GARDEN_H