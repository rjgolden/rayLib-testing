#pragma once

#include <raylib.h>
#include <rlgl.h>
#include <cmath>
#include "config.h"

namespace Utilities {

    void init();
    void drawBackground();
    float toggleFullScreenWindow();
    void DrawRectangleLinesPro(Rectangle rec, Vector2 origin, float rotation, Color color);

}