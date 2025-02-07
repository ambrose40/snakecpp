/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Snake.hpp"
#include "Food.hpp"
#include "Wall.hpp"
#include "Screen.hpp"
#include "SDL2/SDL.h"
#include "main.h"

using namespace SnakeGame;

bool holdGame(Screen & screen, int millis) {
	int startTime = SDL_GetTicks();
	bool quit = false;
	while (SDL_GetTicks() - startTime < millis && !quit) {
		if(screen.processEvents() == Screen::Action::QUIT)
			quit = true;
	}
	return quit;
}

bool pauseGame(Screen & screen, bool & pause) {
	int startTime = SDL_GetTicks();
	bool quit = false;
	while (!quit && pause) {
		int action = screen.processEvents();
		switch (action) {
			case Screen::Action::QUIT:
				quit = true;
				break;
			case Screen::Action::PAUSE:
				pause = false;
				break;
		}

	}
	return quit;
}

void resetLevel(Snake & snake, Food & food, Food & food2, bool & starting) {
	snake.die();
	snake.reset();
	food = Food();
	food2 = Food();
	starting = true;
}

void createWalls(std::vector<Wall *> & walls) {
	const int N_HORIZONTAL = Screen::S_WIDTH / Wall::S_WALL_WIDTH;
	const int N_VERTICAL = Screen::S_HEIGHT / Wall::S_WALL_WIDTH - 2;

	for (int i = 0; i < N_HORIZONTAL; i++) {
		Wall * upperWall = new Wall(i * Wall::S_WALL_WIDTH, 0, 0);
		Wall * lowerWall = new Wall(i * Wall::S_WALL_WIDTH, 
			Screen::S_HEIGHT - 3 * Wall::S_WALL_WIDTH, 0);
		walls.push_back(upperWall);
		walls.push_back(lowerWall);
	}
	for (int i = 1; i < N_VERTICAL - 1; i++) {
		Wall * leftmostWall = new Wall(0, i * Wall::S_WALL_WIDTH, 0);
		Wall * rightmostWall = new Wall(Screen::S_WIDTH - Wall::S_WALL_WIDTH,
			i * Wall::S_WALL_WIDTH, 0);
		walls.push_back(leftmostWall);
		walls.push_back(rightmostWall);
	}
}

void drawWalls(std::vector<Wall *> & walls, Screen & screen) {
	for (auto wall: walls)
		wall->draw(screen);
}

void freeWalls(std::vector<Wall *> & walls) {
	for (auto wall: walls)
		delete wall;
	walls.clear();	
}

int main(int argc, char ** argv) {
	srand(time(NULL));

	Screen screen;
	Snake snake;
	Food food;
	Food food2;

	std::vector<Wall *> walls;
	createWalls(walls);

	int score = 0;

	if (!screen.init()) {
		SDL_Log("Error initializing screen");
		return -1;
	}

	bool quit = false;
	bool starting = true;
	bool pause = false;
	
	while (!quit && snake.m_lives > 0) {
		screen.clear();
		snake.draw(screen);
		food.draw(screen);
		food2.draw(screen);

		drawWalls(walls, screen);
		screen.update(score, snake.m_lives, false);

		if (starting) {
			quit = holdGame(screen, 1500);
			starting = false;
		}

		switch (screen.processEvents()) {
			case Screen::Action::QUIT:
				quit = true;
				break;
			case Screen::Action::PAUSE:
				pause = true;
				break;
			case Screen::Action::MOVE_UP:
				if(!snake.m_hasUpdated)
					snake.updateDirection(Snake::Direction::UP);
				break;
			case Screen::Action::MOVE_DOWN:
				if(!snake.m_hasUpdated)
					snake.updateDirection(Snake::Direction::DOWN);
				break;
			case Screen::Action::MOVE_LEFT:
				if(!snake.m_hasUpdated)
					snake.updateDirection(Snake::Direction::LEFT);
				break;
			case Screen::Action::MOVE_RIGHT:
				if(!snake.m_hasUpdated)
					snake.updateDirection(Snake::Direction::RIGHT);
				break;
		}

		if (pause)
			quit = pauseGame(screen, pause);

		int elapsed = SDL_GetTicks();

		if (elapsed/20 % 12 == 0) {
			if (!snake.move())
				resetLevel(snake, food, food2, starting);
			else {
				if (snake.collidesWith(food)) {
                    consumeFood(food, score, snake);
                }
				if (snake.collidesWith(food2)) {
					consumeFood(food2, score, snake);
				}

				for (auto wall: walls)
					if (snake.collidesWith(* wall))
						resetLevel(snake, food, food2, starting);

				for (int i = 1; i < snake.m_sections.size(); i++)
					if (snake.collidesWith(* snake.m_sections[i]))
						resetLevel(snake, food, food2, starting);
			}
		}

		if (score >= 1000) {
			snake.m_lives = 0;
			screen.clear();	
			screen.drawGameWon();	
			
			screen.update(score, snake.m_lives, true);
			holdGame(screen, 3000);
		} else if (snake.m_lives == 0) {
			screen.clear();	
			screen.drawGameOver();		
			
			screen.update(score, snake.m_lives, true);
			holdGame(screen, 3000);
		}
	}

	freeWalls(walls);
	screen.close();

	return 0;
}

void consumeFood(SnakeGame::Food &food, int &score, SnakeGame::Snake &snake)
{
    int t = food.type;
    food = Food();

    switch (t)
    {
    case 1:
        score += Food::S_VALUE_1;
        snake.addSection();
        break;
    case 2:
        score += Food::S_VALUE_2;
        snake.addSection();
        snake.addSection();
        break;
    case 3:
        score += Food::S_VALUE_3;
        snake.addSection();
        snake.addSection();
        snake.addSection();
        break;
    }
}
