#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<string>

class Window {
private:
	struct SDL_Window* window;
	struct SDL_Surface* screenSurface;
	int width, height;

public:
	Window(int width_, int height_);
	~Window();
	bool OnCreate();
	void OnDestroy();
	SDL_Window* GetSDL_Window();
};
#endif // !WINDOW_H
