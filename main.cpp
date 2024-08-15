#include <iostream>
#include <raylib.h>
#include "include/Map.h"
#include "include/Entities.h"

int main() {
    auto map = Map(16, 12);
    auto player = Player(8, 6, 0, map);

    InitWindow(640, 480, "RaysGame");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_VSYNC_HINT);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        map.render2D();
        player.render2D();
        player.updatePlayer();

        EndDrawing();
    }

    return EXIT_SUCCESS;
}
