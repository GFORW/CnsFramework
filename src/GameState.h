#pragma once
#include <vector>
#include <iostream>
typedef std::vector<std::vector<wchar_t>> Screen;

struct GameState {
public:
	GameState(const unsigned int& Xsize, const unsigned int& Ysize, const std::string& state_name);
	virtual ~GameState() {};
	
	void SetChar(const unsigned int& x, const unsigned int& y, const wchar_t& c);
	wchar_t GetChar(const unsigned int& x, const unsigned int& y) const;

	GameState(const GameState& copy) : RenderScreen(copy.RenderScreen), name(copy.name) 
	{};

	GameState& operator=(const GameState& copy)
	{
		if(this == &copy)
			return *this;

		RenderScreen = copy.RenderScreen;
		name = copy.name;
		return *this;
	}

	std::string name;

private:
	Screen RenderScreen;
};
