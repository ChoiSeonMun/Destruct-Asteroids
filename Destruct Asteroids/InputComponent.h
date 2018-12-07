#pragma once

#include "MoveComponent.h"

using uint8_t = unsigned char;

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor* owner);

	float	GetMaxForwardSpeed() const noexcept { return mMaxForwardSpeed; }
	float	GetMaxAngularSpeed() const noexcept { return mMaxAngularSpeed; }
	int 	GetForwardKey() const noexcept { return mForwardKey; }
	int		GetBackKey() const noexcept { return mBackKey; }
	int		GetClockwiseKey() const noexcept { return mClockwiseKey; }
	int		GetCounterClockwiseKey() const noexcept { return mCounterClockwiseKey; }

	void	SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void	SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void	SetForwardKey(int key) { mForwardKey = key; }
	void	SetBackKey(int key) { mBackKey = key; }
	void	SetClockwiseKey(int key) { mClockwiseKey = key; }
	void	SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

	void	ProcessInput(const uint8_t* keyState) override;
private:
	float	mMaxForwardSpeed = 0.f;
	float	mMaxAngularSpeed = 0.f;
	int		mForwardKey = 0;
	int		mBackKey = 0;
	int		mClockwiseKey = 0;
	int		mCounterClockwiseKey = 0;
};