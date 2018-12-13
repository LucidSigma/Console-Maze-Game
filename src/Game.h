#pragma once
#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "Menu.h"
#include "Player.h"

class Game
{
private:
	static constexpr int TOTAL_LEVELS = 5;
	
	static constexpr char EMPTY_SPACE = ' ';
	static constexpr char MOVEABLE = '*';
	static constexpr char KEY = '>';
	static constexpr char LEVEL_EXIT = 'O';
	
	enum class Direction { Up, Left, Down, Right };
	enum class Options { Play, LevelSelect, Help, Exit };

	enum class Controls : char
	{
		Up = 'w',
		Left = 'a',
		Down = 's',
		Right = 'd',
		Reset = 'r',
		Quit = 'q',
	#if defined(_WIN32) || defined(_WIN64)
		Select = '\r'
	#elif defined(__linux__)
		Select = '\n'
	#endif
	};
	
	Level level;
	Player player;
	
	bool isRunning = false;
	bool programRunning = true;
	bool levelComplete = false;
	
	bool hasKey = false;
	
	unsigned int currentLevel;
	unsigned int moveCounter;
	
	unsigned int targetX;
	unsigned int targetY;
	
public:
	void Play();

private:
	void Load();

	void GameLoop();
	void HelpScreen() const;

	void LoadLevel(const char* fileName);
	void PrintLevel() const;

	void GetInput();
	void MovePlayer(Direction direction);
	void MoveTile(Direction direction);

	void LevelMenuControl(Menu& levelMenu);

	bool CanMoveTile(unsigned int x, unsigned int y, Direction direction, const std::vector<std::string>& levelMap) const;
};

#endif