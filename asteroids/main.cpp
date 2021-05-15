#include <iostream>

#include <SFML/Graphics.hpp>

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

//#include "Game.h"
#include"Game.h"
#include"AiGame.h"
#include"Helpers.h"
#include"NeuralNet.h";
#include"Generation.h"
#include"Population.h"

int main()
{
	AiGame game;
	game.run();
}