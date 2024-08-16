#pragma once

const auto tileSize = 40;
constexpr auto pi = 3.14159265358979323846f;
constexpr auto pi2 = pi / 2;
constexpr auto pi3 = 3 * pi / 2;
constexpr auto fov = pi / 3;
constexpr auto half_fov = fov / 2;
constexpr auto one_degree = pi / 180;
constexpr auto fov_step_size = 0.05f;
constexpr int fov_deg = fov * (180 / pi);
const auto screenWidth = 640;
const auto screenHeight = 480;
const auto mapWidth = 16;
const auto mapHeight = 12;
const float move_speed = 0.05f;
const float playerSize = 5.0f;
constexpr float lineThickness = screenWidth / fov_deg + 1;
constexpr float ray_step = 1.0f / 100;