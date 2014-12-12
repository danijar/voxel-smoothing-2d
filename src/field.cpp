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
	m_image.create(m_blocks->get_size().x * m_resolution + 1, m_blocks->get_size().y * m_resolution + 1, Color(0, 0, 0));
}

void Field::draw()
{
	// clear texture
	clear();

	// loop over blocks
	ivec2 index;
	for (index.x = 0; index.x < m_blocks->get_size().x; index.x++) {
		for (index.y = 0; index.y < m_blocks->get_size().y; index.y++) {
			// draw blocks
			if (m_blocks->get(index))
				draw::square(m_image, coordinates(index).x, coordinates(index).y, 4);

			// fetch points
			auto lines = m_points.find(index);

			// draw pts
			for (auto line : lines) {
				auto i = line.begin();
				ivec2 last_point = coordinates(index, *i);
				ivec2 current_point;
				draw::dot(m_image, last_point.x, last_point.y, 2);
				for (++i; i != line.end(); ++i) {
					current_point = coordinates(index, *i);
					draw::line(m_image, last_point.x, last_point.y, current_point.x, current_point.y);
					draw::dot(m_image, current_point.x, current_point.y);
					last_point = current_point;
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
	// Calculate block from coordinates
	ivec2 block;
	Vector2f offset = m_sprite.getPosition();
	Vector2f size = static_cast<float>(m_resolution) * m_sprite.getScale();
	block.x = static_cast<int>((X - offset.x) / size.x);
	block.y = static_cast<int>((Y - offset.y) / size.y);

	// Toggle block
	m_blocks->set(block, m_blocks->get(block) ? 0 : 1);
}

Sprite* Field::sprite()
{
	return &m_sprite;
}

ivec2 Field::coordinates(ivec2 block, dvec2 offset)
{
	return block * m_resolution + ivec2(offset * dvec2(m_resolution));
}
