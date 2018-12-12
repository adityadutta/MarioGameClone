#include "Scene02.h"
#include"gdBody.h"
#include<iostream>
#include"MMath.h"
#include"Collider.h"
#include <algorithm>  
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()


float getRadius(const Matrix4 &projectionMatrix, gdBody &body);

Scene02::Scene02(SDL_Window* sdlWindow_) {

	isRunning = false;

	window = sdlWindow_;
	elapsedTime = 0.0f;
}

bool Scene02::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	background = IMG_Load("background.png");
	if (background == nullptr) {
		return false;
	}

	float aspectRatio = (float)w / (float)h;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);

	IMG_Init(IMG_INIT_PNG);

	//initializing the player
	player = new gdBody("player.png", 100.0f, Vector3(0.0f, 50.0f, 0.0f), Vector3(0.0f, -25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	//initializing the player
	collector = new gdBody("collector.png", 100.0f, Vector3(-5.0f, -47.0f, 0.0f), Vector3(3.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	//initializing the balls in a cool way
	for (int i = 0; i < 8; i++)
	{
		srand(time(0));  // Initialize random number generator.
		float x1 = (rand() % 20 + (i * 5)) - 30.0f;
		float x2 = (rand() % 20 + (i * 5)) - 30.0f;
		float x3 = (rand() % 20 + (i * 5)) - 30.0f;
		AddBody(new gdBody("ball.png", 1.0f, Vector3(x1, 25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)));
		AddBody(new gdBody("ball.png", 1.0f, Vector3(x2, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)));
		AddBody(new gdBody("ball.png", 1.0f, Vector3(x3, -10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)));
	}

	for (auto body : bodies) {
		if (body == nullptr) {
			return false;
		}
	}

	return true;
}

void Scene02::OnDestroy() {

	IMG_Quit();

	if (player) {
		delete player;
		player = nullptr;
	}

	if (collector) {
		delete collector;
		collector = nullptr;
	}

	for (auto body : bodies) {
		if (body) {
			delete body;
			body = nullptr;
		}
	}

}

void Scene02::Update(const float time) {
	if (isRunning) {
		elapsedTime += time;

		//check collision of player with balls
		for (int i = 0; i < bodies.size(); i++) {
			if (Collider::CollisionCheck(*player, *bodies[i])) {
				Collider::HandleCollision(*player, *bodies[i], 1.0f);
				auto it = std::find(bodies.begin(), bodies.end(), bodies[i]);
				if (it != bodies.end()) {
					bodies.erase(it);
				}
			}
		}

		//check collision with player and the collector
		if (Collider::CollisionCheck(*player, *collector, 12.0f)) {
			player->position.Set(0.0f, 50.0f, 0.0f);
			player->linearVelocity.SetZero();
			isRunning = false;
		}

		//check borders on the y axis for the player
		if (player->position.y > 52.0f || player->position.y < -48.0f) {
			player->linearVelocity.y = -player->linearVelocity.y;
		}
		//check borders on the x axis for the player
		if (player->position.x > 28.0f || player->position.x < -30.0f) {
			player->linearVelocity.x = -player->linearVelocity.x;
		}
		//check borders on the x axis for the collector
		if (collector->position.x > 18.0f || collector->position.x < -30.0f) {
			collector->linearVelocity.x = -collector->linearVelocity.x;
		}
		//update collector
		if (collector) collector->Update(time);
		//update player
		if (player) player->Update(time);
	}
}

void Scene02::Render() {
	SDL_Rect imageRectangle;
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

	Vector3 collectorCoords = projectionMatrix * collector->position;

	imageRectangle.h = collector->getImage()->h;
	imageRectangle.w = collector->getImage()->w;
	imageRectangle.x = collectorCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	imageRectangle.y = collectorCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
	SDL_BlitSurface(collector->getImage(), nullptr, screenSurface, &imageRectangle);

	for (auto body : bodies) {
		Vector3 screenCoords = projectionMatrix * body->position;

		imageRectangle.h = body->getImage()->h;
		imageRectangle.w = body->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(body->getImage(), nullptr, screenSurface, &imageRectangle);
	}

	SDL_UpdateWindowSurface(window);
}

void Scene02::HandleEvents(const SDL_Event &_event) {

	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.sym)
		{
		case SDLK_SPACE:
			isRunning = true;
			player->linearVelocity.Set(0.0f, -25.0f, 0.0f);
			break;
		case SDLK_d:
			if(!isRunning)
				player->position += Vector3(2.0f, 0.0f, 0.0f);
			break;
		case SDLK_a:
			if (!isRunning)
				player->position -= Vector3(2.0f, 0.0f, 0.0f);
			break;
		default:
			break;
		}
	}
}

void Scene02::AddBody(gdBody* body)
{
	bodies.push_back(body);
}

float getRadius(const Matrix4 &projectionMatrix, gdBody &body) {
	Matrix4 invP = MMath::inverse(projectionMatrix);

	Vector3 upperLeft(0.0f, 0.0f, 1.0f);
	Vector3 lowerRight(body.getImage()->w, body.getImage()->h, 1.0f);

	upperLeft = invP * upperLeft;
	lowerRight = invP * lowerRight;

	//std::cout << upperLeft.ToString() << "," << lowerRight.ToString() << std::endl;
	float width = (lowerRight.x - upperLeft.x) / 2.0f;
	float height = (upperLeft.y - lowerRight.y) / 2.0f;

	//std::cout << width << "," << height << std::endl;
	float radius = (width / 2.0f);

	return radius;
}