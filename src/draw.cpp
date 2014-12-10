#include "draw.h"
using namespace std;

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

void dot(sf::Image &image, int x, int y, int radius)
{
	// Loop over a circle
	for (int i = -radius; i <= radius; ++i)
	for (int j = -radius; j <= radius; ++j) {
		// Skip pixels out of circle
		if (i * i + j * j > radius * radius)
			continue;

		// Set pixel
		pixel(image, x + i, y + j, sf::Color(255, 255, 255));
	}
}

void square(sf::Image &image, int x, int y, int radius)
{
	// Loop over a square
	for (int i = -radius; i <= radius; ++i)
	for (int j = -radius; j <= radius; ++j) {
		// Set pixel
		pixel(image, x + i, y + j, sf::Color(255, 255, 255));
	}
}

void line(sf::Image &image, int fromx, int fromy, int tox, int toy)
{
	// Optimized bresenham line algorithm
	int dx = abs(tox - fromx);
	int dy = abs(toy - fromy);
	int sx = detail::sign(fromx, tox);
	int sy = detail::sign(fromy, toy);
	int error = dx - dy;
	for (;;) {
		pixel(image, fromx, fromy, sf::Color(127, 127, 127));
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

void bezier(sf::Image &image, vector<pair<int, int>> points, int samples)
{
	// For now, just draw a straight line
	for (auto point : points) {

	}
}

void grid(sf::Image &image, int resolution)
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
		image.setPixel(i, j, sf::Color(127, 127, 127));
}

namespace detail {

int sign(int from, int to)
{
	int difference = to - from;
	return (difference < 0) ? -1 : (difference > 0) ? 1 : 0;
}

} // namespace detail
} // namespace draw
