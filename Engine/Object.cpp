#include "Object.h"
#include "AmrothUtils.h"

Object::Object(const std::string& name) :
	m_Name{name}
{
	if (!name.empty())
	{
		Print("New ", TextColor::Green);
		Print(m_Name + '\n', TextColor::Lightblue);
	}
}

void Object::Destroy(const Object* objectPtr)
{
	if (objectPtr != nullptr)
	{
		if (!objectPtr->m_Name.empty())
		{
			Print("(x) ", TextColor::Red);
			Print(objectPtr->m_Name, TextColor::Lightblue);
			Print(" destroyed \n", TextColor::Red);
		}

		delete objectPtr;
		objectPtr = nullptr;
	}
}