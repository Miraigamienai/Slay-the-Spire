#include "Game_object/card/red/Barricade.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Apply_power_action.hpp"

namespace Card{
namespace Red{
    void Barricade::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        if(!dungeon_shared.player->get_powers().no_lose_block())
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Barricade, 1, dungeon_shared.player, dungeon_shared.player));
    }
}
}