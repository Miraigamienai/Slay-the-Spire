#include "Game_object/room/Elite_room.hpp"
#include "Game_object/card/Card_generate.hpp"
#include "Game_object/reward_item/Card_reward_item.hpp"
#include "Game_object/reward_item/Gold_reward_item.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Image_book.hpp"

namespace Room{
void Elite_room::to_get_reward(Dungeon::Dungeon_shared &dungeon_shared)const{
    std::vector<std::shared_ptr<Reward::Reward_item>> reward_vec;
    //random golds
    reward_vec.emplace_back(std::make_shared<Reward::Gold_reward_item>(dungeon_shared.random_package.reward_rng.NextInt(25, 36)));
    //random 3 cards * 2
    for(int j=0;j<2;j++){
        std::vector<std::shared_ptr<Card::Cards>> cards;
        for(int i=0;i<3;i++) cards.emplace_back(Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.reward_rng));
        reward_vec.emplace_back(std::make_shared<Reward::Card_reward_item>(cards));
    }
    dungeon_shared.manager.open<Abstraction::ScreenType::combat_reward>(reward_vec);
}

const std::shared_ptr<Draw::ReTexture> &Elite_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/elite.png"),
                                       &Elite_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/eliteOutline.png");
}