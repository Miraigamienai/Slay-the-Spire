#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/character/Characters.hpp"

#include "Util/Logger.hpp"

namespace Action
{
    static inline constexpr float GetAnimDur(Character::Animation anim){
        switch(anim){
            case Character::Animation::ATTACK_SLOW:return 0.5F;
            case Character::Animation::HOP:
            case Character::Animation::ATTACK_FAST:
            case Character::Animation::JUMP:       return 0.25F;
            default:
                LOG_ERROR("This anim:'{}' doesn't have setter action",static_cast<int>(anim));
                return 1.0F;
        }
    }

    Anim_set_action::Anim_set_action(const std::shared_ptr<Character::Characters> &who,Character::Animation anim)
        :who(who),anim(anim),anim_once(false),anim_dur(0.0F)
    {
        this->duration=GetAnimDur(anim);
    }
    Anim_set_action::Anim_set_action(const std::shared_ptr<Character::Characters> &who, Character::Animation anim, float anim_dur, float dur)
        :who(who), anim(anim), anim_once(false), anim_dur(anim_dur)
    {
        this->duration=dur;
    }
    void Anim_set_action::update(Dungeon::Dungeon_shared &/* dungeon_shared */){
        if(!anim_once){
            anim_once=true;
            switch(anim){
                case Character::Animation::ATTACK_SLOW:
                    who->use_animation<Character::Animation::ATTACK_SLOW>();
                    break;
                case Character::Animation::HOP:
                    who->use_animation<Character::Animation::HOP>();
                    break;
                case Character::Animation::ATTACK_FAST:
                    who->use_animation<Character::Animation::ATTACK_FAST>();
                    break;
                case Character::Animation::JUMP:
                    who->use_animation<Character::Animation::JUMP>();
                    break;
                case Character::Animation::SHAKE:
                    who->use_animation<Character::Animation::SHAKE>(anim_dur);
                    break;
                case Character::Animation::FAST_SHAKE:
                    who->use_animation<Character::Animation::FAST_SHAKE>(anim_dur);
                    break;
                default:
                    LOG_ERROR("This anim:'{}' doesn't have setter action",static_cast<int>(anim));
                    break;
            }
        }
        TimeGo();
    }

} // namespace Action
