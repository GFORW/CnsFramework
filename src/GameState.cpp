#include "GameState.h"

GameState::GameState(const unsigned int Xsize, const unsigned int Ysize, const std::string & state_name)
{
	name = state_name;
	RenderScreen.resize(Xsize, std::vector<wchar_t>(Ysize, L' '));
}

void GameState::SetChar(const unsigned int x, const unsigned int y,const wchar_t & c) 
{
	RenderScreen.at(x).at(y) = c;
}

wchar_t GameState::GetChar(const unsigned int x, const unsigned int y) const
{
	return RenderScreen.at(x).at(y);
}
