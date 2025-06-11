#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"

namespace Action{
template <typename T, typename Val_Type1 = void, typename Val_Type2 = void>
class Call_action final:public Actions
{
public:
    Call_action(const std::shared_ptr<T>&ptr, Val_Type1 val1, Val_Type2 val2):ptr(ptr),val1(val1),val2(val2){};
    ~Call_action() override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)override{
        ptr->Call(val1, val2);
        is_done=true;
    }
private:
    const std::shared_ptr<T> ptr;
    const Val_Type1 val1;
    const Val_Type2 val2;
};
template <typename T, typename Val_Type>
class Call_action<T, Val_Type, void> final:public Actions
{
public:
    Call_action(const std::shared_ptr<T>&ptr, Val_Type val):ptr(ptr),val(val){};
    ~Call_action() override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)override{
        ptr->Call(val);
        is_done=true;
    }
private:
    const std::shared_ptr<T> ptr;
    const Val_Type val;
};
template <typename T>
class Call_action<T, void, void> final:public Actions
{
public:
    Call_action(const std::shared_ptr<T>&ptr):ptr(ptr){};
    ~Call_action() override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)override{
        ptr->Call();
        is_done=true;
    }
private:
    const std::shared_ptr<T> ptr;
};
}