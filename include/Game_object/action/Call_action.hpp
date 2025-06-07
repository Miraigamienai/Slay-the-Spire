#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"

namespace Action{
template <typename T, typename Val_Type>
class Call_action final:public Actions
{
public:
    Call_action(const std::shared_ptr<T>&ptr, Val_Type val)noexcept:ptr(ptr),val(val){};
    ~Call_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        ptr->Call(val);
        is_done=true;
    }
private:
    const std::shared_ptr<T> ptr;
    const Val_Type val;
};
}