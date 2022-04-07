#pragma once

#include<windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {
	// Public Functions
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessage();
	// Private Functions
private:


	// Private Variables
private:
	HINSTANCE hInstance;
	HWND hwnd;
};