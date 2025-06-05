#pragma once

#include <utility>
#include <array>

#include "Game_object/character/Monster/Monsters.hpp"
#include "RUtil/Some_Math.hpp"

#include "Util/Logger.hpp"

namespace Abstraction{
using namespace RUtil;

template <int N, typename EnumClass>
class Monster_move_tracker : public Monster::Monsters 
{
public:
    template <typename...Args>
    Monster_move_tracker(Args&&...args)
        :Monster::Monsters(std::forward<Args>(args)...),
        current_n(0),
        idx(0){}
    ~Monster_move_tracker() override =default;
    bool is_current_move(EnumClass move_enum)const noexcept{
        if(current_n==0) return false;
        return arr[Math::SimpleRangeChange(idx+current_n-1, N)]==move_enum;
    }
    bool is_Nth_previous_move(int n, EnumClass move_enum)const noexcept{
        if(current_n<n) return false;
        return arr[Math::SimpleRangeChange(idx+current_n-n, N)]==move_enum;
    }
    bool is_last_two_move(EnumClass move_enum)const noexcept{
        if(current_n<2) return false;
        return arr[Math::SimpleRangeChange(idx+current_n-2, N)]==move_enum && arr[Math::SimpleRangeChange(idx+current_n-1, N)]==move_enum;     
    }
    bool is_last_N_move(int n, EnumClass move_enum)const noexcept{
        if(current_n<n) return false;
        for(int i=1;i<=n;i++)
            if(arr[Math::SimpleRangeChange(idx+current_n-i, N)]!=move_enum) return false;
        return true;
    }
    template <typename...Args>
    void set_move(EnumClass move_enum, Args&&...args){
        record(move_enum);
        Monster::Monsters::set_move(std::forward<Args>(args)...);
    }
    EnumClass current_move()const{
        if(current_n==0) LOG_ERROR("Getting current_move before set_move() called.");
        return arr[Math::SimpleRangeChange(idx+current_n-1, N)];
    }
private:
    std::array<EnumClass, N> arr;
    int current_n;
    int idx;
    void record(EnumClass move_enum)noexcept{
        if(current_n<N){
            arr[current_n++]=move_enum;
        }else{
            arr[idx++]=move_enum;
            if(idx>=N)idx=0;
        }
    }
};

template <typename EnumClass>
class Monster_move_tracker<1, EnumClass> : public Monster::Monsters
{
public:
    template <typename...Args>
    Monster_move_tracker(Args&&...args)
        :Monster::Monsters(std::forward<Args>(args)...),
        have_current(false){}
    template <typename...Args>
    void set_move(EnumClass move_enum, Args&&...args){
        have_current=true;
        current=move_enum;
        Monster::Monsters::set_move(std::forward<Args>(args)...);
    }
    bool is_current_move(EnumClass move_enum)const noexcept{
        return have_current&&current==move_enum;
    }
    EnumClass current_move()const{
        if(!have_current) LOG_ERROR("Getting current_move before set_move() called.");
        return current;
    }
private:
    bool have_current;
    EnumClass current;
};

template <typename EnumClass>
class Monster_move_tracker<0, EnumClass> : public Monster::Monsters
{
public:
    template <typename...Args>
    Monster_move_tracker(Args&&...args):Monster::Monsters(std::forward<Args>(args)...){}
    template <typename First, typename...Args>
    void set_move(First&&, Args&&...args){
        Monster::Monsters::set_move(std::forward<Args>(args)...);
    }
};
} // namespace Abstraction