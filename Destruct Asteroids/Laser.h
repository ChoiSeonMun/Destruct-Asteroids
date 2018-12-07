#pragma once

#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(Game* game);

	void	UpdateActor(float deltaTime) override;
private:
	float	mLifeTime = 0.5f;
	class CircleComponent*	mCircle = nullptr;
};