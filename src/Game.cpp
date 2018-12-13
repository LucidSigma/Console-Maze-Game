#include "Game.h"

#include <iostream>

extern char GetCharacter();
extern void ClearConsole();

void Game::Load()
{
	currentLevel = 1;
	moveCounter = 0;

	std::string fileName = "levels/level";
	fileName += std::to_string(currentLevel);
	fileName += ".txt";

	LoadLevel(fileName.c_str());

	isRunning = true;
}

void Game::Play()
{
	static const std::vector<std::string> menuOptions = { "Play", "Level Select", "Help", "Exit" };

	Menu menu("MAZE GAME");
	menu.Fill(menuOptions);

	std::vector<std::string> levelOptions;

	for (unsigned int levelNumber = 1; levelNumber <= TOTAL_LEVELS; levelNumber++)
	{
		levelOptions.push_back("Level " + std::to_string(levelNumber));
	}

	levelOptions.push_back("Back");

	Menu levelMenu("LEVEL SELECT");
	levelMenu.Fill(levelOptions);

	while (programRunning)
	{
		menu.Print();

		char input = GetCharacter();

		int choice;

		switch (input)
		{
		case static_cast<char>(Controls::Up):
			menu.MoveSelectorUp();

			break;

		case static_cast<char>(Controls::Down):
			menu.MoveSelectorDown();

			break;

		case static_cast<char>(Controls::Select):
			choice = menu.GetSelectorLocation();

			switch (choice)
			{
			case static_cast<char>(Options::Play):
				Load();
				GameLoop();

				break;

			case static_cast<char>(Options::LevelSelect):
				LevelMenuControl(levelMenu);

				break;

			case static_cast<char>(Options::Help):
				HelpScreen();

				break;

			case static_cast<char>(Options::Exit):
				programRunning = false;

				break;

			default:
				break;
			}

			break;

		default:
			break;
		}
	}

	std::cout << std::endl;
}
void Game::GameLoop()
{
	while (isRunning)
	{
		PrintLevel();

		const std::string hasKeyString = hasKey ? "Obtained" : "Not found";

		std::cout << "Moves: " << moveCounter << "\tKey: " << hasKeyString << std::flush;

		GetInput();

		if (levelComplete)
		{
			currentLevel++;

			if (currentLevel > TOTAL_LEVELS)
			{
				isRunning = false;

				levelComplete = false;
				hasKey = false;

				moveCounter = 0;

				ClearConsole();
				
				std::cout << "Congratulations!" << std::endl;

				GetCharacter();
			}
			else
			{
				std::string fileName = "levels/level";
				fileName += std::to_string(currentLevel);
				fileName += ".txt";

				LoadLevel(fileName.c_str());

				levelComplete = false;
				hasKey = false;

				moveCounter = 0;
			}
		}
	}
}

void Game::HelpScreen() const
{
	ClearConsole();

	std::cout << "MAZE GAME HELP\n\n";
	std::cout << "Controls: WASD to move, R to reset level, ESC to return to menu.\n";
	std::cout << "Collect the > to unlock the exit.\n";
	std::cout << "Move to the O to complete the level.\n";
	std::cout << "The * tiles can be moved.\n\n";

	std::cout << "Press any key to return to menu." << std::flush;

	GetCharacter();
}

void Game::LoadLevel(const char* fileName)
{
	level.LoadFile(fileName);

	level.Scan(player);
}

void Game::PrintLevel() const
{
	ClearConsole();

	std::cout << "Level " << currentLevel << "/" << TOTAL_LEVELS << std::endl;

	level.Print();
}

void Game::GetInput()
{
	char input = GetCharacter();

	switch (input)
	{
	case static_cast<char>(Controls::Up):
		MovePlayer(Direction::Up);

		break;

	case static_cast<char>(Controls::Left):
		MovePlayer(Direction::Left);

		break;

	case static_cast<char>(Controls::Down):
		MovePlayer(Direction::Down);

		break;

	case static_cast<char>(Controls::Right):
		MovePlayer(Direction::Right);

		break;

	case static_cast<char>(Controls::Reset):
		level.Reset();
		level.Scan(player);

		hasKey = false;

		break;

	case static_cast<char>(Controls::Quit):
		isRunning = false;

		break;

	default:
		break;
	}
}

void Game::MovePlayer(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		targetX = player.GetX();
		targetY = player.GetY() - 1;

		break;

	case Direction::Left:
		targetX = player.GetX() - 1;
		targetY = player.GetY();

		break;

	case Direction::Down:
		targetX = player.GetX();
		targetY = player.GetY() + 1;

		break;

	case Direction::Right:
		targetX = player.GetX() + 1;
		targetY = player.GetY();

		break;

	default:
		break;
	}

	std::vector<std::string> levelMap = level.GetLevelMap();

	switch (levelMap[targetY][targetX])
	{
	case EMPTY_SPACE:
		level.SwapTiles(player.GetX(), player.GetY(), targetX, targetY);

		player.SetX(targetX);
		player.SetY(targetY);

		moveCounter++;

		break;

	case MOVEABLE:
		if (CanMoveTile(targetX, targetY, direction, levelMap))
		{
			MoveTile(direction);

			moveCounter++;
		}

		break;

	case KEY:
		hasKey = true;

		level.ReplaceTile(targetX, targetY, EMPTY_SPACE);
		level.OpenExit();

		moveCounter++;

		break;

	case LEVEL_EXIT:
		levelComplete = true;

		moveCounter++;

		break;

	default:
		break;
	}
}

void Game::MoveTile(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		level.SwapTiles(player.GetX(), player.GetY() - 1, targetX, targetY - 1);
		level.SwapTiles(player.GetX(), player.GetY(), targetX, targetY);

		player.SetX(targetX);
		player.SetY(targetY);

		break;

	case Direction::Left:
		level.SwapTiles(player.GetX() - 1, player.GetY(), targetX - 1, targetY);
		level.SwapTiles(player.GetX(), player.GetY(), targetX, targetY);

		player.SetX(targetX);
		player.SetY(targetY);

		break;

	case Direction::Down:
		level.SwapTiles(player.GetX(), player.GetY() + 1, targetX, targetY + 1);
		level.SwapTiles(player.GetX(), player.GetY(), targetX, targetY);

		player.SetX(targetX);
		player.SetY(targetY);

		break;

	case Direction::Right:
		level.SwapTiles(player.GetX() + 1, player.GetY(), targetX + 1, targetY);
		level.SwapTiles(player.GetX(), player.GetY(), targetX, targetY);

		player.SetX(targetX);
		player.SetY(targetY);

		break;

	default:
		break;
	}
}

void Game::LevelMenuControl(Menu& levelMenu)
{
	bool inLevelMenu = true;

	while (inLevelMenu)
	{
		levelMenu.Print();

		char input = GetCharacter();

		unsigned int choice;

		switch (input)
		{
		case static_cast<char>(Controls::Up):
			levelMenu.MoveSelectorUp();

			break;

		case static_cast<char>(Controls::Down):
			levelMenu.MoveSelectorDown();

			break;

		case static_cast<char>(Controls::Select):
			choice = levelMenu.GetSelectorLocation();

			if (choice == (levelMenu.GetSize() - 1))
			{
				inLevelMenu = false;
			}
			else
			{
				currentLevel = choice + 1;
				moveCounter = 0;

				std::string fileName = "level";
				fileName += std::to_string(currentLevel);
				fileName += ".txt";

				LoadLevel(fileName.c_str());

				isRunning = true;

				GameLoop();

				inLevelMenu = false;
			}

			break;

		default:
			break;
		}
	}
}

bool Game::CanMoveTile(unsigned int x, unsigned int y, Direction direction, const std::vector<std::string>& levelMap) const
{
	switch (direction)
	{
	case Direction::Up:
		if (levelMap[y - 1][x] == EMPTY_SPACE)
		{
			return true;
		}

		break;

	case Direction::Left:
		if (levelMap[y][x - 1] == EMPTY_SPACE)
		{
			return true;
		}

		break;

	case Direction::Down:
		if (levelMap[y + 1][x] == EMPTY_SPACE)
		{
			return true;
		}

		break;

	case Direction::Right:
		if (levelMap[y][x + 1] == EMPTY_SPACE)
		{
			return true;
		}

		break;

	default:
		break;
	}

	return false;
}