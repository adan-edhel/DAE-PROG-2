#include "pch.h"
#include "Behavior.h"
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	Behavior::Behavior() :
	gameObject{new Object()}
	{
		//gameObject->transform->AddComponent(new SpriteRenderer());
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
