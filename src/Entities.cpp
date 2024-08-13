#include "../include/Entities.h"
#include "raylib.h"
#include "../include/utils.h"

void Player::render2D() const {
    DrawCircle(position.x * tileSize,
               position.y * tileSize,
               5,
               YELLOW);
}
