#include "SpriteComponent.h"
#include "Game.h"
#include "Actor.h"
#include "Math.h"
#include <cassert>
#include <SDL/SDL.h>

SpriteComponent::SpriteComponent(Actor * owner, int drawOrder)
	: Component{ owner }, mDrawOrder{ drawOrder }
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

/*
 * Draw sprite to renderer
 * @Return : void
 * @Param
 * renderer : renderer to which sprite render
 *
 * @Pre-condition
 * renderer is not nullptr
 */
void SpriteComponent::Draw(SDL_Renderer * renderer)
{
	assert(renderer);
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// Draw
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

/*
 * Set the texture(overridable)
 * @Return : void
 * @Param
 * texture : texture to set
 * 
 * @Pre-condition
 * texture is not nullptr
 */
void SpriteComponent::SetTexture(SDL_Texture * texture)
{
	assert(texture);
	mTexture = texture;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
