#pragma once
#include <vector>
#include <functional>

template <typename... Args>
class Delegate
{
    template <typename T>
    struct MemberFunction
    {
        using Function = void(T::*)(Args...);
        T* object;
        Function function;

        MemberFunction(T* obj, Function func)
            : object(obj), function(func)
        {
        }

        void operator()(Args... args) const
        {
            (object->*function)(args...);
        }

        bool operator==(const MemberFunction& other) const
        {
            return object == other.object && function == other.function;
        }
    };

    std::vector<std::function<void(Args...)>> functions;

public:
    template <typename T>
    void Connect(T* obj, void (T::* func)(Args...))
    {
        functions.emplace_back(MemberFunction<T>(obj, func));
    }

    template <typename T>
    void Disconnect(T* obj, void (T::* func)(Args...))
    {
        auto memberFunction = MemberFunction<T>(obj, func);
        functions.erase(std::remove(functions.begin(), functions.end(), memberFunction), functions.end());
    }

    void Invoke(Args... args)
    {
        for (const auto& f : functions)
        {
            f(args...);
        }
    }
};
