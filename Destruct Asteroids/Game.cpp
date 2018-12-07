#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#include "Game.h"
#include "Actor.h"
#include "Utility.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Random.h"
#include "SpriteComponent.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

/*
 * Initilize game object
 *
 * @Return : bool
 * @Param : void
 *
 */
bool Game::IsInitialized()
{
	// Init SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
		return false;
	}

	// Create Window
	mWindow = SDL_CreateWindow(
		"Destruct Asteroids",
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		0
	);
	if (mWindow == nullptr)
	{
		SDL_Log("Failed to create window:%s", SDL_GetError());
		return false;
	}
	
	// Create renderer
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (mRenderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	
	// Init image
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image : %s", SDL_GetError());
		return false;
	}

	Random::Init();

	loadData();

	mbRunning = true;
	mTicksCount = SDL_GetTicks();

	// Init font
	if (TTF_Init() < 0)
	{
		SDL_Log("Unable to initialize SDL_ttf : %s", SDL_GetError());
		return false;
	}
	return true;
}

/*
 * Run game loop
 * 
 * @Return : void
 * @Param : void
 */
void Game::RunLoop()
{
	mShip->SetInvincible();
	while (mbRunning)
	{
		processInput();
		updateGame();
		generateOutput();
		checkOver();
	}
}

/*
 * Shutdown the game
 * 
 * @Return : void
 * @Param : void
 */
void Game::Shutdown()
{
	unloadData();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

/*
 * Add actor to the game
 * @Return : void
 * @Param
 * actor : actor to be added
 */
void Game::AddActor(Actor * actor)
{
	assert(actor);
	if (mbUpdateActor)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

/*
* Remove actor from game
* @Return : void
* @Param
* Actor* actor : actor to be removed
*/
void Game::RemoveActor(Actor* actor)
{
	assert(actor);
	vec_util::Remove(mActors, actor);
	vec_util::Remove(mPendingActors, actor);
}

/*
 * Add the sprite
 * @Return : void
 * @Param
 * sprite : sprite to be added
 */
void Game::AddSprite(SpriteComponent * sprite)
{
	int drawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (drawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

/*
 * Remove the sprite
 * @Return void
 * @Param
 * sprite : sprite to be removed
 */
void Game::RemoveSprite(SpriteComponent * sprite)
{
	vec_util::RemoveStable(mSprites, sprite);
}

void Game::AddAsteroid(Asteroid * asteroid)
{
	mAsteroids.push_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid * asteroid)
{
	vec_util::Remove(mAsteroids, asteroid);
}

/*
 * Get the texture from the file
 * @Return : SDL_Texture*
 * @Param
 * fileName : file to be loaded
 */
SDL_Texture * Game::GetTexture(const std::string & fileName)
{
	// Check the texture already in the map
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		return iter->second;
	}

	return loadTexture(fileName);
}

void Game::processInput()
{
	// For terminate
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mbRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mbRunning = false;
	}

	mbUpdateActor = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
	mbUpdateActor = false;
}

void Game::updateGame()
{

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;
	// Calculate delta time
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	if (deltaTime > 0.5f)
	{
		deltaTime = 0.5f;
	}
	// Update ticks for next frame
	mTicksCount = SDL_GetTicks();

	// Update actors
	mCooldown -= deltaTime;
	// For revival
	if (mbReset && mCooldown <= 0.f)
	{
		createShip();
		mbReset = false;
		
		mShip->SetInvincible();
	}

	mbUpdateActor = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mbUpdateActor = false;
	
	// Move all of pending actors to mActors
	for (auto actor : mPendingActors)
	{
		mActors.emplace_back(actor);
	}
	mPendingActors.clear();

	// Delete dead actors
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::eState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors)
	{
		if (actor == mShip)
		{
			revive();
		}
		delete actor;
	}
}

void Game::generateOutput()
{
	// Clear back buffer
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	//Draw a text
	static TTF_Font* font = TTF_OpenFont("Assets/Fonts/NanumGothic.ttf", 24);
	static SDL_Color red = { 255, 0, 0 };
	static SDL_Color black = { 0, 0, 0 };
	static SDL_Color white = { 255, 255, 255 };
	static const SDL_Rect lifeNumPos = { 10, 0, 120, 50 };
	static const SDL_Rect asteroidsNumPos = { WINDOW_WIDTH - 210, 0, 200, 50 };

	char lifeBuf[128] = { 0 };
	char asteroidsBuf[128] = { 0 };
	sprintf_s(lifeBuf, "Life : %d", mLife);
	sprintf_s(asteroidsBuf, "Asteroids : %d", mAsteroids.size());
	
	SDL_Surface* lifeSurfaceMsg = TTF_RenderUTF8_Blended(font, lifeBuf, red);
	SDL_Surface* asteroidsSurfaceMsg = TTF_RenderUTF8_Blended(font, asteroidsBuf, black);
	SDL_Texture* lifeMsg = SDL_CreateTextureFromSurface(mRenderer, lifeSurfaceMsg);
	SDL_Texture* asteroidsMsg = SDL_CreateTextureFromSurface(mRenderer, asteroidsSurfaceMsg);
	SDL_RenderCopy(mRenderer, lifeMsg, NULL, &lifeNumPos);
	SDL_RenderCopy(mRenderer, asteroidsMsg, NULL, &asteroidsNumPos);

	// Swap
	SDL_RenderPresent(mRenderer);
}

void Game::checkOver()
{
	if (mAsteroids.size() == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Game state - win", "Cool! you win!", mWindow);
		mbRunning = false;
	}
	else if (mbLose)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Game state - lose", "Cheer up! Try next again", mWindow);
		mbRunning = false;
	}
}

void Game::loadData()
{
	// Create asteroids
	for (int i = 0; i < NUM_OF_ASTEROIDS; ++i)
	{
		new Asteroid(this);
	}

	// Create ship
	createShip();
}

void Game::unloadData()
{
	// Delete actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto& p : mTextures)
	{
		SDL_DestroyTexture(p.second);
	}
	mTextures.clear();
}

void Game::createShip()
{
	mShip = new Ship(this);
	mShip->SetPosition(Vector2D(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	mShip->SetRotation(0.f);
}

void Game::revive()
{
	if (mLife > 0)
	{
		mbReset = true;
		mCooldown = 1.f;
		--mLife;
	}
	else
	{
		mbLose = true;
	}
}
