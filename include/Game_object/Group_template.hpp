#pragma once

#include <algorithm>//std::find
#include <type_traits>

namespace Template{
//if doesn't have -> false_type
template<typename, typename=void>
struct has_emplace_front:std::false_type{};
//if has -> true_type
template<typename T>
struct has_emplace_front<T, std::void_t<decltype(std::declval<T>().emplace_front(std::declval<typename T::value_type>()))>>: std::true_type{};

template<typename box_type>
class Group_template
{   
public:
    Group_template()=default;
    virtual ~Group_template()=default;
    using T=typename box_type::value_type;
    void AddTop(T&&item){box.emplace_back(std::move(item));}
    void AddBot(T&&item){//vector doesn't have emplace_front
        if constexpr (has_emplace_front<T>::value)
            box.emplace_front(std::move(item));
        else
            box.insert(box.begin(),std::move(item));
    }
    void AddTop(const T&item){box.emplace_back(item);}
    void AddBot(const T&item){//vector doesn't have emplace_front
        if constexpr (has_emplace_front<T>::value)
            box.emplace_front(item);
        else
            box.insert(box.begin(),item);
    }
    T PopTop(){auto temp=std::move(box.back());box.pop_back();return temp;}
    bool contains(const T&item)const{return std::find(box.begin(),box.end(),item)!=box.end();}
    void erase(const T& item){
        auto it=std::find(box.begin(),box.end(),item);
        if(it!=box.end()) box.erase(it);
    }
    void clear()noexcept(noexcept(box.clear())){box.clear();}
    auto begin()const noexcept(noexcept(box.begin())){return box.begin();}
    auto end()const noexcept(noexcept(box.end())){return box.end();}
    bool empty()const noexcept(noexcept(box.empty())){return box.empty();}
    const auto&Top()const noexcept(noexcept(box.back())){return box.back();}
    const auto&Bot()const noexcept(noexcept(box.front())){return box.front();}
    int size()const noexcept(noexcept(box.size())){return static_cast<int>(box.size());}
protected:
    box_type box;
};
}
