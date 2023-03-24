#include "pch.h"
#include "Behavior.h"

Behavior::Behavior() : Component("Behavior")
{

}

Behavior::~Behavior()
{
	OnDestroy();
}

void Behavior::Update(const float& deltaTime)
{
	
}

void Behavior::OnDestroy()
{
}