#include "Object.h"
#include "AmrothUtils.h"

Object::Object(const std::string& name) : m_Name{name.empty() ? "" : name}
{
}

bool Object::CompareTag(Tag other) const
{
	return m_Tag == other;
}

void Object::Destroy(const Object& GameObject, const Object* object)
{
	// Delete component
	if (object != nullptr)
	{
		if (!object->m_Name.empty() && !GameObject.m_Name.empty())
		{
			Print("(x) ", TextColor::Red);
			Print(object->m_Name, TextColor::Lightblue);
			Print(" destroyed on ", TextColor::Red);
			Print(GameObject.m_Name + " \n", TextColor::Yellow);
		}

		delete object;
		object = nullptr;
	}
}