#pragma once

struct Player {
    struct {
        float x;
        float y;
    } position;
    float angle;
    float fov;

    Player(float x, float y, float angle, float fov)
            : position({x, y}), angle(angle), fov(fov) {}

    void render2D() const;
};

