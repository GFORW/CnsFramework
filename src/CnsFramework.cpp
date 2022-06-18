#include "CnsFramework.h"
#include <conio.h>


CnsFramework::CnsFramework(const int X = 50, const int Y = 25, const std::chrono::nanoseconds tick_ms = timestep) : ScreenX(X), ScreenY(Y), tick(tick_ms)
{
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	// disable text selection
	{
		DWORD mode;
		GetConsoleMode(hConsoleIn, &mode);
		mode &= ENABLE_EXTENDED_FLAGS;
		if (!SetConsoleMode(hConsoleIn, mode))
		{
			std::cout << "SetConsoleMode failed" << GetLastError() << std::endl;
		}
	}
	// set font 
	{
		CONSOLE_FONT_INFOEX ConsoleFontInfo;
		GetCurrentConsoleFontEx(hConsole, FALSE, &ConsoleFontInfo);
		ConsoleFontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		ConsoleFontInfo.FontWeight = 400;
		ConsoleFontInfo.FontFamily = 72;
		wcscpy_s(ConsoleFontInfo.FaceName, L"Terminal");
		ConsoleFontInfo.dwFontSize = COORD{ 8,12 };
		SetCurrentConsoleFontEx(hConsole, FALSE, &ConsoleFontInfo);
	}

	// turn off cursor
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = 0;
		cursorInfo.dwSize = 1;
		if (!SetConsoleCursorInfo(hConsole, &cursorInfo))
		{
			std::cout << "SetConsoleCurInfo failed" << GetLastError() << std::endl;
		}
	}


	WindowSize = { 0, 0, 1, 1 };    // allows setting any size
	SetConsoleWindowInfo(hConsole, TRUE, &WindowSize);

	windowBufSize = { (short)(ScreenX),(short)(ScreenY) };
	if (!SetConsoleScreenBufferSize(hConsole, windowBufSize))
	{
		std::cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << std::endl;
		std::cin.ignore();
	}

	WindowSize = { 0, 0, (short)(ScreenX - 1), (short)(ScreenY - 1) };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &WindowSize))
	{
		std::cout << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
		std::cin.ignore();
	}

	//prevent window resizing
	HWND cWin = GetConsoleWindow();
	SetWindowLong(cWin, GWL_STYLE, GetWindowLong(cWin, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}

CnsFramework::~CnsFramework()
{

}

void CnsFramework::ChangeTickSpeed(const std::chrono::nanoseconds ms)
{
	tick = ms;
}

void CnsFramework::Render(const GameState * const state )
{
	DWORD Chars;
	COORD pos;
	for (short i = 0; i < ScreenX; i++)
		for (short j = 0; j < ScreenY; j++)
		{
			pos = { i,j };
			FillConsoleOutputCharacter(hConsole, static_cast<char>(state->GetChar(i,j)), 1, pos, &Chars);
		}
}

void CnsFramework::Update(){

}

bool CnsFramework::Handle_Events(){

	return true; // false to quit
};

void CnsFramework::Run()
{
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	bool play = true;

	while (play) 
	{
		auto start = clock::now();

		if (_kbhit()) // key pressed
		{
			KeyPressed(_getch());
			if (!FlushConsoleInputBuffer(hConsoleIn))
				std::cout << "FlushConsoleInputBuffer failed with error " << GetLastError();
		}

		play = Handle_Events();

		while (lag >= tick)
		{
			lag -= tick;
		}
		Update();
		Render(current_state);

		auto end = clock::now();

		auto delta_lag = clock::now() - start;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_lag);

		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		if (delta > 0)
			FPS = (1.00f / delta)* 1000.0f;		
		
		auto end_time = std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(tick);
	}
}