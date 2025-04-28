#pragma once

#include <memory>
#include <deque>

#include "Game_object/Group_template.hpp"

namespace Card{
class Card_group_handler;
}
namespace Action{
class Actions;
class Action_group:public Template::Group_template<std::deque<std::shared_ptr<Action::Actions>>>
{
public:
    Action_group()=default;
    ~Action_group() override=default;
};
}