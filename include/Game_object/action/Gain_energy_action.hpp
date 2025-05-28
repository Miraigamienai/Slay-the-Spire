#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
class Gain_energy_action final:public Actions
{
public:
    Gain_energy_action(int amount)noexcept:amount(amount){
        this->duration=ACTION_DUR_MED;
    }
    ~Gain_energy_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration == ACTION_DUR_MED){
            if(amount + dungeon_shared.player->GetCurrEnergy() > dungeon_shared.player->GetMaxEnergy()){
                dungeon_shared.player->AddEnergy(dungeon_shared.player->GetMaxEnergy()-dungeon_shared.player->GetCurrEnergy(), dungeon_shared);
            }else{
                dungeon_shared.player->AddEnergy(amount, dungeon_shared);
            }
        }
        TimeGo();
    }
private:
    int amount;
};
}