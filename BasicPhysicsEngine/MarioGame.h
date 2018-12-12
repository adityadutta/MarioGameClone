#ifndef MARIOGAME_H
#define MARIOGAME_H

#include "Matrix.h"
#include"Vector3.h"
#include "Scene.h"
#include<vector>
#include "Animation.h"
#include <memory>
#include <SDL.h>
#include<SDL_image.h>

class gdBody;
using namespace MATH;
class MarioGame : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;

	gdBody* player;
	gdBody* collector;
	std::vector<gdBody*> bodies;

	float elapsedTime;
	bool isRunning;
	std::unique_ptr <Animation> anims;
	SDL_Surface* background;

	void clampVelocity();
public:
	MarioGame(SDL_Window* sdlWindow);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &_event);
	void AddBody(gdBody* body);
};

#endif //!MARIOGAME_H

