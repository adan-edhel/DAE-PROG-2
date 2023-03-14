#pragma once
#include <vector>

class IDrawEvent
{
public:
	template<typename... Args>
	static void Invoke(void(IDrawEvent::* function)(Args...) const, Args&&... args)
	{
		for (IDrawEvent* eventPtr : m_pEvents)
			(eventPtr->*function)(std::forward<Args>(args)...);
	}

	virtual void DrawBackground()		const{}
	virtual void DrawMidground()		const{}
	virtual void DrawForeground()		const{}
	virtual void DrawUserInterface()	const{}

protected:
	IDrawEvent()
	{
		m_pEvents.push_back(this);
	}

	virtual ~IDrawEvent()
	{
		m_pEvents.erase(std::remove(m_pEvents.begin(), m_pEvents.end(), this), m_pEvents.end());
	}

private:
	inline static std::vector<IDrawEvent*> m_pEvents{};
};
