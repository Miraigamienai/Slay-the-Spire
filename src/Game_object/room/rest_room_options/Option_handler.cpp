#include "Game_object/room/rest_room_options/Option_handler.hpp"
#include "Game_object/room/rest_room_options/Rest_option.hpp"
#include "Game_object/room/rest_room_options/Smith_option.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"

namespace Room{
namespace Option{
    Option_handler::Option_handler(const Dungeon::Dungeon_shared& dungeon_shared){
        //rest option
        opts.emplace_back(std::make_shared<Rest_option>(dungeon_shared.player->GetMaxHP()));
        //smite option
        opts.emplace_back(std::make_shared<Smith_option>(dungeon_shared.card_group_handler.can_upgrade_card()));
        
    }
}
}