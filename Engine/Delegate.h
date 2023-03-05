#pragma once
#include <vector>
#include <functional>
#include <memory>

template <typename... Args>
class Delegate
{
    using Function = std::function<void(Args...)>;
    struct FunctionWrapper
    {
        std::weak_ptr<void> instance;
        Function function;

        template<typename T>
        void Set(T* object, void (T::* memberFunction)(Args...))
        {
            instance = object->shared_from_this();
            function = [object, memberFunction](Args... args)
            {
                if (auto shared = instance.lock())
                {
                    (object->*memberFunction)(args...);
                }
            };
        }

        bool IsEmpty() const
        {
            return function == nullptr;
        }

        void operator()(Args... args) const
        {
            function(args...);
        }
    };
    std::vector<FunctionWrapper> functions;

public:
    template<typename T>
    void Add(T* object, void (T::* memberFunction)(Args...))
    {
        FunctionWrapper wrapper;
        wrapper.Set(object, memberFunction);
        functions.push_back(wrapper);
    }

    template<typename T>
    void Remove(T* object, void (T::* memberFunction)(Args...))
    {
        auto it = std::remove_if(functions.begin(), functions.end(),
            [object, memberFunction](const FunctionWrapper& wrapper)
            {
                if (auto shared = wrapper.instance.lock())
                {
                    return shared.get() == object && wrapper.function.target<void(T::*)(Args...)>() == memberFunction;
                }
        return false;
            });
        functions.erase(it, functions.end());
    }

    void operator()(Args... args)
    {
        for (auto& f : functions)
        {
            if (!f.IsEmpty())
            {
                f(args...);
            }
        }
    }
};
