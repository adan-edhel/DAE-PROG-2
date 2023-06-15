#pragma once
#include "Component.h"

// Include for derived classes
#include "Transform.h"
#include "GameObject.h"

class Behavior : public Component
{
public:
	Behavior(const Behavior& other) = delete;
	Behavior& operator=(const Behavior& other) = delete;
	Behavior(Behavior&& other) noexcept = delete;
	Behavior& operator=(Behavior&& other) noexcept = delete;

protected:
	Behavior(const std::string& name = "");
	~Behavior() override = default;
};