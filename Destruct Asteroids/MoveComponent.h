#pragma once

#include "Component.h"

class Vector2D;

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* owner, int updateOrder = 10);

	float	GetAngularSpeed() const noexcept { return mAngularSpeed; }
	float	GetForwardSpeed() const noexcept { return mForwardSpeed; }

	void	SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void	SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	void	Update(float deltaTime) override;
private:
	float	mAngularSpeed = 0.f;	// radians / second
	float	mForwardSpeed = 0.f;	// units / second
};