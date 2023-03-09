#include "pch.h"
#include "Behavior.h"
#include "SpriteRenderer.h"

namespace AmrothFramework
{
	Behavior::Behavior()
	{
		gameObject.transform.AddComponent(new SpriteRenderer());
	}
}
