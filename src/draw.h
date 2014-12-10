#pragma once
#include <vector>
#include "sfml/Graphics.hpp"

namespace draw {

void pixel(sf::Image &image, int x, int y, sf::Color color);
void dot(sf::Image &image, int left, int top, int radius = 4);
void square(sf::Image &image, int left, int top, int radius = 3);
void line(sf::Image &image, int fromx, int fromy, int tox, int toy);
void bezier(sf::Image &image, std::vector<std::pair<int, int>> points, int samples = 15);
void grid(sf::Image &image, int resolution);

namespace detail {

int sign(int From, int To);

} // namespace detail
} // namespace draw
