/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include "Collideable.hpp"
#include "Screen.hpp"
#include "SDL2/SDL.h"

#ifndef FOOD_HPP
#define FOOD_HPP

namespace SnakeGame {

/**
 * This structure represents a food item
 * Its (x,y) position corresponds to the top left pixel
 */
struct Food: Collideable {
	static const Uint8 S_FOOD_1_RED;
	static const Uint8 S_FOOD_1_GREEN;
	static const Uint8 S_FOOD_1_BLUE;
	static const Uint8 S_FOOD_2_RED;
	static const Uint8 S_FOOD_2_GREEN;
	static const Uint8 S_FOOD_2_BLUE;
	static const Uint8 S_FOOD_3_RED;
	static const Uint8 S_FOOD_3_GREEN;
	static const Uint8 S_FOOD_3_BLUE;

	static const unsigned int S_FOOD_WIDTH;
	static const int S_VALUE_1;
	static const int S_VALUE_2;
	static const int S_VALUE_3;

	/**
	 * Default constructor for Food instances
	 */
	Food();

	/**
	 * @see Drawable#draw
	 */
	void draw(Screen & screen);
};

} // namespace SnakeGame

#endif // FOOD_HPP
