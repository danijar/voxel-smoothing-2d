#pragma once

#include <list>
#include <stdint.h>
#include <glm/glm.hpp>
#include "blocks.h"

class Points
{
public:
	Points(Blocks *blocks);
	std::list<std::list<glm::dvec2>> find(glm::ivec2 block);
private:
	glm::ivec2 blockFromIndex(int i);
	glm::dvec2 pointTowards(glm::ivec2 neighbour);

	Blocks *m_blocks;
};
