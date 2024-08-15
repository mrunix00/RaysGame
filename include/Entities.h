#pragma once

#include "Map.h"
#include "utils.h"
#include <functional>
#include <cmath>

struct RayData {
    float x;
    float y;
    float angle;
};

class Player {
private:
    [[nodiscard]] RayData calculateHorizontalRay(float ray_angle) const;

    [[nodiscard]] RayData calculateVerticalRay(float ray_angle) const;

    [[nodiscard]] RayData findShortestRay(float ray_angle) const;

public:
    struct {
        float x;
        float y;
    } position;
    float angle;
    Map &map;

    Player(float x, float y, float angle, Map &map)
            : position({x, y}), angle(angle), map(map) {}

    void render2D() const;

    void calculateAllRays(const std::function<void(float, RayData)> &callback) const;

    [[nodiscard]] float calculateRayLength(RayData ray) const;

    void updatePlayer();
};

