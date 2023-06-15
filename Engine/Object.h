#pragma once
#include <iostream>

class GameObject;
class Transform;

enum class Tag
{
	Default,
	Player,
	Enemy,
	Coin
};

class Object
{
public:
	Tag m_Tag{ Tag::Default };
	std::string m_Name;

	Object(const Object& other) = delete;
	Object(Object&& other) noexcept = delete;
	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) noexcept = delete;

	// Compares tags between objects
	bool CompareTag(Tag other) const;
	const std::string& ToString() {return m_Name;}
	static void Destroy(const Object& GameObject, const Object* object);

protected:
	Object(const std::string& name);
	virtual ~Object() = default;
};