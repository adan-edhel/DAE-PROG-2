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
        using ConstFunction = void(T::*)(Args...) const;
        T* object;
        union {
            Function function;
            ConstFunction constFunction;
        };

        MemberFunction(T* obj, Function func)
            : object(obj), function(func)
        {
        }

        MemberFunction(T* obj, ConstFunction func)
            : object(obj), constFunction(func)
        {
        }

        void operator()(Args... args) const
        {
            if (function)
                (object->*function)(args...);
            else
                (object->*constFunction)(args...);
        }

        bool operator==(const MemberFunction& other) const
        {
            return object == other.object && function == other.function && constFunction == other.constFunction;
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
    void Connect(T* obj, void (T::* func)(Args...) const)
    {
        functions.emplace_back(MemberFunction<T>(obj, func));
    }

    template <typename T>
    void Disconnect(T* obj, void (T::* func)(Args...))
    {
        auto memberFunction = MemberFunction<T>(obj, func);
        functions.erase(std::remove(functions.begin(), functions.end(), memberFunction), functions.end());
    }

    template <typename T>
    void Disconnect(T* obj, void (T::* func)(Args...) const)
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