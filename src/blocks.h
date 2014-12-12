#pragma once

#include <vector>
#include <stdint.h>
#include <glm/glm.hpp>

class Blocks
{
public:
	Blocks(glm::ivec2 max);
	~Blocks();
	void set(glm::ivec2 block, uint8_t value = 1);
	uint8_t get(glm::ivec2 block, uint8_t fallback = 1);
	bool is(glm::ivec2 block, bool fallback = 1);
	uint8_t **get_pointer();
	bool in_range(glm::ivec2 block);
	glm::ivec2 get_size();
	void fill_randomly();
private:
	const glm::ivec2 m_max;
	uint8_t *m_data;
	uint8_t **m_blocks;
};
