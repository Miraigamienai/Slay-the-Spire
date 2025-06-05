#include "Game_object/character/Monster/ShieldGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    ShieldGremlin::ShieldGremlin(float offset_x, float offset_y, RUtil::Random& rng)
    :Abstraction::Monster_move_tracker<1, ShieldGremlinAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void ShieldGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case ShieldGremlinAction::Protect:
                //TODO: random protect
                break;
            case ShieldGremlinAction::ShieldBash:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{SHIELD_BASH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void ShieldGremlin::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(dungeon_shared.room_monsters.AliveCount()>1)
            set_move(ShieldGremlinAction::Protect, nullptr, Intent::defend, dungeon_shared.player->get_powers());
        else
            set_move(ShieldGremlinAction::ShieldBash, nullptr, Intent::attack, SHIELD_BASH_DAMAGE, dungeon_shared.player->get_powers());
    }

    const std::shared_ptr<Draw::ReTexture> &ShieldGremlin::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Shield-Gremlin-pretty.png");
}

