#include "Animator.h"

#include "AmrothUtils.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator() : Component("Animator")
{
}

void Animator::Start()
{
	m_SpriteRend = m_GameObject->GetComponent<SpriteRenderer>();
}

void Animator::PlayAnimation(const std::string& name)
{
	if (m_Clips == nullptr) return;

	const auto it = m_Clips->find(name);
	if (!it->first.empty())
	{
		m_CurrentAnim = it->second;
		m_SpriteRend->m_Rows = m_CurrentAnim->m_RowCount;
		m_SpriteRend->m_Columns = m_CurrentAnim->m_ColumnCount;
		return;
	}
	m_CurrentAnim = nullptr;
}

void Animator::AssignAnimations(std::map<std::string, Animation*>* anims)
{
	m_Clips = anims;
}

void Animator::Update(const float& deltaTime)
{
	if (m_CurrentAnim != nullptr && m_CurrentAnim->m_NumFrames > 1)
	{
		m_SpriteRend->Slice(m_CurrentAnim->Update(deltaTime, m_PlaySpeed));
	}
}