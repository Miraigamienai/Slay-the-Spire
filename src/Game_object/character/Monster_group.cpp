#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/power/Power_group.hpp"
#include "Game_object/power/Powers.hpp"
#include "Draw/Draw_2D.hpp"

namespace Monster
{
    std::shared_ptr<Monsters> Monster_group::GetHoveredMonster()const{
        for(const auto &it:box) if(it->hovered()) return it;
        return nullptr;
    }
    void Monster_group::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        for(const auto &it:box){
            if(!it->IsDie()) it->render(r2);
            
        } 
    }
    void Monster_group::update(){
        
        auto it = std::remove_if(box.begin(), box.end(), 
            [](const std::shared_ptr<Monsters>& monster) { 
                monster->update();
                return monster->IsDie(); 
            });
        
        box.erase(it, box.end());
    }
    bool Monster_group::IsAllDie()const{
        for(const auto &it:box) 
            if(!it->IsDie()) return false;
        return true;
    }
    
    void Monster_group::at_turn_end(Dungeon::Dungeon_shared &dungeon_shared){
        for(const auto&it1:box)
            for(const auto&it2:it1->get_powers())
                it2->at_turn_end(dungeon_shared, it1);
    }
} // namespace Monster
