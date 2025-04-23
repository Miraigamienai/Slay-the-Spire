#pragma once

#include "Game_object/action/Actions.hpp"

namespace Action{
class Empty_shuffle_action final:public Actions
{
public:
    Empty_shuffle_action(const int discard_pile_size) noexcept:
    amount(discard_pile_size),
    cnt(0),
    first_time(true)
    {
      this->duration=0.0F;
    }
    ~Empty_shuffle_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const int amount;
    int cnt;
    bool first_time;
    static constexpr float OEN_CARD_SHUFFLE_TIME=1.0F/60.0F;
};
}