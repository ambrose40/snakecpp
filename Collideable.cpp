/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include "Collideable.hpp"

namespace SnakeGame {

Collideable::Collideable(int x, int y, int t): Drawable(x,y,t) {}

bool Collideable::collidesWith(Collideable & other) {
	return m_x == other.m_x && m_y == other.m_y;
}


} // namespace SnakeGame