#pragma once

#pragma comment(lib, "SDL2_image.lib")

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <cassert>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Game
{
public:
	// For window
	static constexpr int WINDOW_HEIGHT = 768;
	static constexpr int WINDOW_WIDTH = 1024;
	
	// For Game
	static constexpr int NUM_OF_ASTEROIDS = 20;

	bool	IsInitialized();
	void	RunLoop();
	void	Shutdown();

	void	AddActor(class Actor* actor);
	void	RemoveActor(class Actor* actor);

	void	AddSprite(class SpriteComponent* sprite);
	void	RemoveSprite(class SpriteComponent* sprite);
	SDL_Texture*	GetTexture(const std::string& fileName);

	void	AddAsteroid(class Asteroid* asteroid);
	void	RemoveAsteroid(class Asteroid* asteroid);
	std::vector<class Asteroid*>& GetAsteroids() noexcept { return mAsteroids; }
private:
	void	processInput();
	void	updateGame();
	void	generateOutput();
	void	checkOver();
	void	loadData();
	void	unloadData();
	void	createShip();
	void	revive();

	SDL_Surface*	loadImage(const std::string& fileName);
	SDL_Texture*	loadTexture(const std::string& fileName);
private:
	bool	mbUpdateActor = false;
	bool	mbRunning = false;
	bool	mbReset = false;
	Uint32	mTicksCount = 0;
	SDL_Renderer*	mRenderer = nullptr;
	SDL_Window*		mWindow = nullptr;

	// Game-specific
	bool	mbLose = false;
	bool	mbInvincible = false;
	float	mCooldown = 0.f;
	int		mLife = 5;
	class Ship* mShip = nullptr;
	std::vector<class Asteroid*> mAsteroids;

	// For Drawing
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// Game Object
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;
};

inline SDL_Surface* Game::loadImage(const std::string& fileName)
{
	SDL_Surface* s = IMG_Load(fileName.c_str());
	if (!s)
	{
		SDL_Log("Failed to load the image from the file : %s", fileName);
		return nullptr;
	}
	return s;
}

inline SDL_Texture * Game::loadTexture(const std::string& fileName)
{
	SDL_Surface* surf = loadImage(fileName);
	if (!surf)
	{
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!tex)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName);
		return nullptr;
	}
	mTextures[fileName] = tex;

	return tex;
}


