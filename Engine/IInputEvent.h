#pragma once
#include <vector>

class IInputEvent
{
public:
	template<typename... Args>
	static void Invoke(void(IInputEvent::* function)(Args...), Args&&... args)
	{
		for (IInputEvent* eventPtr : m_pEvents)
			(eventPtr->*function)(std::forward<Args>(args)...);
	}

	virtual void OnKeyHeld(const SDL_KeyboardEvent& e) {}
    virtual void OnKeyDown(const SDL_KeyboardEvent& e)		{}
    virtual void OnKeyUp(const SDL_KeyboardEvent& e)		{}
	virtual void OnMouseMotion(const SDL_MouseMotionEvent& e){}
	virtual void OnMouseDown(const SDL_MouseButtonEvent& e)	{}
	virtual void OnMouseUp(const SDL_MouseButtonEvent& e)	{}

protected:
	IInputEvent()
	{
		m_pEvents.push_back(this);
	}
	virtual ~IInputEvent()
	{
		m_pEvents.erase(std::remove(m_pEvents.begin(), m_pEvents.end(), this), m_pEvents.end());
	}

private:
	inline static std::vector<IInputEvent*> m_pEvents {};
};
