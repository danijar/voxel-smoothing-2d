#include "points.h"

#include <iostream>

using namespace std;
using namespace glm;


Points::Points(Blocks *Blocks) : m_blocks(Blocks)
{

}

bool Points::check(ivec2 block)
{
	// fetch neighbours
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

	// is set
	if (center)
		return true;

	// is not set
	else {
		// iterate over edges
		for (int i = 3; i < 10; i += 2) {
			// get current and adjacent
			bool *current = neighbours[i];
			bool *overnext = neighbours[i + 2];

			// found consecutive edges
			if (*current && *overnext)
				return true;
		}
	}

	return false;
}

list<dvec2> Points::find(ivec2 block)
{
	// control points
	list<dvec2> points;

	// early skip
	if (!check(block))
		return points;

	// fetch neighbours
	bool center      = m_blocks->Is(block.x, block.y);
	bool topleft     = m_blocks->Is(block.x - 1, block.y - 1);
	bool top         = m_blocks->Is(block.x + 0, block.y - 1);
	bool topright    = m_blocks->Is(block.x + 1, block.y - 1);
	bool right       = m_blocks->Is(block.x + 1, block.y + 0);
	bool bottomright = m_blocks->Is(block.x + 1, block.y + 1);
	bool bottom      = m_blocks->Is(block.x + 0, block.y + 1);
	bool bottomleft  = m_blocks->Is(block.x - 1, block.y + 1);
	bool left        = m_blocks->Is(block.x - 1, block.y + 0);
	bool *neighbours[] = { &bottomleft, &left, &topleft, &top, &topright, &right, &bottomright, &bottom, &bottomleft, &left, &topleft, &top };

	// iterate over corners
	for (int i = 2; i < 10; i += 2) {
		// get current and adjacent
		bool *previous = neighbours[i - 1];
		bool *current  = neighbours[i];
		bool *next     = neighbours[i + 1];

		// skip neighbours of center type
		if (*current == center)
			continue;

		// skip points inside shape
		if (!*current && ((*neighbours[i - 1] && *neighbours[i + 2]) || (*neighbours[i + 1] && *neighbours[i - 2]))) {
			*current = !center;
			continue;
		}

		// skip lonely or enclosed neighbours
		if (*previous == *next) {
			*current = !center;
			continue;
		}

		// add point
		points.push_back(pointTowards(i - 2));
	}

	// iterate over sides
	for (int i = 3; i < 10; i += 2) {
		// get current and adjacent
		bool *previous = neighbours[i - 1];
		bool *current = neighbours[i];
		bool *next = neighbours[i + 1];

		// skip neighbours of center type
		if (*current == center)
			continue;
		
		// skip points inside shape
		if (center && (*previous && *next))
			continue;
		if (!*current && ((*neighbours[i - 1] && *neighbours[i + 2]) || (*neighbours[i + 1] && *neighbours[i - 2]))) {
			*current = !center;
			continue;
		}

		// skip lonely or enclosed neighbours
		// except a surrounding edge equals
		if (*previous == *next && *current != *neighbours[i - 2] && *current != *neighbours[i + 2]) {
			*current = !center;
			continue;
		}

		// add point
		points.push_back(pointTowards(i - 2));
	}

	return points;
}

dvec2 Points::pointTowards(int i)
{
	dvec2 point;
	point.x = ((i + 7) % 8 < 4 ? 1 : -1) * ((i + 7) % 4 == 0 ? 0 : 1);
	point.y = ((i + 5) % 8 < 4 ? 1 : -1) * ((i + 5) % 4 == 0 ? 0 : 1);
	point.x = (.85 * point.x) * .5 + .5;
	point.y = (.85 * point.y) * .5 + .5;
	return point;
}
