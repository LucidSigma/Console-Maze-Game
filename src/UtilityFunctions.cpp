#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
extern "C"
{
#include <conio.h>
}

char GetCharacter()
{
	return _getch();
}
#elif defined(__linux__)
#include <cstdio>
#include <cstdlib>

extern "C"
{
#include <termios.h>
#include <unistd.h>
}

char GetCharacter()
{
	char buf = 0;

	struct termios old = { 0 };

	fflush(stdout);

	if (tcgetattr(0, &old) < 0)
	{
		perror("tcsetattr()");
	}

	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;

	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSANOW, &old) < 0)
	{
		perror("tcsetattr ICANON");
	}

	if (read(0, &buf, 1) < 0)
	{
		perror("read()");
	}

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;

	if (tcsetattr(0, TCSADRAIN, &old) < 0)
	{
		perror("tcsetattr ~ICANON");
	}

	return buf;
}
#else
	#error "Unknown/unsupported OS detected."
#endif

void ClearConsole()
{
	static const std::string clearString(100, '\n');

	std::cout << clearString << std::endl;
}