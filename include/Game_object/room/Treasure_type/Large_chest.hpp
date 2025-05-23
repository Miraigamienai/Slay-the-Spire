#pragma once 
#include "Game_object/room/Treasure_item.hpp"
#include "Game_object/room/rooms.hpp"
#include <memory>
namespace Room{
class Large_chest : public Treasure_item
{
    public:
    Large_chest();
    ~Large_chest()=default;
    std::vector<std::shared_ptr<Reward::Reward_item>> get_reward(Dungeon::Dungeon_shared& dungeon_shared)const override;
};
}