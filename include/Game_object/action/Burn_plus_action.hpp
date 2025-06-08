#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Cards_Text_Reader.hpp"

namespace Action{
class Burn_plus_action final:public Actions
{
public:
    Burn_plus_action()noexcept{
        this->duration = DUR;
    }
    ~Burn_plus_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==DUR){
            for(const auto &it:dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::m_discard>())
                if(it->card_text_id==RUtil::Cards_Text_ID::Burn) it->CallUpgrade();
            for(const auto &it:dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::draw_pile>())
                if(it->card_text_id==RUtil::Cards_Text_ID::Burn) it->CallUpgrade();
        }
        TimeGo();
    }
private:
    static constexpr float DUR=1.5F;
};
}