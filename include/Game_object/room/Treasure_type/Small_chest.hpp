#pragma once 
#include "Game_object/room/Rooms"
#include <memory>
namespace Room{
class Small_chest : public Treasure_item
{
    public:
    Small_chest();
    ~Small_chest()=default;
    std::vector<std::shared_ptr<Reward::Reward_item>> get_reward(Dungeon::Dungeon_shared& dungeon_shared)const override;
};
}