#include "Game_object/effect_gen/Card_upgrade_eff_gen.hpp"
#include "Game_object/effect/Hammer_effect.hpp"
#include "Game_object/effect/Shine_particle.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Effect_pool.hpp"

namespace EffectGen{
    static inline void clank(float _x, float _y, Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Hammer_effect>(_x, _y));
        for(int i=0;i<30;i++)
            dungeon_shared.top_effs.AddTop(Effect::Effect_pool<Effect::Shine_particle>::GetEffect(_x, _y, 10.0F));
    }

    void Card_upgrade_eff_gen::update(Dungeon::Dungeon_shared &dungeon_shared){
        //TODO:screen shake
        if(!one && this->duration<0.6F){
            one=true;
            clank(this->x-80.0F*Setting::SCALE, this->y, dungeon_shared);
        }else if(!two && this->duration<0.2F){
            two=true;
            clank(this->x+90.0F*Setting::SCALE, this->y-110.0F*Setting::SCALE, dungeon_shared);
        }
        TimeGo();
        if(this->is_done){
            clank(this->x+30.0F*Setting::SCALE, this->y+120.0F*Setting::SCALE, dungeon_shared);
        }
    }
}