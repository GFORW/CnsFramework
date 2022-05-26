#pragma once
#include <vector>
#include <iostream>
typedef std::vector<std::vector<wchar_t>> Screen;

struct GameState {
public:
	GameState() {};
	GameState(int X, int Y);
	virtual ~GameState();
	void SetChar(unsigned int x, unsigned int y, wchar_t c);
	wchar_t GetChar(unsigned int x, unsigned int y);

	Screen RenderScreen;
	
	std::string name;
	GameState& operator=(const GameState& copy)
	{
		RenderScreen = copy.RenderScreen;
		name = copy.name;
		return *this;
	}
};
