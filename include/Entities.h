#pragma once

#include "Map.h"

struct Player {
    struct {
        float x;
        float y;
    } position;
    float angle;
    float fov;
    Map &map;
    const float move_speed = 0.1f;
    const float playerSize = 5.0f;

    Player(float x, float y, float angle, float fov, Map &map)
            : position({x, y}), angle(angle), fov(fov), map(map) {}

    void render2D() const;
    void updatePlayer();
};

