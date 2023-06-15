#pragma once
#include "Behavior.h"

class Level;

class MaskShard final : public Behavior
{
public:
	MaskShard() = default;
	MaskShard(const MaskShard& other) = delete;
	MaskShard(MaskShard&& other) noexcept = delete;
	MaskShard& operator=(const MaskShard& other) = delete;
	MaskShard& operator=(MaskShard&& other) noexcept = delete;

private:
	friend Level;
	inline static vector<MaskShard*> s_AllShards{};

	const Vector2 m_InitialForce{ 10, 3 };

	~MaskShard() override = default;

	void Awake() override;
	void OnDestroy() override;
	static void Cleanup();
};
