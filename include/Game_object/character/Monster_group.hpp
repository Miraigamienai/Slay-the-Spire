#pragma once

#include <vector>
#include <memory>

#include "Game_object/Group_template.hpp"
#include "Game_object/character/Monster/Monsters.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
}
namespace Dungeon{
    class Dungeon_shared;
}

namespace Monster{
class Monster_group final:public Template::Group_template<std::vector<std::shared_ptr<Monsters>>>
{
public:
    Monster_group()=default;
    ~Monster_group()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update();
    void at_round_end(Dungeon::Dungeon_shared &dungeon_shared);
    void at_turn_start(Dungeon::Dungeon_shared &dungeon_shared);
    
    std::shared_ptr<Monsters> GetTipHoveredMonster()const{
        for(const auto &it:box) if(it->TipHovered()) return it;
        return nullptr;    
    }
    std::shared_ptr<Monsters> GetBodyHoveredMonster()const{
        for(const auto &it:box) if(it->BodyHovered()) return it;
        return nullptr;
    }
    void RefreshDisplay(const Power::Power_group &player_powers){
        for(const auto&it:box) it->refresh_dmg_display(player_powers);
    }
    bool IsAllDie()const{
        for(const auto &it:box) 
            if(!it->IsDie()) return false;
        return true;
    }
    int AliveCount()const{
        int cnt=0;
        for(const auto &it:box) 
            if(!it->IsDie()) cnt++;
        return cnt;
    }
    void ShowHP()const{for(const auto&it:box)it->ShowHP();}
    void next_move(Dungeon::Dungeon_shared &dungeon_shared){for(const auto&it:box)it->next_move(dungeon_shared);}
};
}