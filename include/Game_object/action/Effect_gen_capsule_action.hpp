#pragma once

#include <memory>
#include <utility>//std::move

#include "Game_object/action/Actions.hpp"
#include "Game_object/effect_gen/Effect_gen.hpp"

namespace Action{
class Effect_gen_capsule_action: public Actions
{
public:
    Effect_gen_capsule_action(const std::shared_ptr<EffectGen::Effect_gen> &eff_gen,float duration)
        noexcept : eff_gen(eff_gen)
    {
        this->duration = this->start_dur = duration;
    }
    Effect_gen_capsule_action(std::shared_ptr<EffectGen::Effect_gen> &&eff_gen,float duration)
        noexcept : eff_gen(std::move(eff_gen))
    {
        this->duration = this->start_dur = duration;
    }
    ~Effect_gen_capsule_action()override=default;
    
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<EffectGen::Effect_gen> eff_gen;
    float start_dur;
};
}