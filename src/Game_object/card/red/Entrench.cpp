#include "Game_object/card/red/Entrench.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Card{
namespace Red{
    void Entrench::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(dungeon_shared.player, dungeon_shared.player->GetCurrentBlock()));
    }
}
}