#pragma once
#include "GameBase/GameBase.h"
#include "Globals.h"

const float DRAWING_RADIUS_2 = 1000000.f;

struct Tank;

struct Game : public GameBase
{
	Game();
	~Game();

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() const override;
	virtual void AddObject(GameObject* object) override;

	virtual void OnBugsSpawned() override;

	std::vector<GameObject*> objects;
};