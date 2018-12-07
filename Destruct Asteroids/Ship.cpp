#include "Ship.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include <SDL/SDL_scancode.h>

Ship::Ship(Game * game)
	: Actor{ game }, mLaserKey{ SDL_SCANCODE_L }
{	
	// Create a input component
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.f);
	ic->SetMaxAngularSpeed(10.f);

	// Create a sprite component
	mSprite = new SpriteComponent(this);
	mSprite->SetTexture(game->GetTexture("Assets/Sprites/Ship.png"));

	// Create a circle component
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(100.f);
}

/* 
 * Set this ship invincible
 * @Return : void
 */
void Ship::SetInvincible()
{
	mbInvincible = true;
	mInvincibleCooldown = 2.f;
	mSprite->SetTexture(GetGame()->GetTexture("Assets/Sprites/InvincibleShip.png"));
}

void Ship::ActorInput(const uint8_t * keyState)
{
	if (mLaserCooldown <= 0.f && keyState[mLaserKey])
	{
		// Create a laser and set its position / rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// Reset laser's cooldown
		mLaserCooldown = 0.5f;
	}
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mInvincibleCooldown -= deltaTime;

	if (!mbInvincible)
	{
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (IsCollided(*mCircle, *(ast->GetCircle())))
			{
				SetState(eState::Dead);
				break;
			}
		}
	}
	else if (mInvincibleCooldown < 0.f)
	{
		mbInvincible = false;
		mSprite->SetTexture(GetGame()->GetTexture("Assets/Sprites/Ship.png"));
	}
}
