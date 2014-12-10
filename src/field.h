#pragma once

#include <vector>
#include <stdint.h>
#include "sfml/Graphics.hpp"
#include "blocks.h"
#include "points.h"

class Field {
public:
	Field(Blocks* blocks, int resolution = 32);
	void clear();
	void draw();
	void click(int X, int Y);
	sf::Sprite* sprite();
private:
	int coordinates(int block, double offset = 0.5);
	void set(int X, int Y, uint8_t value = 1);
	uint8_t get(int X, int Y);

	Blocks* m_blocks;
	::Points m_points;
	int m_resolution;
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
