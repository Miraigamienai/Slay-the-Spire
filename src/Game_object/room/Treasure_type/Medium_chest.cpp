#include "Game_object/room/Treasure_item.hpp"
#include "Game_object/room/rooms.hpp"
#include "RUtil/Image_book.hpp"
#include "Game_object/room/Treasure_type/Medium_chest.hpp"
#include "Game_object/reward_item/Card_reward_item.hpp"
#include "Game_object/card/Card_generate.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include <memory>
namespace Room{

    Medium_chest::Medium_chest(): Treasure_item(
              RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/treasureRoom/mediumChest.png"),
              RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/treasureRoom/mediumChestOpened.png")) {}
    std::vector<std::shared_ptr<Reward::Reward_item>> Medium_chest::get_reward(Dungeon::Dungeon_shared& dungeon_shared)const {
        std::vector<std::shared_ptr<Card::Cards>> card_vec;
        for(int i=0;i<2;i++) card_vec.emplace_back(Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.card_reward_rng));
        std::vector<std::shared_ptr<Reward::Reward_item>> reward_vec;
        reward_vec.emplace_back(std::make_shared<Reward::Card_reward_item>(card_vec));
        dungeon_shared.manager.open<Abstraction::ScreenType::combat_reward>(reward_vec);
        return reward_vec;
    }

}