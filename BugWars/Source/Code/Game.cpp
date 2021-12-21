#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] { return new Tank; }, [] {return new Bug; }, [] {return new Bullet; } })
{
	g_Game = this;
}

Game::~Game() {
		for (int i = 0; i < objects.size(); i++)
		{
				GameObject* obj = objects[i];
				delete obj;
		}
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);

	int n = objects.size();

	for (int i = 0; i < objects.size(); i++) {
		GameObject* obj = objects[i];
		if (!obj->disabled) {
			obj->Update(dt);
		}
		else {
			delete obj;
			objects[i--] = objects[objects.size() - 1];
			objects.resize(objects.size() - 1);
		}
	}
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
}

void Game::OnBugsSpawned()
{
}
