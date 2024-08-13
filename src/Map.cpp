#include <iostream>
#include "../include/Map.h"
#include "raylib.h"
#include "../include/utils.h"

constexpr int is_center(int width, int height, int pos) {
    auto x_center = width / 2;
    auto y_center = height / 2;
    return (pos % width == x_center || pos % width + 1 == x_center) &&
           (pos / width == y_center || pos / width + 1 == y_center);
}

Map::Map(int width, int height) : width(width), height(height) {
    std::cout << "Initializing a " << width << 'x' << height << " map..." << std::endl;
    std::srand(std::time(nullptr));
    data = new TileType[width * height];
    for (int i = 0; i < width * height; ++i) {
        for (int j = 0; j < height; ++j) {
            if ((i < width || i % width == 0 || i % width == width - 1 || i > width * (height - 1)) ||
                (std::rand() % 6 == 0 && !is_center(width, height, i)))
                data[i] = TileType::WALL;
            else
                data[i] = TileType::EMPTY;
        }
    }
}

Map::~Map() {
    delete data;
}

void Map::print() const {
    for (int i = 0; i < width * height; ++i) {
        if (i % width == 0)
            std::cout << std::endl;
        std::cout << (data[i] == TileType::EMPTY ? '.' : '#');
    }
    std::cout << std::endl;
}

void Map::render2D() const {
    for (auto x = 0; x < width; ++x) {
        for (auto y = 0; y < height; ++y) {
            auto tile = data[y * width + x];
            if (tile == TileType::WALL)
                DrawRectangle(x * tileSize,
                              y * tileSize,
                              tileSize,
                              tileSize,
                              BLACK);
        }
    }
}
