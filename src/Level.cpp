#include "Level.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

extern void ClearConsole();

void Level::LoadFile(const char* fileName)
{
	std::ifstream levelFile(fileName);
	bool validFile = false;

	while (!validFile)
	{
		try
		{
			if (!levelFile.is_open())
			{
				throw std::invalid_argument("Invalid level filename.");
			}
			else
			{
				validFile = true;
			}
		}
		catch (const std::invalid_argument&)
		{
			ClearConsole();
			std::cout << fileName << " cannot be found or is corrupted. Please fix to continue." << std::endl;

			std::cin.get();
		}
	}

	originalLevel.clear();
	
	std::string levelLine;
	
	while (!levelFile.eof())
	{
		std::getline(levelFile, levelLine);
		
		originalLevel.push_back(levelLine);
	}
	
	levelFile.close();
	
	levelMap = originalLevel;
}

void Level::Scan(Player& player)
{
	for (std::vector<std::string>::size_type y = 0; y < levelMap.size(); y++)
	{
		for (std::vector<std::string>::size_type x = 0; x < levelMap[y].length(); x++)
		{
			switch (levelMap[y][x])
			{
			case PLAYER:
				player.SetX(x);
				player.SetY(y);
				
				break;

			case LOCKED_EXIT:
				exitX = x;
				exitY = y;

				break;
				
			default:
				break;
			}
		}
	}
}

void Level::Reset()
{
	levelMap = originalLevel;
}

void Level::Print() const
{
	for (std::vector<std::string>::size_type y = 0; y < levelMap.size(); y++)
	{
		std::cout << levelMap[y] << "\n";
	}

	std::cout << std::flush;
}

void Level::ReplaceTile(unsigned int x, unsigned int y, char tile)
{
	levelMap[y][x] = tile;
}

void Level::SwapTiles(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	char placeholderTile = levelMap[y1][x1];
	
	levelMap[y1][x1] = levelMap[y2][x2];
	levelMap[y2][x2] = placeholderTile;
}

void Level::OpenExit()
{
	levelMap[exitY][exitX] = OPEN_EXIT;
}