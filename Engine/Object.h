#pragma once
#include <iostream>

class GameObject;
class Transform;

enum class Tag
{
	Default,
	Player,
	Enemy
};

class Object
{
public:
	std::string m_Name;
	Tag tag{ Tag::Default };

	bool CompareTag(Tag other) const;
	const std::string& ToString() {return m_Name;}
	static void Destroy(const Object& parent, const Object* object);

protected:
	Object(const std::string& name);
	virtual ~Object() = default;
};