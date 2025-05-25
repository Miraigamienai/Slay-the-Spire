#include "Game_object/card/red/Shockwave.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "RUtil/Powers_Text_Reader.hpp"

namespace Card{
namespace Red{
    void Shockwave::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        for(const auto &it:dungeon_shared.room_monsters){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, this->magic_num, dungeon_shared.player, it));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable, this->magic_num, dungeon_shared.player, it));
        }
    }
}
}