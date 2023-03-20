#pragma once
#include <iostream>
#include "UnityStructs.h"

class GameObject;
class Transform;

class Object
{
public:
	std::string m_Name;
	Tag tag{ Tag::Default };

	const std::string& ToString() {return m_Name;}
	static void Destroy(const Object* objectPtr);

protected:
	Object(const std::string* name);
	virtual ~Object() = default;
};