#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Player.h"

class Level
{
private:
	static constexpr char PLAYER = '@';
	static constexpr char LOCKED_EXIT = 'X';
	static constexpr char OPEN_EXIT = 'O';
	
	std::vector<std::string> levelMap;
	std::vector<std::string> originalLevel;

	unsigned int exitX = 0;
	unsigned int exitY = 0;
	
public:
	void LoadFile(const char* fileName);
	void Scan(Player& player);
	void Reset();
	void Print() const;
	
	void ReplaceTile(unsigned int x, unsigned int y, char tile);
	void SwapTiles(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	
	void OpenExit();
	
	inline const std::vector<std::string>& GetLevelMap() const { return levelMap; }
};

#endif