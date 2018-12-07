#pragma once

#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	int		GetUpdateOrder() const noexcept { return mUpdateOrder; }

	virtual void	Update(float deltaTime);
	virtual void	ProcessInput(const uint8_t* keyState);
protected:
	class Actor*	mOwner = nullptr;
private:
	int		mUpdateOrder = 0;
};