#pragma once
#include "GameState.h"
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms); // 1 / (60 fps) = 16 milliseconds


class CnsFramework
{
public:
	CnsFramework(int X = 50, int Y = 25, std::chrono::nanoseconds tick_ms = timestep);

	virtual ~CnsFramework();
	virtual void KeyPressed(int Code) {};

	virtual void Update(GameState * state);
	virtual bool Handle_Events();

	void Run();
	void ChangeTickSpeed(std::chrono::nanoseconds ms);

	std::chrono::nanoseconds tick;

	int FPS;
	int ScreenX;
	int ScreenY;

	GameState * current_state;

private:
	void Render(GameState const & state);

	HANDLE hConsole;
	HANDLE hConsoleIn;

	COORD windowBufSize;
	COORD DwBufferCoord;

	SMALL_RECT WindowSize;
};