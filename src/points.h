#pragma once

#include <list>
#include <stdint.h>
#include <glm/glm.hpp>
#include "blocks.h"

class Points
{
public:
	Points(Blocks *blocks);
	bool check(glm::ivec2 block);
	std::list<glm::dvec2> find(glm::ivec2 block);
private:
	glm::dvec2 pointTowards(int i);

	Blocks *m_blocks;
};
