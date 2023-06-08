#pragma once
#include <array>
#include <vector>

using std::array;
using std::vector;

class IDrawable
{
public:
	enum class Layers
	{
		Background = 0,
		Actors = 4,
		Pickups = 5,
		Middleground = 7,
		Platforms = 8,
		Foreground = 10
	};

	inline const static int m_TotalLayerCount{ 15 };
	inline const static int s_MidLayer{ (m_TotalLayerCount / 2) };

	template<typename... Args>
	static void Invoke(void(IDrawable::* function)(Args...) const, Args&&... args, const int& layer)
	{
		// if function list is empty, continue
		if (m_ArrFunctionList[layer].empty()) return;

		// Invoke all functions inside list
		for (IDrawable* func : m_ArrFunctionList[layer])
		{
			(func->*function)(std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void InvokeAll(void(IDrawable::* function)(Args...) const, Args&&... args)
	{
		// Go through array of function lists
		for (int layer = 0; layer < m_ArrFunctionList.size(); layer++)
		{
			// if function list is empty, continue
			if (m_ArrFunctionList[layer].empty()) continue;

			// Invoke all functions inside list
			for (IDrawable* func : m_ArrFunctionList[layer])
			{
				(func->*function)(std::forward<Args>(args)...);
			}
		}
	}

	virtual void CameraDraw() const {}
	virtual void Draw()	const {}
	virtual void UIDraw() const {}
	virtual void DebugDraw() const {}

	int GetLayer() const { return m_OrderInLayer; }
	void SetLayer(const int& layer)
	{
		RemoveFromVector();
		m_OrderInLayer = layer;
		m_ArrFunctionList[m_OrderInLayer].push_back(this);
	}

protected:
	IDrawable(const int& drawLayer = s_MidLayer) : m_OrderInLayer{ drawLayer }
	{
		m_ArrFunctionList[m_OrderInLayer].push_back(this);
	}

	virtual ~IDrawable()
	{
		RemoveFromVector();
	}

private:
	int m_OrderInLayer;
	inline static std::array<vector<IDrawable*>, m_TotalLayerCount> m_ArrFunctionList{};

	void RemoveFromVector()
	{
		m_ArrFunctionList[m_OrderInLayer].erase(std::remove
		(m_ArrFunctionList[m_OrderInLayer].begin(),
		m_ArrFunctionList[m_OrderInLayer].end(), this),
		m_ArrFunctionList[m_OrderInLayer].end());
	}
};