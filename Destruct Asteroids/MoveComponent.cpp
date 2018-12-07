#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor * owner, int updateOrder)
	: Component{ owner, updateOrder }
{
}

/*
 * Update position and rotation of actor
 * @Return : void
 * @Param
 * deltaTime : delta time
 */
void MoveComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	// Update rotation of actor
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	// Update position of actor
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2D pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		// Clamp position in screen
		if (pos.x < 0.0f)
		{
			pos.x = 1022.0f;
		}
		else if (pos.x > 1024.0f)
		{
			pos.x = 2.0f;
		}

		if (pos.y < 0.0f)
		{
			pos.y = 766.0f;
		}
		else if (pos.y > 768.0f)
		{
			pos.y = 2.0f;
		}

		mOwner->SetPosition(pos);
	}
}
