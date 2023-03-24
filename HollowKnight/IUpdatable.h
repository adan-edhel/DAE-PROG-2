#pragma once
#include <vector>

class IUpdatable
{
public:
	template<typename... Args>
	static void Invoke(void(IUpdatable::* function)(Args...), Args&&... args)
	{
		for (IUpdatable* eventPtr : m_pEvents)
			(eventPtr->*function)(std::forward<Args>(args)...);
	}

	virtual void Update(const float& deltaTime)	{}

protected:
	IUpdatable()
	{
		m_pEvents.push_back(this);
	}

	virtual ~IUpdatable()
	{
		m_pEvents.erase(std::remove(m_pEvents.begin(), m_pEvents.end(), this), m_pEvents.end());
	}

private:
	inline static std::vector<IUpdatable*> m_pEvents{};
};

