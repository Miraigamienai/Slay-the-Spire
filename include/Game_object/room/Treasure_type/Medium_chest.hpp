#pragma once 
#include "Game_object/room/Treasure_item.hpp"
#include "Game_object/room/Rooms"
#include <memory>
namespace Room{
class Medium_chest : public Treasure_item
{
    public:
    Medium_chest();
    ~Medium_chest()=default;
    std::vector<std::shared_ptr<Reward::Reward_item>> get_reward(Dungeon::Dungeon_shared& dungeon_shared)const override;
};
}