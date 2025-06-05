#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father

//fwd decl
namespace Character{
    class Characters;
}
namespace RUtil{
    enum class Powers_Text_ID:int;
}

namespace Action{
class Apply_power_action final:public Actions
{
public:
    //id amount from to 
    Apply_power_action(RUtil::Powers_Text_ID power_id,int amount, const std::shared_ptr<Character::Characters> &src, const std::shared_ptr<Character::Characters> &target, bool skip_reduce_once=false);
    ~Apply_power_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const RUtil::Powers_Text_ID power_id;
    int amount;
    const bool skip_reduce_once;
    const std::shared_ptr<Character::Characters> src;
    const std::shared_ptr<Character::Characters> target;
};
}