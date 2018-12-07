#include "Laser.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Laser::Laser(Game * game)
	: Actor{ game }
{
	// Create a sprite component
	SpriteComponent* sp = new SpriteComponent(this);
	sp->SetTexture(game->GetTexture("Assets/Sprites/Laser.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.f);


	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.f);
}

void Laser::UpdateActor(float deltaTime)
{
	// Reduce lifetime
	mLifeTime -= deltaTime;
	if (mLifeTime <= 0.f)
	{
		SetState(eState::Dead);
	}
	else
	{
		// Check intersect with an asteroid
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (IsCollided(*mCircle, *(ast->GetCircle())))
			{
				SetState(eState::Dead);
				ast->SetState(eState::Dead);
				break;
			}
		}
	}
}
