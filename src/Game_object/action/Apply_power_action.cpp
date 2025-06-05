#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Remove_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Characters.hpp"
#include "Game_object/effect/Flash_power_eff.hpp"
#include "Game_object/effect_gen/Power_buff_debuff_gen.hpp"
#include "Game_object/power/Power_creator.hpp"

#include "Util/Logger.hpp"

namespace Action
{
    Apply_power_action::Apply_power_action(RUtil::Powers_Text_ID power_id,int amount, const std::shared_ptr<Character::Characters> &src, const std::shared_ptr<Character::Characters> &target, bool skip_reduce_once)
        :power_id(power_id),
        amount(amount),
        skip_reduce_once(skip_reduce_once),
        src(src),
        target(target)
    {
        duration=ACTION_DUR_FAST;
    }

    void Apply_power_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->amount==0){
            LOG_ERROR("Apply_power_action class amount is 0");
            is_done=true;
            return;
        }
        if(duration==ACTION_DUR_FAST){
            if(target->IsDie() || src->IsDie()){
                is_done=true;
                return;
            }
            //check already have or not
            std::shared_ptr<Power::Powers> power=nullptr;
            bool already_have=false;
            auto &powers=target->get_powers();
            for(const auto&it:powers){
                if(it->power_id==this->power_id){
                    power=it;
                    already_have=true;
                    break;
                }
            }
            if(already_have){
                //already have
                if(power->get_amount() == -this->amount){
                    dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Remove_power_action>(power, target));
                    is_done=true;
                    return;
                }
            }else{
                //not
                power=Power::Power_creator::GetPowerByID(this->power_id);
                if(skip_reduce_once) power->skip_reduce_once();
                target->add_power(power);
            }
            power->add_amount(this->amount);
            power->desc_update();
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Power_buff_debuff_gen>(target->GetFixedOriginX(), target->GetFixedOriginY()+target->GetHeight()/2.0F, power_id, amount, power->power_type, already_have));
            power->flash();
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Flash_power_eff>(target->GetcX(), target->GetcY(), power->region_128_id));
            dungeon_shared.refresh_display();
            if(power->power_type==Power::PowerType::debuff) target->use_animation<Character::Animation::FAST_SHAKE>(0.5F);
        }
        TimeGo();
    }
} // namespace Action