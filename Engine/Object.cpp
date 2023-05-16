#include "Object.h"
#include "AmrothUtils.h"

Object::Object(const std::string& name) : m_Name{name.empty() ? "" : name}
{
}

bool Object::CompareTag(Tag other) const
{
	return tag == other;
}

void Object::Destroy(const Object& parent, const Object* object)
{
	// delete component
	if (object != nullptr)
	{
		if (!object->m_Name.empty() && !parent.m_Name.empty())
		{
			Print("(x) ", TextColor::Red);
			Print(object->m_Name, TextColor::Lightblue);
			Print(" destroyed on ", TextColor::Red);
			Print(parent.m_Name + " \n", TextColor::Yellow);
		}

		delete object;
		object = nullptr;
	}
}