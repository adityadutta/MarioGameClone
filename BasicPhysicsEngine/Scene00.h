#ifndef SCENE00_H
#define SCENE00_H

#include "Scene.h"

#include"Matrix.h"
#include <SDL.h>
#include<SDL_image.h>

using namespace MATH;
class Scene00 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	float elapsedTime;
	bool isRunning;

	SDL_Surface* background;
public:
	Scene00(SDL_Window* sdlWindow);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &_event);
};

#endif

