#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene02.h"
#include "Scene00.h"
#include"MarioGame.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Scene00(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {

	SDL_Event event;

	timer->Start();

	while (isRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				case SDLK_RETURN:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = nullptr;
					currentScene = new Scene02(ptr->GetSDL_Window());
					if (currentScene == nullptr) {
						OnDestroy();
					}

					if (currentScene->OnCreate() == false) {
						OnDestroy();
					}
					break;
				case SDLK_m:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = nullptr;
					currentScene = new MarioGame(ptr->GetSDL_Window());
					if (currentScene == nullptr) {
						OnDestroy();
					}

					if (currentScene->OnCreate() == false) {
						OnDestroy();
					}
					break;
				}
			}
		}
		currentScene->HandleEvents(event);
		
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec

	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy() {
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}