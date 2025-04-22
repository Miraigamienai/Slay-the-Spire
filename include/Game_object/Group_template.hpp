#pragma once

namespace Template{
template<typename box_type>
class Group_template
{
public:
    Group_template()=default;
    virtual ~Group_template()=default;
    using T=typename box_type::value_type;
    void AddTop(T&&item){box.emplace_back(std::move(item));}
    void AddBot(T&&item){box.emplace_front(std::move(item));}
    void AddTop(const T&item){box.emplace_back(item);}
    void AddBot(const T&item){box.emplace_front(item);}
    T PopTop(){auto temp=std::move(box.back());box.pop_back();return temp;}
    void Clear(){box.clear();}
    
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
