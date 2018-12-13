#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	unsigned int x;
	unsigned int y;
	
public:
	Player() = default;

	inline void SetX(unsigned int x) { this->x = x; }
	inline void SetY(unsigned int y) { this->y = y; }
	
	inline unsigned int GetX() const { return x; }
	inline unsigned int GetY() const { return y; }
};

#endif
