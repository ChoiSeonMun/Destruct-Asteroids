#include "Asteroid.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game * game)
	: Actor{ game }
{
	// Initialize to random position / orientation
	Vector2D randPos = Random::GetVector(Vector2D::Zero, Vector2D(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));
	
	// Create a sprite component, and set texture
	SpriteComponent* s = new SpriteComponent(this);
	s->SetTexture(GetGame()->GetTexture("Assets/Sprites/Asteroid.png"));

	// Create a move component, and set a forward speed
	MoveComponent* m = new MoveComponent(this);
	m->SetForwardSpeed(50.f);

	// Create a circle component, annd set a radius
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.f);

	// Add this asteroid to Game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
