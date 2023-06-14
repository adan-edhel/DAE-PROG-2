#include "pch.h"
#include "MaskShard.h"

// Libraries
#include "SpriteLibrary.h"

// Components
#include <SpriteRenderer.h>
#include <Rigidbody2D.h>
#include <Collider.h>

void MaskShard::Awake()
{
	// Register shard
	s_AllShards.push_back(this);

	// Initialize MaskShard
	m_GameObject->m_Tag = Tag::Coin;
	m_Transform->scale = Vector2(0.5f, 0.5f);

	// Initialize SpriteRenderer
	SpriteRenderer* renderer = m_GameObject->AddComponent(new SpriteRenderer());
	renderer->AssignSprite(SpriteLibrary::GetSprite(Sprite::Coin));
	renderer->SetLayer(int(IDrawable::Layers::Pickups));

	// Initialize Collider
	Collider* collider = m_GameObject->AddComponent(new Collider());
	collider->SetSize(Vector2(renderer->GetBounds().width, renderer->GetBounds().height));

	// Initialize Rigidbody2D
	Rigidbody2D* rb = m_GameObject->AddComponent(new Rigidbody2D());
	rb->AddForce(Vector2(RandomRange(-m_InitialForce.x, m_InitialForce.x), m_InitialForce.y));
}

void MaskShard::OnDestroy()
{
	s_AllShards.erase(std::remove(s_AllShards.begin(), s_AllShards.end(), this), s_AllShards.end());
}

void MaskShard::Cleanup()
{
	while (!s_AllShards.empty())
	{
		for (int i = 0; i < s_AllShards.size(); i++)
		{
			delete s_AllShards[i]->m_GameObject;
		}
	}
}
