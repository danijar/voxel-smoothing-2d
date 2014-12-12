#pragma once

#include <list>
#include <sfml/Graphics.hpp>
#include <glm/glm.hpp>


namespace draw {

void pixel(sf::Image &image, int x, int y, sf::Color color);
void dot(sf::Image &image, int left, int top, int radius = 4, sf::Color color = sf::Color::White);
void square(sf::Image &image, int left, int top, int radius = 3, sf::Color color = sf::Color::White);
void line(sf::Image &image, int fromx, int fromy, int tox, int toy, sf::Color color = sf::Color(127, 127, 127));
void bezier(sf::Image &image, std::list<glm::dvec2> &points, int resolution = 15, sf::Color color = sf::Color::White);
void grid(sf::Image &image, int resolution, sf::Color color = sf::Color(127, 127, 127));

namespace detail {

int sign(int From, int To);
std::list<glm::dvec2> slide(std::list<glm::dvec2> &points, double time);

} // namespace detail
} // namespace draw
