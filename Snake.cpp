/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include "Screen.hpp"
#include "Snake.hpp"
#include <iostream>

namespace SnakeGame {

const Uint8 Snake::S_SNK_RED = 0x01;
const Uint8 Snake::S_SNK_GREEN = 0xFF;
const Uint8 Snake::S_SNK_BLUE = 0x08;
const double Snake::S_INITIAL_SPEED = 0.05;
cint Snake::S_INITIAL_DIRECTION = Snake::Direction::RIGHT;
cint Snake::S_N_SECTS = 8;
cint Snake::S_INITIAL_LIVES = 3;

Snake::Snake(): m_speed(Snake::S_INITIAL_SPEED), m_lives(Snake::S_INITIAL_LIVES),
	m_direction(S_INITIAL_DIRECTION) {
	for (int i = 0; i < S_N_SECTS; i++)
		m_sections.push_back(
			Section(Screen::S_WIDTH/2 - Section::S_SECTION_WIDTH*i, 0)
		);
}

void Snake::draw(Screen & screen) {
	for (int i = 0; i < m_sections.size(); i++)
		m_sections[i].draw(screen);
}

void Snake::updateDirection(int direction) {
	if (
			(m_direction == Snake::Direction::UP || m_direction ==
			Snake::Direction::DOWN) && (direction == Snake::Direction::LEFT ||
			direction == Snake::Direction::RIGHT)
			||
			(m_direction == Snake::Direction::LEFT || m_direction ==
			Snake::Direction::RIGHT) && (direction == Snake::Direction::UP ||
			direction == Snake::Direction::DOWN)
		)
		m_direction = direction;
}

bool Snake::move() {
	for (int i = m_sections.size(); i > 0; i--)
		m_sections[i].move(m_sections[i].calculateDirection(m_sections[i-1]));

	m_sections[0].move(m_direction);

	if (m_sections[0].m_x + Section::S_SECTION_WIDTH >= Screen::S_WIDTH ||
			m_sections[0].m_x - Section::S_SECTION_WIDTH < 0 ||
			m_sections[0].m_y + Section::S_SECTION_WIDTH >= Screen::S_HEIGHT ||
			m_sections[0].m_y + Section::S_SECTION_WIDTH < 0) {
		m_lives -= 1;
		return false;
	}
	else
		return true;
}

void Snake::reset() {
	Snake::resetSections();
	Snake::resetDirection();
}

void Snake::resetSections() {
	m_sections.erase(m_sections.begin() + S_N_SECTS, m_sections.end());

	for (int i = 0; i < S_N_SECTS; i++){
		m_sections[i].m_x = Screen::S_WIDTH/2 - Section::S_SECTION_WIDTH*i;
		m_sections[i].m_y = 0;
	}
}

void Snake::resetDirection() {
	m_direction = S_INITIAL_DIRECTION;
}

bool Snake::collidesWith(Collideable & object) {
	return m_sections[0].collidesWith(object);
}

void Snake::addSection() {
	int N = m_sections.size();
	int basePlacement = m_sections[N-2].calculateDirection(m_sections[N-1]);

	int x = 0;
	int y = 0;

	switch (basePlacement) {
		case Snake::Direction::UP:
			x = m_sections[N-1].m_x;
			y = m_sections[N-1].m_y - Section::S_SECTION_WIDTH;
			break;
		case Snake::Direction::DOWN:
			x = m_sections[N-1].m_x;
			y = m_sections[N-1].m_y + Section::S_SECTION_WIDTH;
			break;
		case Snake::Direction::LEFT:
			x = m_sections[N-1].m_x - Section::S_SECTION_WIDTH;
			y = m_sections[N-1].m_y;
			break;
		case Snake::Direction::RIGHT:
			x = m_sections[N-1].m_x + Section::S_SECTION_WIDTH;
			y = m_sections[N-1].m_y;
			break;
	}

	m_sections.push_back(Section(x, y));
	/*N = m_sections.size();

	SDL_Log("Added a new section at: %d, %d  because last section was at %d, %d  and the previous to that was %d, %d  and the calculated direction was %d", x, y, m_sections[N-2].m_x, m_sections[N-2].m_y,  m_sections[N-3].m_x, m_sections[N-3].m_y, basePlacement);
	SDL_Log("Up: %d", Snake::Direction::UP);
	SDL_Log("Down: %d", Snake::Direction::DOWN);
	SDL_Log("Left: %d", Snake::Direction::LEFT);
	SDL_Log("Right: %d", Snake::Direction::RIGHT);*/
}

void Snake::toString() {  // TODO Remove. For debugging purposes
	SDL_Log("----------------------------------------");
	SDL_Log("The snake is:");
	for (auto section: m_sections)
		section.toString();
	SDL_Log("----------------------------------------");
}

} // namespace SnakeGame
