#include "points.h"

#include <iostream>

using namespace std;
using namespace glm;


Points::Points(Blocks *blocks) : m_blocks(blocks)
{

}

list<list<dvec2>> Points::find(ivec2 block)
{
	// Control points
	list<list<ivec2>> lines;
	list<ivec2> *line = nullptr;
	
	// Fetch blocks, neighbours start top left and count
	// around the center block clock wise
	int center = m_blocks->get(block);
	int neighs[8];
	for (int i = 0; i < 8; i++) {
		auto coord = blockFromIndex(i);
		neighs[i] = m_blocks->get(block + coord);
	}

	// Iterate over neighbour blocks
	for (int i = 0; i < 8; i++) {
		int current = neighs[i];
		int next = neighs[(i + 1) % 8];
		bool is_side   = (((i + 1) % 2) == 1);
		bool is_corner = (((i + 1) % 2) == 0);

		if (line) {
			// Border between air and ground needs a line
			if (current != center) {
				// Sides are cool, but corners get skipped when they don't
				// stop a line
				if (is_side || next == center)
					line->push_back(blockFromIndex(i));
			} else if (is_side || next == center) {
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
				line->push_back(blockFromIndex(i));
			}
		}
	}

	// Merge last line with first if touching. This will not merge
	// complete circles yet.
	if (neighs[0] != center && neighs[7] != center) {
		if (lines.size() > 1) {
			lines.front().insert(lines.front().begin(), line->begin(), line->end());
			lines.pop_back();
		} else {
			// Close circle
			auto first_point = lines.front().front();
			lines.front().push_back(first_point);
		}
	}

	list<list<dvec2>> points;
	for (auto &line : lines) {
		points.emplace_back();
		for (auto &neighbour : line)
			points.back().push_back(pointTowards(neighbour));
	}
	return points;
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