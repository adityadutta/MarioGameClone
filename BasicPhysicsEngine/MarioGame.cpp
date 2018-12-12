#include "MarioGame.h"
#include"gdBody.h"
#include<iostream>
#include"MMath.h"
#include"Collider.h"
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include"Animation.h"

void MarioGame::clampVelocity()
{
	float maxSpeed = 10.0f;
	float lSpeed = -maxSpeed;
	if (player->linearVelocity.x > maxSpeed)
		player->linearVelocity.x = maxSpeed;
	if (player->linearVelocity.x < lSpeed)
		player->linearVelocity.x = lSpeed;
}

MarioGame::MarioGame(SDL_Window* sdlWindow_) {

	isRunning = false;
	window = sdlWindow_;
	elapsedTime = 0.0f;
}

bool MarioGame::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	background = IMG_Load("background.png");
	if (background == nullptr) {
		return false;
	}
	anims = std::unique_ptr<Animation>(new Animation());
	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);

	IMG_Init(IMG_INIT_PNG);

	//initializing the player
	player = new gdBody("MarioBigIdle.png", 10.0f, Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	return true;
}

void MarioGame::OnDestroy() {

	IMG_Quit();

	if (player) {
		delete player;
		player = nullptr;
	}

}

void MarioGame::Update(const float time) {
		elapsedTime += time;
		anims->setTimer(time);
		//check collision of player with balls
		/*for (int i = 0; i < bodies.size(); i++) {
			if (Collider::CollisionCheck(*player, *bodies[i])) {
				Collider::HandleCollision(*player, *bodies[i], 1.0f);
				auto it = std::find(bodies.begin(), bodies.end(), bodies[i]);
				if (it != bodies.end()) {
					bodies.erase(it);
				}
			}
		}*/

		//check collision with player and the collector
		/*if (Collider::CollisionCheck(*player, *collector, 12.0f)) {
			player->position.Set(0.0f, 50.0f, 0.0f);
			player->linearVelocity.SetZero();
			isRunning = false;
		}*/

		//check borders on the y axis for the player
		/*if (player->position.y > 52.0f || player->position.y < -48.0f) {
			player->linearVelocity.y = -player->linearVelocity.y;
		}*/
		if (player->position.y <= -40.0f) {
			player->position.y = -40.0f;
		}
		//check borders on the x axis for the player
		if (player->position.x > 28.0f || player->position.x < -30.0f) {
			player->linearVelocity.x = -player->linearVelocity.x;
		}

	
	
		clampVelocity();
		player->acceleration.y += -9.81f;
		
		//update player
		if (player) player->Update(time);


}

void MarioGame::Render() {
	SDL_Rect playerRectangle;
	SDL_Rect backgroundRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	backgroundRectangle.h = background->h;
	backgroundRectangle.w = background->w;
	backgroundRectangle.x = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	backgroundRectangle.y = 0.0f; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(background, nullptr, screenSurface, &backgroundRectangle);

	Vector3 playerCoords = projectionMatrix * player->position;

	playerRectangle.h = player->getImage()->h;
	playerRectangle.w = player->getImage()->w;
	playerRectangle.x = playerCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	playerRectangle.y = playerCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(player->getImage(), nullptr, screenSurface, &playerRectangle);

	SDL_UpdateWindowSurface(window);
}

void MarioGame::HandleEvents(const SDL_Event &_event) {

	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.sym)
		{
		case SDLK_d:
			//player->linearVelocity += VECTOR3_RIGHT * 100.0f * 0.016;
			player->ApplyForceToCentre(VECTOR3_RIGHT * 2000);
			anims->setAnim(*player, States::WALKING);
			break;
		case SDLK_a:
			//player->linearVelocity += (VECTOR3_LEFT * 10.0f);
			player->ApplyForceToCentre(VECTOR3_LEFT * 2000);
			break;
		case SDLK_SPACE:
			anims->setAnim(*player, States::JUMPING);
			player->ApplyForceToCentre(VECTOR3_UP * 3000);
			break;
		default:
			break;
		}
	}
}

void MarioGame::AddBody(gdBody* body)
{
	bodies.push_back(body);
}