#include "sfml/Window.hpp"
#include "blocks.h"
#include "points.h"
#include "field.h"
using namespace sf;

// Debug
#include <iostream>
#include "draw.h"
using namespace std;

int main()
{
	// Open window
	RenderWindow window(VideoMode(651, 331), "Voxel Smoothing 2D");
	
	// Intialization
	Blocks blocks(20, 10);
	blocks.Random();
	Field field(&blocks);
	field.sprite()->setPosition(5, 5);
	field.draw();

	// main loop
	while (window.isOpen()) {
		// Handle events
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::Escape:
					window.close();
					break;
				}
				break;
			case Event::MouseButtonPressed:
				Vector2f target = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
				field.click(static_cast<int>(target.x), static_cast<int>(target.y));
				field.draw();
				break;
			}
		}

		// Draw sprite
		window.clear();
		window.draw(*field.sprite());
		window.display();
	}
}
