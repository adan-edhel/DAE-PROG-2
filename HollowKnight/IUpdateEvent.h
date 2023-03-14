#pragma once
#include <vector>

class IUpdateEvent
{
public:
	template<typename... Args>
	static void Invoke(void(IUpdateEvent::* function)(Args...), Args&&... args)
	{
		for (IUpdateEvent* eventPtr : m_pEvents)
			(eventPtr->*function)(std::forward<Args>(args)...);
	}

	virtual void Update(const float& deltaTime)	{}

protected:
	IUpdateEvent()
	{
		m_pEvents.push_back(this);
	}

	virtual ~IUpdateEvent()
	{
		m_pEvents.erase(std::remove(m_pEvents.begin(), m_pEvents.end(), this), m_pEvents.end());
	}

private:
	inline static std::vector<IUpdateEvent*> m_pEvents{};
};

