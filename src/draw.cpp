#include "draw.h"

#include <iostream>

using namespace std;
using namespace glm;


namespace draw {

void pixel(sf::Image &image, int x, int y, sf::Color color)
{
	// Check bounds
	if (x < 0) return;
	if (y < 0) return;
	sf::Vector2u size = image.getSize();
	if (x >= (int)size.x) return;
	if (y >= (int)size.y) return;

	// Set pixel
	image.setPixel(x, y, color);
}

void dot(sf::Image &image, int x, int y, int radius, sf::Color color)
{
	// Loop over a circle
	for (int i = -radius; i <= radius; ++i)
	for (int j = -radius; j <= radius; ++j) {
		// Skip pixels out of circle
		if (i * i + j * j > radius * radius)
			continue;

		// Set pixel
		pixel(image, x + i, y + j, color);
	}
}

void square(sf::Image &image, int x, int y, int radius, sf::Color color)
{
	// Loop over a square
	for (int i = -radius; i <= radius; ++i)
	for (int j = -radius; j <= radius; ++j) {
		// Set pixel
		pixel(image, x + i, y + j, color);
	}
}

void line(sf::Image &image, int fromx, int fromy, int tox, int toy, sf::Color color)
{
	// Optimized bresenham line algorithm
	int dx = abs(tox - fromx);
	int dy = abs(toy - fromy);
	int sx = detail::sign(fromx, tox);
	int sy = detail::sign(fromy, toy);
	int error = dx - dy;
	for (;;) {
		pixel(image, fromx, fromy, color);
		bool fx = sx > 0 ? fromx >= tox : fromx <= tox;
		bool fy = sy > 0 ? fromy >= toy : fromy <= toy;
		if (fx && fy)
			break;
		if (2 * error > -dy) {
			error -= dy;
			fromx += sx;
		}
		if (2 * error < dx) {
			error += dx;
			fromy += sy;
		}
	}
}

void bezier(sf::Image &image, list<dvec2> &points, int resolution, sf::Color color)
{
	// Sample curve points
	list<dvec2> samples;
	double step = 1.0 / resolution;
	for (double time = 0.0; time <= 1.0; time += step) {
		list<dvec2> sliders = points;
		while (sliders.size() > 1)
			sliders = detail::slide(sliders, time);
		samples.push_back(sliders.front());
	}

	// Draw curve by connection samples with small lines
	auto i = samples.begin();
	dvec2 last = *i++;
	for (; i != samples.end(); ++i) {
		int fromx = static_cast<int>(last.x);
		int fromy = static_cast<int>(last.y);
		int tox = static_cast<int>(i->x);
		int toy = static_cast<int>(i->y);
		line(image, fromx, fromy, tox, toy, color);
		last = *i;
	}
}

void grid(sf::Image &image, int resolution, sf::Color color)
{
	// Get dimensions
	sf::Vector2u size = image.getSize();

	// Draw rows
	for (size_t j = 0; j < size.y; j += resolution)
	for (size_t i = 0; i < size.x; ++i)
		image.setPixel(i, j, sf::Color(127, 127, 127));

	// Draw columns
	for (size_t i = 0; i < size.x; i += resolution)
	for (size_t j = 0; j < size.y; ++j)
		image.setPixel(i, j, color);
}

namespace detail {

int sign(int from, int to)
{
	int difference = to - from;
	return (difference < 0) ? -1 : (difference > 0) ? 1 : 0;
}

list<dvec2> slide(list<dvec2> &points, double time)
{
	list<dvec2> result;
	auto current = points.begin();
	dvec2 last = *current;
	for (++current; current != points.end(); ++current)
		result.push_back(last * time + *current * (1.0 - time));
	return result;
}

} // namespace detail
} // namespace draw
