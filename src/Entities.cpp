#include <complex>
#include "../include/Entities.h"
#include "raylib.h"
#include "../include/utils.h"

void Player::render2D() const {
    DrawCircle(position.x * tileSize,
               position.y * tileSize,
               playerSize,
               YELLOW);
    DrawLine(position.x * tileSize,
             position.y * tileSize,
             position.x * tileSize + playerSize * 3 * std::cos(angle),
             position.y * tileSize + playerSize * 3 * std::sin(angle),
             RED);
}

void Player::updatePlayer() {
    auto pos_x = position.x;
    auto pos_y = position.y;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        pos_x += move_speed * std::cos(angle);
        pos_y += move_speed * std::sin(angle);
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        pos_x -= move_speed * std::cos(angle);
        pos_y -= move_speed * std::sin(angle);
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        angle -= move_speed;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        angle += move_speed;
    }
    if (map.data[static_cast<int>(pos_y) * map.width + static_cast<int>(pos_x)] == TileType::EMPTY) {
        position.x = pos_x;
        position.y = pos_y;
    }
}
