#pragma once

#include "Component.h"
#include "Actor.h"

class Vector2D;

class CircleComponent : public Component
{
public:
	CircleComponent(Actor* owner);
	
	float	GetRadius() const noexcept { return mRadius * mOwner->GetScale(); }
	void	SetRadius(float r) { mRadius = r; }

	const	Vector2D&	GetCenter() const { return mOwner->GetPosition(); }
private:
	float	mRadius = 0.f;
};

bool IsCollided(const CircleComponent& lhs, const CircleComponent& rhs);