#include <iostream>
#include <windows.h>

#include "Potion.h"

// CUSTOM ACTOR
void Potion::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "P";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
