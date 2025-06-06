#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Weighty_impact_eff.hpp"
#include "Game_object/effect/Border_flash_eff.hpp"
#include "Game_object/effect/Damage_impact_curvy_eff.hpp"
#include "Game_object/effect/Shine_particle.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/ColorValuesOnly.hpp"

namespace EffectGen{
class Weighty_impact_gen final:public Effect_gen
{
public:
    Weighty_impact_gen(float x, float y, float color_r, float color_b)
        :x(x), y(y), r(color_r), b(color_b)
    {
        duration=DUR;
    }
    ~Weighty_impact_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==DUR){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Weighty_impact_eff>(x, y, r, b));
        }
        TimeGo();
        if(is_done){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Border_flash_eff>(RUtil::ToRGBA(RUtil::Colors::ORANGE)));
            for(int i=0;i<5;i++)
                dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Damage_impact_curvy_eff>(glm::vec2{x, y}, RUtil::ToRGBA(RUtil::Colors::GOLDENROD)));
            for(int i=0;i<30;i++)
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Shine_particle>(x+RUtil::Random::GetRandomFloat(-100.0F, 100.0F)*Setting::SCALE, y+RUtil::Random::GetRandomFloat(-50.0F, 120.0F)*Setting::SCALE));
        }
    }
private:
    const float x, y, r, b;

    static constexpr float DUR=0.8F;
};
}