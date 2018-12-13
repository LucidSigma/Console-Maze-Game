#pragma once
#ifndef MENU_H
#define MENU_H

#include <cstddef>
#include <string>
#include <vector>

class Menu
{
private:
	static constexpr char SELECTOR = '>';
	static constexpr char NO_SELECTOR = ' ';
	
	std::string title;
	
	std::vector<char> selectIcons;
	std::vector<std::string> options;
	
	unsigned int size;
	unsigned int selectorLocation;
	
public:
	explicit Menu(const std::string& title);
	
	void Fill(const std::vector<std::string>& options);	
	void Print() const;
	
	void MoveSelectorUp();
	void MoveSelectorDown();
	
	inline unsigned int GetSelectorLocation() const { return selectorLocation; }
	inline unsigned int GetSize() const { return size; }
};

#endif