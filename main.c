// INCLUDES ----------------------------------------------------------------------------------------
#define CLAY_IMPLEMENTATION
#include "includes/clay.h"
#include "includes/clay_renderer_raylib.c"

#include "garden.h"

#include <stdio.h>

// GLOBALS -----------------------------------------------------------------------------------------
const Clay_Color COLOUR_BACKGROUND     = { 36, 36, 36, 255 };

// MAIN LAYOUT -------------------------------------------------------------------------------------
void test_callback() {
    printf("hello!");
}

Clay_RenderCommandArray layoutMain() {
    Clay_BeginLayout(); // BEGIN LAYOUT

    CLAY(CLAY_ID("containerMain"), {
        .backgroundColor = COLOUR_BACKGROUND,
        .layout = {
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            },
            .padding = { 8, 8, 8, 8 },
            .childGap = 8
        }
    }) {
        gBUTTON("test", test_callback);
    }

    // END LAYOUT
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}


// RUN APP -----------------------------------------------------------------------------------------
void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

int main(void) {
    Clay_Raylib_Initialize(
        1280, 720, // width and height
        "Clay Garden", // window title
        FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT //flags
    );

    // get memory allocation
    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(
        clayRequiredMemory, 
        malloc(clayRequiredMemory)
    );

    // initalise clay using memory information
    Clay_Initialize(clayMemory, (Clay_Dimensions) {
       .width = GetScreenWidth(),
       .height = GetScreenHeight()
    }, (Clay_ErrorHandler) { HandleClayErrors });

    // handle fonts
    Font fonts[2];
    fonts[FONT_ID_BODY] = LoadFontEx("resources/fonts/Atkinson_Hyperlegible_Next/static/AtkinsonHyperlegibleNext-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[FONT_ID_BODY].texture, TEXTURE_FILTER_BILINEAR);
    fonts[FONT_ID_MONO] = LoadFontEx("resources/fonts/Atkinson_Hyperlegible_Mono/static/AtkinsonHyperlegibleMono-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[FONT_ID_MONO].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    // update loop (per frame)
    while (!WindowShouldClose()) {
        Vector2 dpiScale = GetWindowScaleDPI();

        // update dimensions every frame to handle resizing
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = (float)GetRenderWidth() / dpiScale.x,
            .height = (float)GetRenderHeight() / dpiScale.y
        });

        // handle input
        Vector2 mousePosition = GetMousePosition();
        Vector2 scrollDelta = GetMouseWheelMoveV();
        Clay_SetPointerState(
            (Clay_Vector2) { mousePosition.x, mousePosition.y },
            IsMouseButtonDown(0)
        );
        Clay_UpdateScrollContainers(
            false,
            (Clay_Vector2) { scrollDelta.x * 4, scrollDelta.y * 4 },
            GetFrameTime()
        );

        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        // get layout render commands for the ui
        Clay_RenderCommandArray renderCommands = layoutMain();

        // draw the ui
        BeginDrawing();
        ClearBackground(BLACK); // clear the screen each
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
}