#pragma once

#include <memory>

#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/action/Action_group_handler.hpp"
#include "Game_object/card/Card_group_handler.hpp"
#include "Game_object/dungeon/Dungeon_manager.hpp"
#include "Game_object/dungeon/Overlay.hpp"
#include "Game_object/effect_gen/Effect_gen_group.hpp"
#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Random_package.hpp"

namespace Dungeon{
struct Dungeon_shared
{
    Effect::Effect_group effs;
    Effect::Effect_group back_effs;
    Effect::Effect_group top_effs;
    EffectGen::Effect_gen_group gen_group;
    Action::Action_group_handler action_group_handler;
    Card::Card_group_handler card_group_handler;
    RUtil::Random_package random_package;
    Overlay overlay;
    std::shared_ptr<Character::Player> player=nullptr;
    Dungeon_manager manager;
    Monster::Monster_group room_monsters;
    std::shared_ptr<Map::Map_node> current_node = nullptr;
    std::shared_ptr<Map::Map_node> next_node = nullptr;
    void refresh_display(){
        card_group_handler.hand_cards_values_refresh(player->get_powers());
        room_monsters.RefreshDisplay(player->get_powers());
    }
};
}