#include <cmath>
#include "../include/Entities.h"
#include "raylib.h"
#include "rlgl.h"

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
        if (angle < 0)
            angle += 2 * pi;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        angle += move_speed;
        if (angle > 2 * pi)
            angle -= 2 * pi;
    }
    if (map.data[static_cast<int>(pos_y) * map.width + static_cast<int>(pos_x)] == TileType::EMPTY) {
        position.x = pos_x;
        position.y = pos_y;
    }

    constexpr int fov_deg = fov * (180 / pi);
    constexpr auto one_degree = pi / 180;
    auto start = angle - half_fov;
    for (float i = 0; i < fov_deg;) {
        auto a = start + i * one_degree;
        if (a < 0)
            a += 2 * pi;
        if (a > 2 * pi)
            a -= 2 * pi;
        auto ray = findShortestRay(a);
        DrawLineEx(
                {position.x * tileSize,
                 position.y * tileSize},
                {ray.x * tileSize,
                 ray.y * tileSize},
                3,
                GREEN);
        i++;
    }
}

RayData Player::calculateHorizontalRay(float ray_angle) const {
    float ray_x, ray_y, ray_xoffset, ray_yoffset;
    float aTan = -1 / std::tan(ray_angle);
    if (ray_angle > pi) {
        ray_y = position.y;
        ray_x = position.x + (position.y - ray_y) * aTan;
        ray_yoffset = -0.1;
        ray_xoffset = -ray_yoffset * aTan;
    } else if (ray_angle < pi) {
        ray_y = position.y;
        ray_x = position.x + (position.y - ray_y) * aTan;
        ray_yoffset = 0.1;
        ray_xoffset = -ray_yoffset * aTan;
    } else if (ray_angle == 0 || ray_angle == pi) {
        ray_x = position.x;
        ray_y = position.y;
        ray_xoffset = 0.1;
        ray_yoffset = 0;
    }

    while (ray_x >= 0 && ray_x < map.width && ray_y >= 0 && ray_y < map.height &&
           map.data[static_cast<int>(ray_y) * map.width + static_cast<int>(ray_x)] == TileType::EMPTY) {
        ray_x += ray_xoffset / 10;
        ray_y += ray_yoffset / 10;
    }
    return {ray_x, ray_y};
}

RayData Player::calculateVerticalRay(float ray_angle) const {
    float ray_x, ray_y, ray_xoffset, ray_yoffset;
    float nTan = -std::tan(ray_angle);
    if (ray_angle == pi2 || ray_angle == pi3) {
        ray_x = position.x;
        ray_y = position.y;
        ray_xoffset = 0.1;
        ray_yoffset = 0;
    } else if (ray_angle > pi2 && ray_angle < pi3) {
        ray_x = position.x;
        ray_y = position.y + (position.x - ray_x) * nTan;
        ray_xoffset = -1;
        ray_yoffset = -ray_xoffset * nTan;
    } else {
        ray_x = position.x + 1;
        ray_y = position.y + (position.x - ray_x) * nTan;
        ray_xoffset = 1;
        ray_yoffset = -ray_xoffset * nTan;
    }
    while (ray_x >= 0 && ray_x < map.width && ray_y >= 0 && ray_y < map.height &&
           map.data[static_cast<int>(ray_y) * map.width + static_cast<int>(ray_x)] == TileType::EMPTY) {
        ray_x += ray_xoffset / 100;
        ray_y += ray_yoffset / 100;
    }
    return {ray_x, ray_y};
}

RayData Player::findShortestRay(float angle) const {
    auto hRay = calculateHorizontalRay(angle);
    auto vRay = calculateVerticalRay(angle);
    auto hx = hRay.x - position.x, hy = hRay.y - position.y;
    auto vx = vRay.x - position.x, vy = vRay.y - position.y;
    auto hLength = std::sqrt(hx * hx + hy * hy);
    auto vLength = std::sqrt(vx * vx + vy * vy);
    if (hLength < vLength)
        return hRay;
    else
        return vRay;
}
