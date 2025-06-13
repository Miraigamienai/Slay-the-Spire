#include "Game_object/card/red/Inflame.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/effect_gen/Inflame_eff_gen.hpp"

namespace Card{
namespace Red{
    void Inflame::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Inflame_eff_gen>(dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY()), 1.0F));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, this->magic_num, dungeon_shared.player, dungeon_shared.player));
    }
}
}