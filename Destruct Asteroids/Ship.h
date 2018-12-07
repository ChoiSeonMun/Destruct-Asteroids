#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(Game* game);

	void	SetInvincible();

	void	ActorInput(const uint8_t* keyState) override;
	void	UpdateActor(float deltaTime) override;
private:
	uint8_t mLaserKey = 0;
	float	mLaserCooldown = 0.f;
	float	mInvincibleCooldown = 0.f;
	bool	mbInvincible= false;
	class CircleComponent* mCircle = nullptr;
	class SpriteComponent* mSprite = nullptr;
};