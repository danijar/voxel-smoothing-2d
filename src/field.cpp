#include "field.h"

#include <glm/glm.hpp>

#include "draw.h"
#include "points.h"

using namespace std;
using namespace glm;
using namespace sf;

Field::Field(Blocks* blocks, int resolution) : m_blocks(blocks), m_points(m_blocks), m_resolution(resolution)
{
	// initialize data
	clear();
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
}

void Field::clear()
{
	m_image.create(m_blocks->X() * m_resolution + 1, m_blocks->Y() * m_resolution + 1, Color(0, 0, 0));
}

void Field::draw()
{
	// clear texture
	clear();

	// loop over blocks
	ivec2 index;
	for (index.x = 0; index.x < m_blocks->X(); index.x++) {
		for (index.y = 0; index.y < m_blocks->Y(); index.y++) {
			// draw blocks
			if (m_blocks->Get(index.x, index.y))
				draw::square(m_image, coordinates(index.x), coordinates(index.y), 4);

			// fetch points
			auto lines = m_points.find(index);

			// draw pts
			for (auto line : lines) {
				auto i = line.begin();
				dvec2 last = *i;
				draw::dot(m_image, coordinates(index.x, last.x), coordinates(index.y, last.y), 2);
				for (++i; i != line.end(); ++i) {
					draw::line(m_image, coordinates(index.x, last.x), coordinates(index.y, last.y), coordinates(index.x, i->x), coordinates(index.y, i->y));
					draw::dot(m_image, coordinates(index.x, i->x), coordinates(index.y, i->y), 2);
					last = *i;
				}
			}
		}
	}

	// draw grid
	draw::grid(m_image, m_resolution);

	// update texture
	m_texture.loadFromImage(m_image);
}

void Field::click(int X, int Y)
{
	// calculate block from coordinates
	Vector2f offset = m_sprite.getPosition();
	Vector2f size = static_cast<float>(m_resolution) * m_sprite.getScale();
	int i = static_cast<int>((X - offset.x) / size.x);
	int j = static_cast<int>((Y - offset.y) / size.y);

	// toggle block
	m_blocks->Set(i, j, m_blocks->Get(i, j) ? 0 : 1);
}

Sprite* Field::sprite()
{
	return &m_sprite;
}

int Field::coordinates(int block, double offset)
{
	return block * m_resolution + int(offset * m_resolution);
}
