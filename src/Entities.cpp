#include "../include/Entities.h"
#include "raylib.h"
#include "../include/utils.h"

void Player::render2D() const {
    DrawCircle(position.x * tileSize,
               position.y * tileSize,
               playerSize,
               YELLOW);
}

void Player::updatePlayer() {
    auto pos_x = position.x;
    auto pos_y = position.y;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        pos_y -= 0.1;
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        pos_y += 0.1;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        pos_x -= 0.1;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        pos_x += 0.1;
    }
    if (map.data[static_cast<int>(pos_y) * map.width + static_cast<int>(pos_x)] == TileType::EMPTY) {
        position.x = pos_x;
        position.y = pos_y;
    }
}
