#pragma once

#include <utility>//std::forward

namespace Abstraction{
//Reusable effect abstraction.
//the derived class should implement the Initial() method,
//with same parameters as its constructor for reinitialization.
template<typename T>
class Reusable{
public:
    //CRTP //Don't need virtual destructor //Don't use Base* to point to Derived
    template<typename...Args>
    void CallInitial(Args&&...args)noexcept(noexcept(std::declval<T&>().Initial(std::forward<Args>(args)...))){
        static_cast<T*>(this)->Initial(std::forward<Args>(args)...);
    }
};
} // namespace 
