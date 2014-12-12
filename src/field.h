#pragma once

#include <vector>
#include <stdint.h>
#include "sfml/Graphics.hpp"
#include "blocks.h"
#include "points.h"

class Field {
public:
	Field(Blocks* blocks, int resolution = 64);
	void clear();
	void draw();
	void click(int X, int Y);
	sf::Sprite* sprite();
private:
	glm::ivec2 coordinates(glm::ivec2 block, glm::dvec2 offset = glm::dvec2(0.5));

	Blocks* m_blocks;
	::Points m_points;
	int m_resolution;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
