#ifndef SCENE02_H
#define SCENE02_H

#include "Matrix.h"
#include"Vector3.h"
#include "Scene.h"
#include<vector>

#include <SDL.h>
#include<SDL_image.h>

class gdBody;
using namespace MATH;
class Scene02 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	gdBody* player;
	gdBody* collector;
	std::vector<gdBody*> bodies;

	float elapsedTime;
	bool isRunning;

	SDL_Surface* background;
public:
	Scene02(SDL_Window* sdlWindow);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &_event);
	void AddBody(gdBody* body);
};

#endif

