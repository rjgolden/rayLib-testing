#pragma once

#include <raylib.h>
#include <rlgl.h>
#include <cmath>
#include "global.h"

namespace Utilities {

    void init();
    void drawBackground();
    void toggleFullscreenWindow();
    void DrawRectangleLinesPro(Rectangle rec, Vector2 origin, Color color, float rotation);

}