#include "Game_object/effect_gen/Fire_ball_gen.hpp"
#include "Game_object/effect/Light_flare_particle_eff.hpp"
#include "Game_object/effect/Fire_burst_particle_eff.hpp"
#include "Game_object/effect_gen/Ghost_ignite_gen.hpp"
#include "Game_object/effect/Ghostly_fire_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Some_Math.hpp"

namespace EffectGen{
    Fire_ball_gen::Fire_ball_gen(float start_x, float start_y, float target_x, float target_y)
        :x(start_x),
        y(start_y),
        start_x(start_x),
        start_y(start_y),
        target_x(target_x+RUtil::Random::GetRandomFloat(-20.0F, 20.0F)*Setting::SCALE),
        target_y(target_y+RUtil::Random::GetRandomFloat(-20.0F, 20.0F)*Setting::SCALE),
        gen_timer(0.0F)
    {
        duration=DUR;
    }
    
    void Fire_ball_gen::update(Dungeon::Dungeon_shared &dungeon_shared){
        x=RUtil::Math::interpolation_fade(target_x, start_x, duration/DUR);
        y=RUtil::Math::interpolation_fade(target_y, start_y, duration/DUR);
        gen_timer-=DT;
        if(gen_timer<0.0F){
            gen_timer=0.016F;
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Light_flare_particle_eff>(x, y, RUtil::ToRGBA(RUtil::Colors::CHARTREUSE)));
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Fire_burst_particle_eff>(x, y));
        }
        TimeGo();
        if(is_done){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Ghostly_fire_eff>(x, y, true));
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Ghost_ignite_gen>(x, y));
        }
    }
}
