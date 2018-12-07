#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool bSuccess = game.IsInitialized();
	if (bSuccess)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}