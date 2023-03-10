#pragma once
#include "Transform.h"

namespace AmrothFramework
{
	class Rigidbody2D : public IComponent
	{
	public:
		bool m_IsStatic{ false };
		Vector2 m_Velocity{};

		Rigidbody2D();
		void Update(const float& deltaTime) override;
		void SetVelocity(const Vector2& velocity);
		void AddForce(const Vector2& force);
		~Rigidbody2D() override = default;

	private:
		float m_GravityModifier{};
		float m_Bounciness{ -0.75f };
		float m_Friction{0};

		void VelocityDecay(const float& deltaTime);
		void SimulateGravity(const float& deltaTime);
	};
}
