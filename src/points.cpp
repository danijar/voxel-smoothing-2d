#include "points.h"

#include <iostream>

using namespace std;
using namespace glm;


Points::Points(Blocks *blocks) : m_blocks(blocks)
{

}

bool Points::check_old(ivec2 block)
{
	// Fetch neighbours
	bool center = m_blocks->Is(block.x, block.y);
	bool topleft = m_blocks->Is(block.x - 1, block.y - 1);
	bool top = m_blocks->Is(block.x + 0, block.y - 1);
	bool topright = m_blocks->Is(block.x + 1, block.y - 1);
	bool right = m_blocks->Is(block.x + 1, block.y + 0);
	bool bottomright = m_blocks->Is(block.x + 1, block.y + 1);
	bool bottom = m_blocks->Is(block.x + 0, block.y + 1);
	bool bottomleft = m_blocks->Is(block.x - 1, block.y + 1);
	bool left = m_blocks->Is(block.x - 1, block.y + 0);
	bool *neighbours[] = { &bottomleft, &left, &topleft, &top, &topright, &right, &bottomright, &bottom, &bottomleft, &left, &topleft, &top };

	// Is set
	if (center)
		return true;

	// Is not set
	else {
		// Iterate over edges
		for (int i = 3; i < 10; i += 2) {
			// Get current and adjacent
			bool *current = neighbours[i];
			bool *overnext = neighbours[i + 2];

			// Found consecutive edges
			if (*current && *overnext)
				return true;
		}
	}

	return false;
}

list<dvec2> Points::find_old(ivec2 block)
{
	// Control points
	list<dvec2> points;
	/*
	// Early skip
	if (!check_old(block))
		return points;

	// Fetch neighbours
	bool center = m_blocks->Is(block.x, block.y);
	bool topleft = m_blocks->Is(block.x - 1, block.y - 1);
	bool top = m_blocks->Is(block.x + 0, block.y - 1);
	bool topright = m_blocks->Is(block.x + 1, block.y - 1);
	bool right = m_blocks->Is(block.x + 1, block.y + 0);
	bool bottomright = m_blocks->Is(block.x + 1, block.y + 1);
	bool bottom = m_blocks->Is(block.x + 0, block.y + 1);
	bool bottomleft = m_blocks->Is(block.x - 1, block.y + 1);
	bool left = m_blocks->Is(block.x - 1, block.y + 0);
	bool *neighbours[] = { &bottomleft, &left, &topleft, &top, &topright, &right, &bottomright, &bottom, &bottomleft, &left, &topleft, &top };

	// Iterate over corners
	for (int i = 2; i < 10; i += 2) {
		// Get current and adjacent
		bool *previous = neighbours[i - 1];
		bool *current = neighbours[i];
		bool *next = neighbours[i + 1];

		// Skip neighbours of center type
		if (*current == center)
			continue;

		// Skip points inside shape
		if (!*current && ((*neighbours[i - 1] && *neighbours[i + 2]) || (*neighbours[i + 1] && *neighbours[i - 2]))) {
			*current = !center;
			continue;
		}

		// Skip lonely or enclosed neighbours
		if (*previous == *next) {
			*current = !center;
			continue;
		}

		// Add point
		points.push_back(pointTowards(i - 2));
	}

	// Iterate over sides
	for (int i = 3; i < 10; i += 2) {
		// Get current and adjacent
		bool *previous = neighbours[i - 1];
		bool *current = neighbours[i];
		bool *next = neighbours[i + 1];

		// Skip neighbours of center type
		if (*current == center)
			continue;

		// Skip points inside shape
		if (center && (*previous && *next))
			continue;
		if (!*current && ((*neighbours[i - 1] && *neighbours[i + 2]) || (*neighbours[i + 1] && *neighbours[i - 2]))) {
			*current = !center;
			continue;
		}

		// Skip lonely or enclosed neighbours
		// Except a surrounding edge equals
		if (*previous == *next && *current != *neighbours[i - 2] && *current != *neighbours[i + 2]) {
			*current = !center;
			continue;
		}

		// Add point
		points.push_back(pointTowards(i - 2));
	}
	*/
	return points;
}

list<list<dvec2>> Points::find(ivec2 block)
{
	// Control points
	list<list<dvec2>> lines;
	list<dvec2> *line = nullptr;
	
	// Fetch blocks, neighbours start top left and count
	// around the center block clock wise
	int center = m_blocks->Get(block.x, block.y);
	int neighs[8];
	for (int i = 0; i < 8; i++) {
		auto coord = blockFromIndex(i);
		neighs[i] = m_blocks->Get(block.x + coord.x, block.y + coord.y);
	}

	// Iterate over neighbour blocks
	for (int i = 0; i < 8; i++) {
		int current = neighs[i];
		int next = neighs[(i + 1) % 8];
		bool is_side   = (((i + 1) % 2) == 1);
		bool is_corner = (((i + 1) % 2) == 0);

		/*
		// Merge last line with first if touching. This will not merge
		// complete circles yet.
		if (i == 7 && lines.size() > 1 && neighs[0] != center) {
			//lines.pop_back();
			//lines.front().pop_front(); // First neighbour was an enclosed corner
			lines.front().insert(lines.front().begin(), line->begin(), line->end());
			lines.pop_back();
		}
		*/

		if (line) {
			// Border between air and ground needs a line
			if (current != center) {
				// Sides are cool, but corners get skipped when they don't
				// stop a line
				if (is_side || next == center)
					line->push_back(pointTowards(blockFromIndex(i)));
			} else {
				// Stop line since we found an end of the border
				line = nullptr;
			}
		} else {
			// Start a new line for the border between air and ground that
			// just appeared. However, skips lines that would only have one
			// point, so we have to look at the next block, too.
			if (current != center && next != center) {
				lines.emplace_back();
				line = &lines.back();
				line->push_back(pointTowards(blockFromIndex(i)));
			}
		}
	}

	return lines;
}

glm::ivec2 Points::blockFromIndex(int i)
{
	// Returns first positive representant, we need this so that the
	// conditions below "wrap around"
	auto modulo = [](int i, int n) { return (i % n + n) % n; };

	ivec2 block(0, 0);
	// For two indices, zero is right so skip
	if (modulo(i - 1, 4))
		// The others are either 1 or -1
		block.x = modulo(i - 1, 8) / 4 ? -1 : 1;
	// Other axis is same sequence but shifted
	if (modulo(i - 3, 4))
		block.y = modulo(i - 3, 8) / 4 ? -1 : 1;
	return block;
}

dvec2 Points::pointTowards(ivec2 neighbour)
{
	dvec2 point;
	point.x = static_cast<double>(neighbour.x);
	point.y = static_cast<double>(neighbour.y);
	point *= .85;

	// Convert from neighbour space into
	// drawing space of the block
	point *= 0.5;
	point += dvec2(.5);

	return point;
}

dvec2 Points::pointTowards_old(int i)
{
	dvec2 point;
	point.x = ((i + 7) % 8 < 4 ? 1 : -1) * ((i + 7) % 4 == 0 ? 0 : 1);
	point.y = ((i + 5) % 8 < 4 ? 1 : -1) * ((i + 5) % 4 == 0 ? 0 : 1);
	point.x = (.85 * point.x) * .5 + .5;
	point.y = (.85 * point.y) * .5 + .5;
	return point;
}
