#include <iostream>
#include <raylib.h>
#include "include/Map.h"
#include "include/Entities.h"

int main() {
    auto map = Map(mapWidth, mapHeight);
    auto player = Player(mapWidth / 2, mapHeight / 2, 0, map);

    InitWindow(screenWidth, screenHeight, "RaysGame");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_VSYNC_HINT);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        player.updatePlayer();

        player.calculateAllRays([&](float r, RayData ray) {
            float ray_length = player.calculateRayLength(ray);
            float corrected_angle = player.angle - ray.angle;
            if (corrected_angle < 0)
                corrected_angle += 2 * pi;
            if (corrected_angle > 2 * pi)
                corrected_angle -= 2 * pi;
            ray_length = ray_length * std::cos(corrected_angle);
            float line_height = screenWidth / ray_length;
            if (line_height > screenWidth)
                line_height = screenWidth;
            float line_offset = (float) screenHeight - line_height;

            float lighting_factor = 1.0f / (1.0f + (ray_length * 0.05f));
            Color color = {0,
                           0,
                           static_cast<unsigned char>(255 * lighting_factor),
                           255,};

            DrawRectangle((r * lineThickness),
                          line_offset / 2,
                          lineThickness,
                          line_height,
                          color);
        });
        EndDrawing();
    }

    return EXIT_SUCCESS;
}
