#include "Game_object/character/Monster/Lagavulin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Reduce_power_action.hpp"
#include "Game_object/action/Call_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    Lagavulin::Lagavulin(RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<0, LagavulinAction>(0.0F, 20.0F, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), SLEEP_IMG),
        sleep_cnt(0),
        is_awake(false),
        move_cnt(0){}
    
    void Lagavulin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(!is_awake){
            ++sleep_cnt;
            if(sleep_cnt>=3)
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Lagavulin, decltype(dungeon_shared)>>(std::static_pointer_cast<Lagavulin>(shared_from_this()), dungeon_shared));
        }else{
            if(move_cnt==-1){
                move_cnt=0;
            }else{
                switch (PATTERN[move_cnt]){
                    case LagavulinAction::Attack:
                        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));    
                        break;
                    case LagavulinAction::SiphonSoul:
                        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Dexterity, SIPHONSOUL_DEBUFF_NUM, shared_from_this(), dungeon_shared.player, true));
                        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, SIPHONSOUL_DEBUFF_NUM, shared_from_this(), dungeon_shared.player, true));
                    default:
                        break;
                }
                ++move_cnt;
                if(move_cnt>=static_cast<int>(PATTERN.size()))move_cnt=0;
            }
        }
    }

    void Lagavulin::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(!is_awake){
            set_move(LagavulinAction::Sleep, nullptr, Intent::sleep, dungeon_shared.player->get_powers());
            return;
        }
        switch(PATTERN[move_cnt]){
            case LagavulinAction::Attack:
                set_move(LagavulinAction::Attack, nullptr, Intent::attack, ATTACK_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case LagavulinAction::SiphonSoul:
                set_move(LagavulinAction::SiphonSoul, nullptr, Intent::strong_debuff, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    void Lagavulin::at_combat_start(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), METALLICIZE_BLOCK));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Metallicize, METALLICIZE_BLOCK, shared_from_this(), shared_from_this()));
    }

    void Lagavulin::Call(Dungeon::Dungeon_shared &dungeon_shared){
        is_awake=true;
        resize_hb(0.0F, -25.0F*Setting::SCALE, 320.0F*Setting::SCALE, 360.0F*Setting::SCALE);
        set_img(AWAKE_IMG);
        std::shared_ptr<Power::Powers> _p = nullptr;
        for(const auto&it:get_powers())
            if(it->power_id == RUtil::Powers_Text_ID::Metallicize) _p = it;
        if(_p!=nullptr)
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Reduce_power_action>(_p, shared_from_this(), METALLICIZE_BLOCK));
    }

    void Lagavulin::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared){
        int temp=current_HP;
        Monsters::damage(damage_info, dungeon_shared);
        if(!is_awake && temp!=current_HP){
            is_awake=true;
            move_cnt=-1;
            set_move(LagavulinAction::Stun, nullptr, Intent::stun, dungeon_shared.player->get_powers());
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Lagavulin, decltype(dungeon_shared)>>(std::static_pointer_cast<Lagavulin>(shared_from_this()), dungeon_shared));
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Lagavulin::AWAKE_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Lagavulin/Lagavulin-awake-pretty.png");
    const std::shared_ptr<Draw::ReTexture> &Lagavulin::SLEEP_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Lagavulin/Lagavulin-zzz-pretty.png");
}