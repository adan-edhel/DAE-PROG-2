#pragma once
#include <vector>
#include <functional>

template <typename... Args>
class Delegate
{
    using Function = std::function<void(Args...)>;
    std::vector<Function> functions;

public:
    void operator+=(const Function& f)
    {
        functions.push_back(f);
    }

    void operator-=(const Function& f)
    {
        functions.erase(std::remove(functions.begin(), functions.end(), f), functions.end());
    }

    void Invoke(Args... args)
    {
        for (const auto& f : functions)
        {
            f(args...);
        }
    }
};

