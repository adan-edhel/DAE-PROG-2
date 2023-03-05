#include "pch.h"
#include "Character.h"

#include <iostream>

#include "Game.h"

Character::Character()
{
	Game::myDelegate.Connect(this, &Character::Update);
}

void Character::Update(float deltaTime)
{
	std::cout << "It works!\n";
}