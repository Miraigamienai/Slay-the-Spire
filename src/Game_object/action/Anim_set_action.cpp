#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/character/Characters.hpp"

#include "Util/Logger.hpp"

namespace Action
{
    static inline constexpr float GetAnimDur(Character::Animation anim){
        switch(anim){
            case Character::Animation::ATTACK_SLOW:return 0.5F;
            default:
                LOG_ERROR("This anim:'{}' doesn't have setter action",static_cast<int>(anim));
                return 1.0F;
        }
    }

    Anim_set_action::Anim_set_action(const std::shared_ptr<Character::Characters> &who,Character::Animation anim)
        :who(who),anim(anim)
    {
        this->duration=GetAnimDur(anim);
    }
    
    void Anim_set_action::update(Dungeon::Dungeon_shared &/* dungeon_shared */){
        if(!anim_once){
            anim_once=true;
            switch(anim){
                case Character::Animation::ATTACK_SLOW:
                    who->useSlowAttackAnimation();
                    break;
                default:
                    LOG_ERROR("This anim:'{}' doesn't have setter action",static_cast<int>(anim));
                    break;
            }
        }
        TimeGo();
    }

} // namespace Action
