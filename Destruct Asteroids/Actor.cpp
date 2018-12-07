#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "Utility.h"

Actor::Actor(Game * game)
	: mGame{ game }
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

/*
 * Update game object
 * this function called from Game
 * @Return : void
 * @Param
 * float deltaTime
 */
void Actor::Update(float deltaTime)
{
	if (mState == eState::Active)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

/*
 * Updates all the components attached to the actor
 * @Return : void
 * @Param
 * float deltaTime
 */
void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

/*
 * Update actor-specific
 * @Return : void
 * @Param
 * float deltaTime
 */
void Actor::UpdateActor(float deltaTime)
{
}

/*
 * Process input. this function called from Game
 * @Return : void
 * @Param
 * keyState : key state
 */
void Actor::ProcessInput(const uint8_t * keyState)
{
	if (mState == eState::Active)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t * keyState)
{
}

/*
 * Add component to this actor
 * @Return : void
 * @Param
 * Component* component : component that this actor require
 */
void Actor::AddComponent(Component * component)
{
	int updateOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (updateOrder <= (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

/*
 * Remove component from this actor
 * @Return : void
 * @Param
 * Component* component : component to be removed
 */
void Actor::RemoveComponent(Component * component)
{
	vec_util::RemoveStable(mComponents, component);
}

/*
 * Get forward vector of actor
 * @Return : Vector2D
 * @Param : void
 */
 Vector2D Actor::GetForward()
 {
	 if (mRotation == 0.f)
	 {
		 return Vector2D(1.f, 0.f);
	 }

	 return Vector2D(Math::Cos(mRotation), -Math::Sin(mRotation));
 }
