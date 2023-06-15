#include "Animator.h"

#include "Animation.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator() : Component("Animator")
{
}

void Animator::Start()
{
	m_SpriteRendererPtr = m_GameObject->GetComponent<SpriteRenderer>();
}

Animation* Animator::Current() const
{
	return m_CurrentAnimPtr;
}

void Animator::Play(const std::string& name)
{
	// Return if there are no clips
	if (m_Clips == nullptr) return;

	// Find given animation in clips
	const std::map<string, Animation*>::iterator it = m_Clips->find(name);

	// Check if animation is valid
	if (!it->first.empty())
	{
		// Check if there is already an animation playing
		if (m_CurrentAnimPtr != nullptr)
		{
			// Return if current animation is the same as given clip
			if (m_CurrentAnimPtr == m_Clips->find(name)->second) return;

			// Reset current animation
			m_CurrentAnimPtr->ResetAnim();
		}

		// AssignClips new clip as current animation
		m_CurrentAnimPtr = it->second;
		m_CurrentAnimPtr->ResetAnim();
		m_SpriteRendererPtr->m_Rows = m_CurrentAnimPtr->GridSize().x;
		m_SpriteRendererPtr->m_Columns = m_CurrentAnimPtr->GridSize().y;
	}
}

void Animator::AssignClips(std::map<std::string, Animation*>* anims)
{
	m_Clips = anims;
}

bool Animator::IsLoaded() const
{
	return !m_Clips->empty();
}

void Animator::Update(const float& deltaTime)
{
	// If there is a current animation
	if (m_CurrentAnimPtr != nullptr)
	{
		// Update SpriteRenderer to current frame
		m_SpriteRendererPtr->Slice(m_CurrentAnimPtr->Update(deltaTime, m_PlaybackSpeed));
	}
}
