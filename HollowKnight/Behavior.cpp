#include "pch.h"
#include "Behavior.h"

namespace AmrothFramework
{
	Behavior::Behavior() :
	gameObject{new Object()}
	{

	}

	void Behavior::Update(const float& deltaTime)
	{
		gameObject->Update(deltaTime);
	}


	Behavior::~Behavior()
	{
		delete gameObject;
	}
}
