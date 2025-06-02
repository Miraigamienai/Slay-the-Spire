#include "Game_object/character/Monster/WizardGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    WizardGremlin::WizardGremlin(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<0, WizardGremlinAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        charging_cnt(0){}
    
    void WizardGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(charging_cnt==3){
            charging_cnt=0;
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{ULTIMATE_BLAST, shared_from_this(), AttackType::fire}, dungeon_shared.player));
        }else{
            ++charging_cnt;
            //TODO: talk
        }
    }

    void WizardGremlin::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(charging_cnt==3)
            set_move(WizardGremlinAction::UltimateBlast, nullptr, Intent::attack, ULTIMATE_BLAST, dungeon_shared.player->get_powers());
        else
            set_move(WizardGremlinAction::Charging, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
    }

    const std::shared_ptr<Draw::ReTexture> &WizardGremlin::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Wizard-gremlin-pretty.png");
}

