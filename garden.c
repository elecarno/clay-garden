#include <stdio.h>
#include <string.h>

#include "garden.h"
#include "includes/raylib.h"

int activeDropdownId = -1;

Clay_String gDynamicClayString(char *string) {
    return (Clay_String) {
        .length = (int)strlen(string),
        .chars = string
    };
}

void gHandleButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData) {
    ButtonCallback onClick = (ButtonCallback)userData;
    
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        if (onClick != NULL) {
            onClick();
        }

        activeDropdownId = -1;
    }
}

// COMPONENTS --------------------------------------------------------------------------------------
void gBUTTON(char* label, ButtonCallback callback) {
    CLAY_AUTO_ID({
        .backgroundColor = COL_BUTTON_BG,
        .layout = {
            .padding = { 8, 8, 4, 4 },
            .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() }
        }
    }) {
        if (Clay_Hovered()) { SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); }
        Clay_OnHover(gHandleButtonCallback, callback);

        CLAY_TEXT(gDynamicClayString(label),
            CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY, .fontSize = FONT_SIZE_BODY, .textColor = COL_WHITE })
        );
    }
}