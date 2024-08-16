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
    calculateAllRays([this](int, RayData ray) {
        DrawLineEx(
                {this->position.x * tileSize,
                 this->position.y * tileSize},
                {ray.x * tileSize + 1,
                 ray.y * tileSize + 1},
                3,
                GREEN);
    });
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
}

RayData Player::calculateHorizontalRay(float ray_angle) const {
    if (ray_angle == 0 || ray_angle == pi) {
        return {position.x, position.y, ray_angle, false};
    }
    float ray_x = position.x, ray_y = position.y;
    float aTan = -1.0f / std::tan(ray_angle);
    float ray_yoffset = ray_angle > pi ? -ray_step : ray_step;
    float ray_xoffset = -ray_yoffset * aTan;

    while (map.in_bounds(ray_x, ray_y) &&
           map.at(ray_x, ray_y) == TileType::EMPTY) {
        ray_x += ray_xoffset;
        ray_y += ray_yoffset;
    }
    return {ray_x, ray_y, ray_angle, false};
}

RayData Player::calculateVerticalRay(float ray_angle) const {
    if (ray_angle == 0 || ray_angle == pi) {
        return {position.x, position.y, ray_angle, true};
    }
    float ray_x = position.x, ray_y = position.y;
    float nTan = -std::tan(ray_angle);
    float ray_xoffset = ray_angle > pi2 && ray_angle < pi3 ? -ray_step : ray_step;
    float ray_yoffset = -ray_xoffset * nTan;

    while (map.in_bounds(ray_x, ray_y) &&
           map.at(ray_x, ray_y) == TileType::EMPTY) {
        ray_x += ray_xoffset;
        ray_y += ray_yoffset;
    }
    return {ray_x, ray_y, ray_angle, true};
}

RayData Player::findShortestRay(float ray_angle) const {
    auto hRay = calculateHorizontalRay(ray_angle);
    auto vRay = calculateVerticalRay(ray_angle);
    auto hLength = calculateRayLength(hRay);
    auto vLength = calculateRayLength(vRay);
    if (hLength < vLength)
        return hRay;
    else
        return vRay;
}

void Player::calculateAllRays(const std::function<void(float, RayData)> &callback) const {
    auto start = angle - half_fov;
    for (float i = 0; i < fov_deg;) {
        auto a = start + i * one_degree;
        if (a < 0)
            a += 2 * pi;
        if (a > 2 * pi)
            a -= 2 * pi;
        auto ray = findShortestRay(a);
        callback(i, ray);
        i += fov_step_size;
    }
}

float Player::calculateRayLength(RayData ray) const {
    return std::sqrt((ray.x - position.x) * (ray.x - position.x) +
                     (ray.y - position.y) * (ray.y - position.y));
}
