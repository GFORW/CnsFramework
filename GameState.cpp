#include "GameState.h"

GameState::GameState(int Xsize, int Ysize)
{
	RenderScreen.resize(Xsize, std::vector<wchar_t>(Ysize, L' '));
}

void GameState::SetChar(unsigned int x, unsigned int y, wchar_t c)
{
	RenderScreen.at(x).at(y) = c;
}

wchar_t GameState::GetChar(unsigned int x, unsigned int y)
{
	return RenderScreen.at(x).at(y);
}

GameState::~GameState() {};
