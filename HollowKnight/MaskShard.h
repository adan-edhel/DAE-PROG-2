#pragma once
#include "Behavior.h"

class Level;

class MaskShard final : public Behavior
{
	friend Level;
	inline static vector<MaskShard*> s_AllShards{};

	const Vector2 m_InitialForce{ 10, 3 };

	void Awake() override;
	void OnDestroy() override;
	static void Cleanup();
};
