#include "pch.h"
#include "Object.h"
#include "../Engine/AmrothUtils.h"

Object::Object(const std::string* name) :
	m_Name{*name}
{
	Print("New ", TextColor::Green);
	Print(m_Name + '\n', TextColor::Lightblue);
}

void Object::Destroy(const Object* objectPtr)
{
	if (objectPtr != nullptr)
	{
		Print("(x) ", TextColor::Red);
		Print(objectPtr->m_Name, TextColor::Lightblue);
		Print(" destroyed \n", TextColor::Red);

		delete objectPtr;
		objectPtr = nullptr;
	}
}