#include "Scene00.h"
#include"gdBody.h"
#include<iostream>
#include"MMath.h"
#include"Collider.h"
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()


Scene00::Scene00(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
}

bool Scene00::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	IMG_Init(IMG_INIT_PNG);


	background = IMG_Load("Title.png");
	if (background == nullptr) {
		return false;
	}

	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);


	return true;
}

void Scene00::OnDestroy() {

	IMG_Quit();

}

void Scene00::Update(const float time) {
	
}

void Scene00::Render() {
	SDL_Rect backgroundRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	backgroundRectangle.h = background->h;
	backgroundRectangle.w = background->w;
	backgroundRectangle.x = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	backgroundRectangle.y = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(background, nullptr, screenSurface, &backgroundRectangle);


	SDL_UpdateWindowSurface(window);
}

void Scene00::HandleEvents(const SDL_Event &_event) {

}
