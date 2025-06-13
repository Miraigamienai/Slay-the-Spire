#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
class Gain_energy_action final:public Actions
{
public:
    Gain_energy_action(int amount, bool can_out_max=false)noexcept:amount(amount),can_out_max(can_out_max){
        this->duration=ACTION_DUR_MED;
    }
    ~Gain_energy_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration == ACTION_DUR_MED){
            if(!can_out_max && amount + dungeon_shared.player->GetCurrEnergy() > dungeon_shared.player->GetMaxEnergy()){
                dungeon_shared.player->AddEnergy(dungeon_shared.player->GetMaxEnergy()-dungeon_shared.player->GetCurrEnergy(), dungeon_shared);
            }else{
                dungeon_shared.player->AddEnergy(amount, dungeon_shared);
            }
        }
        TimeGo();
    }
private:
    const int amount;
    const bool can_out_max;
};
}