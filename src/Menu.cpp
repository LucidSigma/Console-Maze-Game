#include "Menu.h"

#include <iostream>

extern void ClearConsole();

Menu::Menu(const std::string& title) 
	: title(title)
{ }

void Menu::Fill(const std::vector<std::string>& options)
{
	size = options.size();
	
	this->options = options;
	
	for (unsigned int option = 0; option < size; option++)
	{
		selectIcons.push_back(NO_SELECTOR);
	}
	
	selectIcons[0] = SELECTOR;
	selectorLocation = 0;
}

void Menu::Print() const
{
	ClearConsole();
	
	std::cout << title << "\n";
	
	for (unsigned int option = 0; option < size; option++)
	{
		std::cout << selectIcons[option] << options[option];
		
		if (option < (size - 1))
		{
			std::cout << "\n";
		}
	}

	std::cout << std::flush;
}

void Menu::MoveSelectorUp()
{
	if (selectorLocation > 0)
	{
		selectorLocation--;
		
		selectIcons[selectorLocation] = SELECTOR;
		selectIcons[selectorLocation + 1] = NO_SELECTOR;
	}
	else
	{
		selectorLocation = size - 1;

		selectIcons[selectorLocation] = SELECTOR;
		selectIcons[0] = NO_SELECTOR;
	}
}

void Menu::MoveSelectorDown()
{
	if (selectorLocation < (size - 1))
	{
		selectorLocation++;
		
		selectIcons[selectorLocation] = SELECTOR;
		selectIcons[selectorLocation - 1] = NO_SELECTOR;
	}
	else
	{
		selectorLocation = 0;

		selectIcons[selectorLocation] = SELECTOR;
		selectIcons[size - 1] = NO_SELECTOR;
	}
}