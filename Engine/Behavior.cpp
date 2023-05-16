#include "Behavior.h"

#include "AmrothUtils.h"

Behavior::Behavior(const std::string& name)
{
	if (!name.empty())
	{
		m_GameObject->m_Name = name;

		Print("New ", TextColor::Green);
		Print(m_Name + "\n", TextColor::Yellow);
	}
}

Behavior::~Behavior()
{
	OnDestroy();
}

void Behavior::OnDestroy()
{
}