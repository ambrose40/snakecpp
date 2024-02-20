/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include <stdlib.h>
#include "Screen.hpp"
#include "Food.hpp"
#include <ctime>

namespace SnakeGame {

const Uint8 Food::S_FOOD_1_RED = 0x00;
const Uint8 Food::S_FOOD_1_GREEN = 0xFF;
const Uint8 Food::S_FOOD_1_BLUE = 0x00;

const Uint8 Food::S_FOOD_2_RED = 0xFF;
const Uint8 Food::S_FOOD_2_GREEN = 0xFF;
const Uint8 Food::S_FOOD_2_BLUE = 0x00;

const Uint8 Food::S_FOOD_3_RED = 0xFF;
const Uint8 Food::S_FOOD_3_GREEN = 0x00;
const Uint8 Food::S_FOOD_3_BLUE = 0x00;

const unsigned int Food::S_FOOD_WIDTH = 20;

const int Food::S_VALUE_1 = 50;
const int Food::S_VALUE_2 = 100;
const int Food::S_VALUE_3 = 300;

Food::Food(): Collideable(0, 0, 0) {
	srand(time(0));
    type = (int) (rand() % 3) + 1;
	m_x = (int) ((Screen::S_WIDTH / S_FOOD_WIDTH - 2.0) * (1.0 * rand() / RAND_MAX) + 1) * S_FOOD_WIDTH;
	m_y = (int) ((Screen::S_HEIGHT / S_FOOD_WIDTH - 4.0) * (1.0 * rand() / RAND_MAX) + 1) * S_FOOD_WIDTH;
}

void Food::draw(Screen & screen) {
	for (int i = 0; i < S_FOOD_WIDTH; i++)
		for (int j = 0; j < S_FOOD_WIDTH; j++)

		switch (type) {
			case 1:
				screen.setPixel((int) m_x + i, (int) m_y + j, S_FOOD_1_RED, S_FOOD_1_GREEN, S_FOOD_1_BLUE);
				break;
			case 2:
				screen.setPixel((int) m_x + i, (int) m_y + j, S_FOOD_2_RED, S_FOOD_2_GREEN, S_FOOD_2_BLUE);
				break;
			case 3:
				screen.setPixel((int) m_x + i, (int) m_y + j, S_FOOD_3_RED, S_FOOD_3_GREEN, S_FOOD_3_BLUE);
				break;
		}
			
}

} // namespace SnakeGame
