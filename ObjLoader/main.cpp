//
//  main.cpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 18/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#include "Game.hpp"


int main(int argc, char **argv)
{


	Game *game = new Game("obj loader, by Rafael", 800, 600);
	game->Run();

	delete game;


	return 0;
}
