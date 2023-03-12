#pragma once
#include <vector>
#include <functional>

template <typename... Args>
class Event
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

        bool isConstFunction;

        MemberFunction(T* obj, Function func)
            : object(obj), function(func), isConstFunction(false)
        {
        }

        MemberFunction(T* obj, ConstFunction func)
            : object(obj), constFunction(func), isConstFunction(true)
        {
        }

        void operator()(Args... args) const
        {
            if (!isConstFunction)
                (object->*function)(args...);
            else
                (object->*constFunction)(args...);
        }

        bool operator==(const MemberFunction& other) const
        {
            return object == other.object && isConstFunction == other.isConstFunction &&
                ((isConstFunction && constFunction == other.constFunction) || (!isConstFunction && function == other.function));
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
        functions.erase(std::remove_if(functions.begin(), functions.end(),
            [&memberFunction](const std::function<void(Args...)>& f) {
                if constexpr (std::is_same_v<decltype(f), MemberFunction<T>>) {
                    return f == memberFunction;
                }
        return false;
            }),
            functions.end());
    }

    template <typename T>
    void Disconnect(T* obj, void (T::* func)(Args...) const)
    {
        auto memberFunction = MemberFunction<T>(obj, func);
        functions.erase(std::remove_if(functions.begin(), functions.end(),
            [&memberFunction](const std::function<void(Args...)>& f) {
                if constexpr (std::is_same_v<decltype(f), MemberFunction<T>>) {
                    return f == memberFunction;
                }
        return false;
            }),
            functions.end());
    }

    void DisconnectAll()
    {
        functions.clear();
    }

    void Invoke(Args... args)
    {
        for (const auto& function : functions)
        {
            function(args...);
        }
    }
};
