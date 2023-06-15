#include "Behavior.h"

#include "AmrothUtils.h"
#include "CORE.h"

Behavior::Behavior(const std::string& name)
{
	if (!name.empty())
	{
		m_GameObject->m_Name = name;

		if (CORE::s_DebugMode)
		{
			Print("New ", TextColor::Green);
			Print(m_Name + "\n", TextColor::Yellow);
		}
	}
}
