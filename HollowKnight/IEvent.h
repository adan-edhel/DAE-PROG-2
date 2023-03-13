#pragma once
#include <vector>

class IEvent
{
public:
	IEvent()
	{
		m_EventPtrs.push_back(this);
	}

	template<typename... Args>
	static void Invoke(void(IEvent::* method)(Args...), Args&&... args)
	{
		for (IEvent* eventPtr : m_EventPtrs)
			(eventPtr->*method)(std::forward<Args>(args)...);
	}

protected:
    virtual void OnKeyDown() {}
    virtual void OnKeyUp() {}

	~IEvent()
	{
		m_EventPtrs.erase(std::remove(m_EventPtrs.begin(), m_EventPtrs.end(), this), m_EventPtrs.end());
	}

private:
	inline static std::vector<IEvent*> m_EventPtrs {};
};
