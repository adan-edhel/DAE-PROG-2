#include "Animator.h"

#include "Animation.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator() : Component("Animator")
{
}

void Animator::Start()
{
	m_SpriteRend = m_GameObject->GetComponent<SpriteRenderer>();
}

Animation* Animator::Current() const
{
	return m_CurrentAnim;
}

void Animator::Play(const std::string& name)
{
	// Return if there are no clips
	if (m_Clips == nullptr) return;

	// Find given animation in clips
	const auto it = m_Clips->find(name);

	// Check if animation is valid
	if (!it->first.empty())
	{
		// Check if there is already an animation playing
		if (m_CurrentAnim != nullptr)
		{
			// Return if current animation is the same as given clip
			if (m_CurrentAnim == m_Clips->find(name)->second) return;

			// Reset current animation
			m_CurrentAnim->Reset();
		}

		// AssignClips new clip as current animation
		m_CurrentAnim = it->second;
		m_CurrentAnim->Reset();
		m_SpriteRend->m_Rows = m_CurrentAnim->GridSize().x;
		m_SpriteRend->m_Columns = m_CurrentAnim->GridSize().y;
	}
}

void Animator::AssignClips(std::map<std::string, Animation*>* anims)
{
	m_Clips = anims;
}

void Animator::Update(const float& deltaTime)
{
	// If there is a current animation
	if (m_CurrentAnim != nullptr)
	{
		// Update SpriteRenderer to current frame
		m_SpriteRend->Slice(m_CurrentAnim->Update(deltaTime, m_PlaybackSpeed));
	}
}