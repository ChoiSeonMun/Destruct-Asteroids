#pragma once

#include <vector>

#include "Math.h"

class Actor
{
public:
	enum class eState
	{
		Active,
		Paused,
		Dead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void	SetState(eState state) { mState = state; }
	void	SetScale(float scale) { mScale = scale; }
	void	SetRotation(float rotation) { mRotation = rotation; }
	void	SetPosition(const Vector2D& center) { mPosition = center; }
	
	eState	GetState() const noexcept { return mState; }
	float	GetScale() const noexcept { return mScale; }
	float	GetRotation() const noexcept { return mRotation; }
	const Vector2D& GetPosition() const noexcept { return mPosition; }
	class Game* GetGame() const noexcept { return mGame; }

	void	Update(float deltaTime);
	void	UpdateComponents(float deltaTime);
	virtual void	UpdateActor(float deltaTime);
	
	void	ProcessInput(const uint8_t* keyState);
	virtual void	ActorInput(const uint8_t* keyState);

	void	AddComponent(class Component* component);
	void	RemoveComponent(class Component* component);
	Vector2D	GetForward();
private:
	// Actor's state
	eState	mState = eState::Active;

	// Transform
	float		mScale = 1.f;			// 1.f for 100%
	float		mRotation = 0.f;		// in radian
	Vector2D	mPosition = Vector2D::Zero;
	
	//Components held by this actor
	std::vector<class Component*>	mComponents;
	class Game*	mGame;
};

