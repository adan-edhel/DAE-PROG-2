#pragma once
#include <array>
#include <vector>

using std::array;
using std::vector;

class IDrawable
{
private:
	const int m_Layer;
	inline const static int m_TotalLayerCount{ 15 };
	inline static std::array<vector<IDrawable*>, m_TotalLayerCount> m_ArrFunctionList{};

protected:
	inline const static int s_MidLayer{ (m_TotalLayerCount / 2) };

	IDrawable(const int& drawLayer = s_MidLayer) : m_Layer{ drawLayer }
	{
		m_ArrFunctionList[m_Layer].push_back(this);
	}

	virtual ~IDrawable()
	{
		 m_ArrFunctionList[m_Layer].erase(std::remove
		(m_ArrFunctionList[m_Layer].begin(),
		 m_ArrFunctionList[m_Layer].end(), this),
		 m_ArrFunctionList[m_Layer].end());
	}

public:
	template<typename... Args>
	static void Invoke(void(IDrawable::* function)(Args...) const, Args&&... args)
	{
		// Go through array of function lists
		for (vector<IDrawable*> functionList : m_ArrFunctionList)
		{
			// if function list is empty, continue
			if (functionList.empty()) continue;

			// Invoke all functions inside list
			for (IDrawable* func : functionList)
			{
				(func->*function)(std::forward<Args>(args)...);
			}
		}
	}

	virtual void CameraDraw() const{}
	virtual void Draw()	const{}
	virtual void DebugDraw() const{}
};