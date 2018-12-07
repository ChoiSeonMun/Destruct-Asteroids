#pragma once

#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	virtual ~SpriteComponent();

	int		GetTexWidth() const noexcept { return mTexWidth; }
	int		GetTexHeight() const noexcept { return mTexHeight; }
	int		GetDrawOrder() const noexcept { return mDrawOrder; }

	virtual void	Draw(struct SDL_Renderer* renderer);
	virtual void	SetTexture(struct SDL_Texture* texture);
private:
	int		mTexWidth = 0;
	int		mTexHeight = 0;
	int		mDrawOrder = 0;
	struct SDL_Texture*	mTexture;
};