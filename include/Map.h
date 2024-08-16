#pragma once

#include <cstdint>

enum class TileType : uint8_t {
    EMPTY = 0,
    WALL,
};

struct Map {
    int width;
    int height;
    TileType *data;

    Map(int width, int height);
    ~Map();
    void print() const;
    void render2D() const;
    [[nodiscard]] TileType at(int x, int y) const;
    [[nodiscard]] bool in_bounds(int x, int y) const;
};
