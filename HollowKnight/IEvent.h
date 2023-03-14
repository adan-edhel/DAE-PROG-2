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
	static void Invoke(void(IEvent::* function)(Args...), Args&&... args)
	{
		for (IEvent* eventPtr : m_EventPtrs)
			(eventPtr->*function)(std::forward<Args>(args)...);
	}

    virtual void OnKeyDown(const SDL_KeyboardEvent& e)		{}
    virtual void OnKeyUp(const SDL_KeyboardEvent& e)		{}
	virtual void OnMouseMotion(const SDL_MouseMotionEvent& e){}
	virtual void OnMouseDown(const SDL_MouseButtonEvent& e)	{}
	virtual void OnMouseUp(const SDL_MouseButtonEvent& e)	{}

protected:
	virtual ~IEvent()
	{
		m_EventPtrs.erase(std::remove(m_EventPtrs.begin(), m_EventPtrs.end(), this), m_EventPtrs.end());
	}

private:
	inline static std::vector<IEvent*> m_EventPtrs {};
};
