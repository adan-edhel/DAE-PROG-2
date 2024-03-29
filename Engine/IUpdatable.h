#pragma once
#include <vector>

class IUpdatable
{
public:
	template<typename... Args>
	static void Invoke(void(IUpdatable::* function)(Args...), Args&&... args)
	{
		for (int i = 0; i < m_EventPtrs.size(); i++)
		{
			(m_EventPtrs[i]->*function)(std::forward<Args>(args)...);
		}
	}

	virtual void Update(const float& deltaTime)	{}

protected:
	IUpdatable()
	{
		m_EventPtrs.push_back(this);
	}

	virtual ~IUpdatable()
	{
		m_EventPtrs.erase(std::remove(m_EventPtrs.begin(), m_EventPtrs.end(), this), m_EventPtrs.end());
	}

private:
	inline static std::vector<IUpdatable*> m_EventPtrs{};
};