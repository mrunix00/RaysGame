#pragma once

#include "Map.h"
#include "utils.h"

struct RayData {
    float x;
    float y;
};

class Player {
private:
    [[nodiscard]] RayData calculateHorizontalRay(float ray_angle) const;

    [[nodiscard]] RayData calculateVerticalRay(float ray_angle) const;

    [[nodiscard]] RayData findShortestRay(float angle) const;

public:
    struct {
        float x;
        float y;
    } position;
    float angle;
    Map &map;
    const float move_speed = 0.1f;
    const float playerSize = 5.0f;

    Player(float x, float y, float angle, Map &map)
            : position({x, y}), angle(angle), map(map) {}

    void render2D() const;

    void updatePlayer();
};

