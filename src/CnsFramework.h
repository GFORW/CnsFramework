#pragma once
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "GameState.h"

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms); // 1 / (60 fps) = 16 milliseconds


class CnsFramework
{
public:
	CnsFramework(const int X ,const int Y , const std::chrono::nanoseconds tick_ms);

	virtual ~CnsFramework();
	virtual void KeyPressed(const int Code) const {};

	virtual void Update();
	virtual bool Handle_Events();

	void Run();
	void ChangeTickSpeed(const std::chrono::nanoseconds ms);

	std::chrono::nanoseconds tick;

	int FPS;
	int ScreenX;
	int ScreenY;

	GameState * current_state;

private:
	void Render(const GameState* const state);

	HANDLE hConsole;
	HANDLE hConsoleIn;

	COORD windowBufSize{};

	SMALL_RECT WindowSize{};
};